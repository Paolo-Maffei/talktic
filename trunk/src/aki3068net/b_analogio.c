#include <cyg/hal/var_arch.h>
#include "jsint.h"
#include "reg_macro.h"

// for H8/3069F
// wrong values are defined in cyg/hal/mod_regs_adc.h included from cyg/ha/var_arch.h
#undef CYGARC_DADR0
#define CYGARC_DADR0  0xFFFF9C
#undef CYGARC_DADR1
#define CYGARC_DADR1  0xFFFF9D
#undef CYGARC_DACR
#define CYGARC_DACR   0xFFFF9E

static void
analogRead_global_method(JSVirtualMachine * vm, JSBuiltinInfo * builtin_info,
				  void *instance_context, JSNode * result_return, JSNode * args)
{
	unsigned int val = 0;
	JSInt32 pin;

	result_return->type = JS_FLOAT;
	result_return->u.vfloat = 0;

	if (args->u.vinteger == 1) {
		pin = js_vm_to_int32(vm, &args[1]);
		if(pin<0 || pin>7) {
			return;
		}

		// select adc port
		REG(CYGARC_ADCSR) = pin & 0x07;
		// start adc
		REG_WRITE(CYGARC_ADCSR, 5, 1);
		// wait until adc end
		while(! REG_READ(CYGARC_ADCSR, 7));

		// read result
		switch(pin) {
		case 0:
		case 4:
			val = (REG(CYGARC_ADDRAH)<<2)+(REG(CYGARC_ADDRAL)>>6);
			break;
		case 1:
		case 5:
			val = (REG(CYGARC_ADDRBH)<<2)+(REG(CYGARC_ADDRBL)>>6);
			break;
		case 2:
		case 6:
			val = (REG(CYGARC_ADDRCH)<<2)+(REG(CYGARC_ADDRCL)>>6);
			break;
		case 3:
		case 7:
			val = (REG(CYGARC_ADDRDH)<<2)+(REG(CYGARC_ADDRDL)>>6);
			break;
		}

		// 10bit adc
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
			d = (n.u.vfloat * 0xff);
		} else {
			return;
		}

		switch(pin) {
		case 0:
			REG_WRITE(CYGARC_DACR, 6, 1);
			REG(CYGARC_DADR0) = d;
			break;
		case 1:
			REG_WRITE(CYGARC_DACR, 7, 1);
			REG(CYGARC_DADR1) = d;
			break;
		default:
			return;
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
		{NULL, NULL}
	};

	for (i = 0; global_methods[i].name; i++) {
		info = js_vm_builtin_info_create(vm);
		info->global_method_proc = global_methods[i].method;

		n = &vm->globals[js_vm_intern(vm, global_methods[i].name)];
		js_vm_builtin_create(vm, n, info, NULL);
	}
}
