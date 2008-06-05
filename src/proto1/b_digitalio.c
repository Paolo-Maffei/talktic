#include "jsint.h"
#include "device_port.h"
#include <avr/io.h>

static void
dpi_global_method(JSVirtualMachine * vm, JSBuiltinInfo * builtin_info,
				  void *instance_context, JSNode * result_return, JSNode * args)
{
	result_return->type = JS_BOOLEAN;
	result_return->u.vboolean = 0;
	if (args->u.vinteger == 2
		&& args[1].type == JS_INTEGER
		&& args[1].u.vinteger > 0
		&& args[1].u.vinteger < 8
		&& args[2].type == JS_BOOLEAN) {
		switch(args[1].u.vinteger) {
		case 0:
			DEVICE_PORT_DIR0_(args[2].u.vboolean);
			DEVICE_PORT_OUT0_(0);
			break;
		case 1:
			DEVICE_PORT_DIR1_(args[2].u.vboolean);
			DEVICE_PORT_OUT1_(0);
			break;
		case 2:
			DEVICE_PORT_DIR2_(args[2].u.vboolean);
			DEVICE_PORT_OUT2_(0);
			break;
		case 3:
			DEVICE_PORT_DIR3_(args[2].u.vboolean);
			DEVICE_PORT_OUT3_(0);
			break;
		case 4:
			DEVICE_PORT_DIR4_(args[2].u.vboolean);
			DEVICE_PORT_OUT4_(0);
			break;
		case 5:
			DEVICE_PORT_DIR5_(args[2].u.vboolean);
			DEVICE_PORT_OUT5_(0);
			break;
		case 6:
			DEVICE_PORT_DIR6_(args[2].u.vboolean);
			DEVICE_PORT_OUT6_(0);
			break;
		case 7:
			DEVICE_PORT_DIR7_(args[2].u.vboolean);
			DEVICE_PORT_OUT7_(0);
			break;
		}
		result_return->u.vboolean = 1;
	}
}

static void
dps_global_method(JSVirtualMachine * vm, JSBuiltinInfo * builtin_info,
				  void *instance_context, JSNode * result_return, JSNode * args)
{
	result_return->type = JS_BOOLEAN;
	result_return->u.vboolean = 0;
	if (args->u.vinteger == 2
		&& args[1].type == JS_INTEGER
		&& args[1].u.vinteger >= 0
		&& args[1].u.vinteger < 8
		&& args[2].type == JS_BOOLEAN) {
		switch(args[1].u.vinteger) {
		case 0:
			DEVICE_PORT_OUT0_(args[2].u.vboolean);
			break;
		case 1:
			DEVICE_PORT_OUT1_(args[2].u.vboolean);
			break;
		case 2:
			DEVICE_PORT_OUT2_(args[2].u.vboolean);
			break;
		case 3:
			DEVICE_PORT_OUT3_(args[2].u.vboolean);
			break;
		case 4:
			DEVICE_PORT_OUT4_(args[2].u.vboolean);
			break;
		case 5:
			DEVICE_PORT_OUT5_(args[2].u.vboolean);
			break;
		case 6:
			DEVICE_PORT_OUT6_(args[2].u.vboolean);
			break;
		case 7:
			DEVICE_PORT_OUT7_(args[2].u.vboolean);
			break;
		}
		result_return->u.vboolean = 1;
	}
}

static void
dpg_global_method(JSVirtualMachine * vm, JSBuiltinInfo * builtin_info,
				  void *instance_context, JSNode * result_return, JSNode * args)
{
	result_return->type = JS_BOOLEAN;
	result_return->u.vboolean = 0;
	if (args->u.vinteger == 1
		&& args[1].type == JS_INTEGER
		&& args[1].u.vinteger >= 0
		&& args[1].u.vinteger < 8) {
		switch(args[1].u.vinteger) {
		case 0:
			result_return->u.vboolean = DEVICE_PORT_INP0;
			break;
		case 1:
			result_return->u.vboolean = DEVICE_PORT_INP1;
			break;
		case 2:
			result_return->u.vboolean = DEVICE_PORT_INP2;
			break;
		case 3:
			result_return->u.vboolean = DEVICE_PORT_INP3;
			break;
		case 4:
			result_return->u.vboolean = DEVICE_PORT_INP4;
			break;
		case 5:
			result_return->u.vboolean = DEVICE_PORT_INP5;
			break;
		case 6:
			result_return->u.vboolean = DEVICE_PORT_INP6;
			break;
		case 7:
			result_return->u.vboolean = DEVICE_PORT_INP7;
			break;
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
		{"dpi", dpi_global_method},
		{"dps", dps_global_method},
		{"dpg", dpg_global_method},
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
