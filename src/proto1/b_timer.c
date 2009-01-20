#include "jsint.h"
#include <avr/io.h>
#include <avr/interrupt.h>

extern JSVirtualMachine *s_vm;

#define B_TIMER_MIN_INTERVAL 1

typedef struct timer_node_st{
    JSNode  func;               //function to call
    unsigned int interval;      //original interval
    unsigned int when;          //nominal time to run this timer reckoned from last timer
    struct timer_node_st* next;
    unsigned char isRepeated;   //interval or timeout?
} TIMER_NODE;

static unsigned int tickCount = 0;
static unsigned int intervalCount = 0;

static TIMER_NODE* timerList;
static TIMER_NODE* firedTimerList;
static TIMER_NODE* firedTimerListTail;

static void
getTickCount_global_method(JSVirtualMachine * vm, JSBuiltinInfo * builtin_info,
				  void *instance_context, JSNode * result_return, JSNode * args)
{
	result_return->type = JS_INTEGER;
	result_return->u.vinteger = 0;

	if (args->u.vinteger == 0) {
        result_return->u.vinteger = (JSInt32)tickCount;
    }
}

// 1000/128[msec] per tickCount
ISR(SIG_OVERFLOW0) {
	tickCount++;
    if(timerList == NULL) return;
    
    intervalCount++;
	while(intervalCount > timerList->when){
	    
        intervalCount -= timerList->when;

        //move timer to the execution queue.
	    if(firedTimerList == NULL){
            firedTimerList = timerList;
            firedTimerListTail = timerList;
            timerList = timerList->next;
            firedTimerListTail->next = NULL;
	    }else{
            firedTimerListTail->next = timerList;
            firedTimerListTail = timerList;
            timerList = timerList->next;	        
            firedTimerListTail->next = NULL;
	    }
	    
		if(s_vm && !(s_vm->interrupt_table[2].fired)) {
			s_vm->interrupt_table[2].fired = 1;
		}
	}
}

static void addTimer(TIMER_NODE** pTimerList, TIMER_NODE* aTimer){
    
    TIMER_NODE *current, *previous;
    
    aTimer->when = aTimer->interval >> 3;   //rough approximation(2.34% error)
                                            //using pseudo value instead of real one.
                                            //pseudo: 1024/128[msec] per tickCount
                                            //real:   1000/128[msec] per tickCount

    if(timerList == NULL){
         //add aTimer at the begining as timerList contains nothing
         aTimer->next = NULL;
         *pTimerList = aTimer;
    }else{
         previous = NULL;
         current = timerList;
         do{
             if(aTimer->when < current->when){
                 if(previous == NULL){
                     //add aTimer at the top of nodes
                     current->when = current->when - aTimer->when;
                     aTimer->next = current;
                     *pTimerList = aTimer;
                     return;
                 }else{
                     //add aTimer between previous and current
                     previous->next = aTimer;
                     current->when = current->when - aTimer->when;
                     aTimer->next = current;                    
                     return;
                 }
             }else{
                 //skip a node to find suit position
                 aTimer->when = aTimer->when - current->when;
                 previous = current;
                 current = current->next;
             }
         }while(current != NULL);
         //add aTimer at the last of nodes
         previous->next = aTimer;
         aTimer->next = NULL;
     }
}


static void
setInterval_global_method(JSVirtualMachine * vm, JSBuiltinInfo * builtin_info,
				  void *instance_context, JSNode * result_return, JSNode * args)
{
	result_return->type = JS_INTEGER;
	result_return->u.vinteger = 0;

    TIMER_NODE* aTimer = malloc(sizeof(TIMER_NODE));

	if (args->u.vinteger == 2) {
	    
        (&args[1])->type = JS_FUNC;    
        aTimer->func = args[1];                 //there would be better way to pass function
        aTimer->interval = js_vm_to_int32(vm, &args[2]);
        aTimer->isRepeated = 1;
    	result_return->u.vinteger = aTimer;     //should be more careful to cast 
        addTimer(&timerList, aTimer);
    }
}

static void
clearInterval_global_method(JSVirtualMachine * vm, JSBuiltinInfo * builtin_info,
				  void *instance_context, JSNode * result_return, JSNode * args)
{
    TIMER_NODE *aTimer, *current, *previous;
    
	result_return->type = JS_INTEGER;
	result_return->u.vinteger = 0;

	if (args->u.vinteger == 1) {
	    
	    aTimer = (TIMER_NODE*)(js_vm_to_int32(vm, &args[1]));   //should be more careful to cast 
	    if (aTimer == NULL)
            return;
            
        if(timerList != NULL)
        {
            previous = NULL;
            current = timerList;
            do{
                if(current == aTimer){
                    if(previous == NULL){
                        timerList = current->next;
                    }else{
                        previous->next = current->next;
                    }
                    free(aTimer);
                	result_return->u.vinteger = 1;
                    return;
                }
                previous = current;
                current = current->next;
            }while(current != NULL);
            
            //no match within timerList
        }        
        
        //if the timer is found in execution queue, just stop further repeat 
        if(firedTimerList != NULL){
            current = firedTimerList;
            do{
                if(current == aTimer){
                    aTimer->isRepeated = 0;
                	result_return->u.vinteger = 1;
                    return;
                }
                current = current->next;            
            }while(current != NULL);
            
            //no match within firedTimerList
        }

    }
}


static int onTimer_global_vm_interrupt(JSVirtualMachine * vm, void *data)
{
    TIMER_NODE *aTimer;
	JSNode argv[1];

	argv[0].type = JS_INTEGER;
	argv[0].u.vinteger = 0;

    while(firedTimerList != NULL){
        js_vm_apply(vm, NULL, &(firedTimerList->func), 1, argv);
        aTimer = firedTimerList;
        firedTimerList = firedTimerList -> next;
        if (aTimer->isRepeated){
            addTimer(&timerList, aTimer);
        }else{
            free(aTimer);
        }
    }
	return 0;
}

void init_builtin_timer(JSVirtualMachine *vm) {
	JSBuiltinInfo *info;
	JSNode *n;
	unsigned char i;

	struct {
		char *name;
		JSBuiltinGlobalMethod method;
	} global_methods[] = {
		{"getTickCount", getTickCount_global_method},
    	{"setInterval", setInterval_global_method},
		{"clearInterval", clearInterval_global_method},
/*
		{"setTimeout", setTimeout_global_method},
		{"clearTimeout", clearTimeout_global_method},
*/
		{NULL, NULL}
	};

	for (i = 0; global_methods[i].name; i++) {
		info = js_vm_builtin_info_create(vm);
		info->global_method_proc = global_methods[i].method;

		n = &vm->globals[js_vm_intern(vm, global_methods[i].name)];
		js_vm_builtin_create(vm, n, info, NULL);
	}
	
    timerList = NULL;
    firedTimerList = NULL;

	vm->interrupt_table[2].handler = onTimer_global_vm_interrupt;
	vm->interrupt_table[2].enable = 1;

	//setup timer0
    ASSR |= (1 << AS0);     //use external oscillator
    TCCR0 |= (1 << CS00);   //normal mode, no prescaling
    TIMSK |= (1 << TOIE0);  //Enable counter0 overflow interrupt
    sei(); // Enable global interrupt
	
}
