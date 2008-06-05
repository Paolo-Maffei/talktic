#include "jsint.h"
#include "pwm.h"
#include "device_ad.h"
#include <avr/io.h>

static void
pwm_global_method(JSVirtualMachine * vm, JSBuiltinInfo * builtin_info,
				  void *instance_context, JSNode * result_return, JSNode * args)
{
	result_return->type = JS_BOOLEAN;
	result_return->u.vboolean = 0;
	if (args->u.vinteger == 2
		&& args[1].type == JS_INTEGER
		&& args[1].u.vinteger >= 0
		&& args[1].u.vinteger < 2
		&& args[2].type == JS_INTEGER) {
		switch(args[1].u.vinteger) {
		case 0:
			if(! PWM_is_inited(0)) {
				PWM_init(0);
			}
			PWM_out(0,args[2].u.vinteger);
			break;
		case 1:
			if(! PWM_is_inited(1)) {
				PWM_init(1);
			}
			PWM_out(1,args[2].u.vinteger);
			break;
		}
		result_return->u.vboolean = 1;
	}
}

static void
snd_global_method(JSVirtualMachine * vm, JSBuiltinInfo * builtin_info,
				  void *instance_context, JSNode * result_return, JSNode * args)
{
	result_return->type = JS_BOOLEAN;
	result_return->u.vboolean = 0;
	if (args->u.vinteger == 2
		&& args[1].type == JS_INTEGER
		&& args[1].u.vinteger >= 0
		&& args[1].u.vinteger < 2) {
		JSFloat f;
		if(args[2].type == JS_INTEGER) {
			f = (JSFloat)args[2].u.vinteger;
		} else if (args[2].type == JS_FLOAT) {
			f = args[2].u.vfloat;
		} else {
			return;
		}
		if(f == 0) {
			switch(args[1].u.vinteger) {
			case 0:
				SOUND_off(0);
				break;
			case 1:
				SOUND_off(1);
				break;
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
		{"pwm", pwm_global_method},
		{"snd", snd_global_method},
		{NULL, NULL}
	};

	for (i = 0; global_methods[i].name; i++) {
		JSBuiltinInfo *info;

		info = js_vm_builtin_info_create(vm);
		info->global_method_proc = global_methods[i].method;

		n = &vm->globals[js_vm_intern(vm, global_methods[i].name)];
		js_vm_builtin_create(vm, n, info, NULL);
	}
}
