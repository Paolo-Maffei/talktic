#include "jsint.h"

#include <avr/io.h>
//#include <avr/interrupt.h>

static void
led_global_method(JSVirtualMachine * vm, JSBuiltinInfo * builtin_info,
				  void *instance_context, JSNode * result_return, JSNode * args)
{
	unsigned char pin = 0;
	if (args->u.vinteger == 2 && args[1].type == JS_INTEGER && args[2].type == JS_BOOLEAN) {
		switch (args[1].u.vinteger) {
		case 1:
			pin = 4;
			break;
		case 2:
			pin = 7;
			break;
		}
		if (pin && args[2].u.vboolean) {
			PORTB |= (1 << pin);
		} else {
			PORTB &= ~(1 << pin);
		}
	}
	result_return->type = JS_UNDEFINED;
}

/*
static int interrupt5VMHandler(JSVirtualMachine * vm, void *data)
{
	printf("interrupt5");
	js_vm_apply(vm, "onDigitalIO", NULL, 0, NULL);
	return 0;
}

ISR(SIG_INTERRUPT5)
{
	if (s_vm) {
		if (!(s_vm->interrupt_table[1].fired)) {
			s_vm->interrupt_table[1].fired = 1;
		}
	}
}

ISR(SIG_INTERRUPT4)
{
	if (s_vm) {
		js_vm_apply(s_vm, "onDigitalIo2", NULL, 0, NULL);
	}
}
*/

void init_builtin_digital_io() {
	DDRB |= (1 << 7) | (1 << 4);
	PORTB |= (1 << 7) | (1 << 4);
/*
	// enable interrupt 5 on up edge
	EICRB |= (1 << 2) | (1 << 3);
	EIMSK |= (1 << 5);
	EICRB |= (1 << 0) | (1 << 1);
	EIMSK |= (1 << 4);
	sei();
*/
}
