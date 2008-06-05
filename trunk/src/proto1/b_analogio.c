#include "jsint.h"
#include "pwm.h"
#include "device_ad.h"
#include <avr/io.h>

#define delay_us _delay_us
#define delay_ms _delay_ms

#include <util/delay.h>

static void
analogRead_global_method(JSVirtualMachine * vm, JSBuiltinInfo * builtin_info,
				  void *instance_context, JSNode * result_return, JSNode * args)
{
	unsigned int val;
	JSInt32 pin;

	result_return->type = JS_FLOAT;
	result_return->u.vfloat = 0;

	if (args->u.vinteger == 1) {
		pin = js_vm_to_int32(vm, &args[1]);
		if(pin < 0 || pin > 7) {
			DEVICE_ADC_UNINIT();
			return;
		}

		if(! DEVICE_ADC_CHECK()) {
			DEVICE_ADC_INIT();
			DEVICE_ADC_ENABLE();
		}

		// チャンネルを変更したときは最低7us待つ必要がある
    	DEVICE_ADC_SET_CHANNEL(pin);
		delay_us(7);

		DEVICE_ADC_SAMPLE_SINGLE();
		DEVICE_ADC_GET_SAMPLE_10BIT(val);

		result_return->u.vfloat = (JSFloat)val / 0x3ff;
	}
}

static void
analogWrite_global_method(JSVirtualMachine * vm, JSBuiltinInfo * builtin_info,
				  void *instance_context, JSNode * result_return, JSNode * args)
{
	unsigned char d;
	JSInt32 pin;
	JSNode n;

	result_return->type = JS_BOOLEAN;
	result_return->u.vboolean = 0;

	if (args->u.vinteger == 2) {
		pin = js_vm_to_int32(vm, &args[1]);
		js_vm_to_number(vm, &args[2], &n);

		if(n.type == JS_INTEGER) {
			d = n.u.vinteger;
		} else if (n.type == JS_FLOAT) {
			d = (int)(n.u.vfloat * 0xff);
		} else {
			return;
		}

		switch(pin) {
		case 0:
			if(! PWM_is_inited(0)) {
				PWM_init(0);
			}
			PWM_out(0,d);
			break;
		case 1:
			if(! PWM_is_inited(1)) {
				PWM_init(1);
			}
			PWM_out(1,d);
			break;
		default:
			return;
		}
		result_return->u.vboolean = 1;
	}
}

static void
soundWrite_global_method(JSVirtualMachine * vm, JSBuiltinInfo * builtin_info,
				  void *instance_context, JSNode * result_return, JSNode * args)
{
	JSNode n;
	JSInt32 pin;
	JSFloat f;

	result_return->type = JS_BOOLEAN;
	result_return->u.vboolean = 0;

	if (args->u.vinteger == 2) {
		pin = js_vm_to_int32(vm, &args[1]);
		js_vm_to_number(vm, &args[2], &n);

		if(n.type == JS_INTEGER) {
			f = (JSFloat)n.u.vinteger;
		} else if (n.type == JS_FLOAT) {
			f = n.u.vfloat;
		} else {
			return;
		}

		if(f == 0) {
			switch(pin) {
			case 0:
				SOUND_off(0);
				break;
			case 1:
				SOUND_off(1);
				break;
			default:
				return;
			}
		} else {
			if(f<245) {
				f = 245;
			}
			switch(args[1].u.vinteger) {
			case 0:
				if(! SOUND_is_inited(0)) {
					SOUND_init(0);
				}
				SOUND_out(0,f);
				break;
			case 1:
				if(! SOUND_is_inited(1)) {
					SOUND_init(1);
				}
				SOUND_out(1,f);
				break;
			default:
				return;
			}
		}
		result_return->u.vboolean = 1;
	}
}

void init_builtin_analogio(JSVirtualMachine *vm) {
	JSBuiltinInfo *info;
	JSNode *n;
	unsigned char i;

	struct {
		char *name;
		JSBuiltinGlobalMethod method;
	} global_methods[] = {
		{"analogRead", analogRead_global_method},
		{"analogWrite", analogWrite_global_method},
		{"soundWrite", soundWrite_global_method},
		{NULL, NULL}
	};

	for (i = 0; global_methods[i].name; i++) {
		info = js_vm_builtin_info_create(vm);
		info->global_method_proc = global_methods[i].method;

		n = &vm->globals[js_vm_intern(vm, global_methods[i].name)];
		js_vm_builtin_create(vm, n, info, NULL);
	}
}
