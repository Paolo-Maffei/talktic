#include <cyg/hal/var_arch.h>
#include "jsint.h"
#include "reg_macro.h"

static void
pinMode_global_method(JSVirtualMachine * vm, JSBuiltinInfo * builtin_info,
				  void *instance_context, JSNode * result_return, JSNode * args)
{
	JSInt32 pin;
	int mode;

	result_return->type = JS_BOOLEAN;
	result_return->u.vboolean = 0;

	if (args->u.vinteger == 2) {
		pin = js_vm_to_int32(vm, &args[1]);
		mode = js_vm_to_boolean(vm, &args[2]);
		switch(pin) {
		case 0:
			REG_WRITE(CYGARC_PADDR, 0, mode);
			break;
		case 1:
			REG_WRITE(CYGARC_PADDR, 1, mode);
			break;
		case 2:
			REG_WRITE(CYGARC_PADDR, 2, mode);
			break;
		case 3:
			REG_WRITE(CYGARC_PADDR, 3, mode);
			break;
		case 4:
			REG_WRITE(CYGARC_PADDR, 4, mode);
			break;
		case 5:
			REG_WRITE(CYGARC_PADDR, 5, mode);
			break;
		case 6:
			REG_WRITE(CYGARC_PADDR, 6, mode);
			break;
		case 7:
			REG_WRITE(CYGARC_PADDR, 7, mode);
			break;
		default:
			return;
		}
		result_return->u.vboolean = 1;
	}
}

static void
digitalWrite_global_method(JSVirtualMachine * vm, JSBuiltinInfo * builtin_info,
				  void *instance_context, JSNode * result_return, JSNode * args)
{
	JSInt32 pin;
	int mode;

	result_return->type = JS_BOOLEAN;
	result_return->u.vboolean = 0;

	if (args->u.vinteger == 2) {
		pin = js_vm_to_int32(vm, &args[1]);
		mode = js_vm_to_boolean(vm, &args[2]);
		switch(pin) {
		case 0:
			REG_WRITE(CYGARC_PADR, 0, mode);
			break;
		case 1:
			REG_WRITE(CYGARC_PADR, 1, mode);
			break;
		case 2:
			REG_WRITE(CYGARC_PADR, 2, mode);
			break;
		case 3:
			REG_WRITE(CYGARC_PADR, 3, mode);
			break;
		case 4:
			REG_WRITE(CYGARC_PADR, 4, mode);
			break;
		case 5:
			REG_WRITE(CYGARC_PADR, 5, mode);
			break;
		case 6:
			REG_WRITE(CYGARC_PADR, 6, mode);
			break;
		case 7:
			REG_WRITE(CYGARC_PADR, 7, mode);
			break;
		default:
			return;
		}
		result_return->u.vboolean = 1;
	}
}

static void
digitalRead_global_method(JSVirtualMachine * vm, JSBuiltinInfo * builtin_info,
				  void *instance_context, JSNode * result_return, JSNode * args)
{
	JSInt32 pin;

	result_return->type = JS_BOOLEAN;
	result_return->u.vboolean = 0;

	if (args->u.vinteger == 1) {
		pin = js_vm_to_int32(vm, &args[1]);
		switch(pin) {
		case 0:
			result_return->u.vboolean = REG_READ(CYGARC_PADR, 0);
			break;
		case 1:
			result_return->u.vboolean = REG_READ(CYGARC_PADR, 1);
			break;
		case 2:
			result_return->u.vboolean = REG_READ(CYGARC_PADR, 2);
			break;
		case 3:
			result_return->u.vboolean = REG_READ(CYGARC_PADR, 3);
			break;
		case 4:
			result_return->u.vboolean = REG_READ(CYGARC_PADR, 4);
			break;
		case 5:
			result_return->u.vboolean = REG_READ(CYGARC_PADR, 5);
			break;
		case 6:
			result_return->u.vboolean = REG_READ(CYGARC_PADR, 6);
			break;
		case 7:
			result_return->u.vboolean = REG_READ(CYGARC_PADR, 7);
			break;
		default:
			return;
		}
	}
}

void init_builtin_digitalio(JSVirtualMachine *vm) {
	JSBuiltinInfo *info;
	JSNode *n;
	unsigned char i;

	struct {
		char *name;
		JSBuiltinGlobalMethod method;
	} global_methods[] = {
		{"pinMode", pinMode_global_method},
		{"digitalWrite", digitalWrite_global_method},
		{"digitalRead", digitalRead_global_method},
		{NULL, NULL}
	};

	for (i = 0; global_methods[i].name; i++) {
		info = js_vm_builtin_info_create(vm);
		info->global_method_proc = global_methods[i].method;

		n = &vm->globals[js_vm_intern(vm, global_methods[i].name)];
		js_vm_builtin_create(vm, n, info, NULL);
	}
}
