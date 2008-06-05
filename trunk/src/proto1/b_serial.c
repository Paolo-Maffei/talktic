#include "jsint.h"
#include <avr/io.h>
#include <avr/interrupt.h>

extern JSVirtualMachine *s_vm;

#define BUF_SIZE 64

#define BAUD_RATE 9600		// impossible at 115200bps
#define UART 0
#define _(a,b) a##0##b

#define FRAMING_ERROR        (1 << FE)
#define PARITY_ERROR         (1 << UPE)
#define DATA_OVERRUN         (1 << DOR)
#define DATA_REGISTER_EMPTY  (1 << UDRE)
#define RX_COMPLETE          (1 << RXC)

#if (BUF_SIZE < 256)
typedef unsigned char bufsize_t;
#else
typedef unsigned int bufsize_t;
#endif

static volatile char s_buf[BUF_SIZE];
static volatile bufsize_t s_buf_w_index, s_buf_r_index, s_buf_counter;

static void serialSend_global_method(JSVirtualMachine * vm, JSBuiltinInfo * builtin_info,
					 void *instance_context, JSNode * result_return, JSNode * args)
{
	JSNode n;
	unsigned int i;

	if (args->u.vinteger == 1) {
		js_vm_to_string(vm, &args[1], &n);
		for(i = 0; i<n.u.vstring->len; i++) {
			loop_until_bit_is_set(_(UCSR,A), UDRE);
			_(UDR,) = *(n.u.vstring->data+i);
		}
	}
	result_return->type = JS_UNDEFINED;
}

static void serialAvailable_global_method(JSVirtualMachine * vm, JSBuiltinInfo * builtin_info,
					 void *instance_context, JSNode * result_return, JSNode * args)
{
    result_return->type = JS_INTEGER;
	result_return->u.vinteger = s_buf_counter;
}

static bufsize_t buf_readline(char* buf, bufsize_t bufsize) {
	unsigned char save_sreg;
	bufsize_t len = 0;
	char ch;

	while(s_buf_counter == 0);

	while(s_buf_counter > 0 && len < bufsize) {
		save_sreg = SREG;
		cli();
		ch = s_buf[s_buf_r_index];
		if(++s_buf_r_index == BUF_SIZE) {
			s_buf_r_index = 0;
		}
		s_buf_counter--;
		*(buf+(len++)) = ch;
		SREG = save_sreg;
		if(ch == '\r' || ch == '\n' || ch == '\0') {
			break;
		}
	}
	buf[len] = '\0';

	return len;
}

static void serialRead_global_method(JSVirtualMachine * vm, JSBuiltinInfo * builtin_info,
					 void *instance_context, JSNode * result_return, JSNode * args)
{
	char buf[BUF_SIZE];
	bufsize_t len;
	len = buf_readline(buf, BUF_SIZE);
	js_vm_make_string(vm, result_return, buf, len);
}

static int onSerialReceive_global_vm_interrupt(JSVirtualMachine * vm, void *data)
{
	JSNode argv[1];

	argv[0].type = JS_INTEGER;
	argv[0].u.vinteger = 0;

	js_vm_apply(vm, "onSerialReceive", NULL, 1, argv);
	return 0;
}

static void serialInit_global_method(JSVirtualMachine * vm, JSBuiltinInfo * builtin_info,
					 void *instance_context, JSNode * result_return, JSNode * args)
{
	unsigned long baud = BAUD_RATE;
	unsigned short baud_reg;

	result_return->type = JS_UNDEFINED;

	if (args->u.vinteger > 0) {
		baud = js_vm_to_int32(vm, &args[1]);
	}
	baud_reg = (unsigned short)((F_CPU)/(16*baud) -1);

	_(UBRR,L) = (unsigned char)(baud_reg & 0x00ff);
	_(UBRR,H) = (unsigned char)(baud_reg >> 8);
	_(UCSR,A) = 0x00;
	_(UCSR,B) = 0b10011000; // allow receive interrupt, enable send and receive
	_(UCSR,C) = 0x06;

	s_buf_w_index = s_buf_r_index = s_buf_counter = 0;

	sei();
	vm->interrupt_table[1].enable = 1;
}

ISR(_(SIG_UART,_RECV))
{
    unsigned char status;
    char data;

    status = _(UCSR,A);
    data = _(UDR,);

    if ((status & (FRAMING_ERROR | PARITY_ERROR | DATA_OVERRUN)) == 0) {
        s_buf[s_buf_w_index] = data;

        if (++s_buf_w_index == BUF_SIZE) {
            s_buf_w_index = 0;
        }
        if (++s_buf_counter == BUF_SIZE) {
			// buffer over flow
            s_buf_counter = 0;
        }
		if(data == '\n' || data == '\r' || data == '\0') {
			if(s_vm && !(s_vm->interrupt_table[1].fired)) {
				s_vm->interrupt_table[1].fired = 1;
			}
		}
    }
}

void init_builtin_serial(JSVirtualMachine *vm) {
	JSBuiltinInfo *info;
	JSNode *n;
	unsigned char i;

	struct {
		char *name;
		JSBuiltinGlobalMethod method;
	} global_methods[] = {
		{"serialInit", serialInit_global_method},
		{"serialSend", serialSend_global_method},
		{"serialRead", serialRead_global_method},
		{"serialAvailable", serialAvailable_global_method},
		{NULL, NULL}
	};

	for (i = 0; global_methods[i].name; i++) {
		info = js_vm_builtin_info_create(vm);
		info->global_method_proc = global_methods[i].method;

		n = &vm->globals[js_vm_intern(vm, global_methods[i].name)];
		js_vm_builtin_create(vm, n, info, NULL);
	}

	vm->interrupt_table[1].handler = onSerialReceive_global_vm_interrupt;
}
