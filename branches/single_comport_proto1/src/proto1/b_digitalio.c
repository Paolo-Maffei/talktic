#include "jsint.h"
#include "device_port.h"
#include "pwm.h"
#include <avr/io.h>

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
			DEVICE_PORT_DIR0_(mode);
			DEVICE_PORT_OUT0_(0);
			break;
		case 1:
			DEVICE_PORT_DIR1_(mode);
			DEVICE_PORT_OUT1_(0);
			break;
		case 2:
			DEVICE_PORT_DIR2_(mode);
			DEVICE_PORT_OUT2_(0);
			break;
		case 3:
			DEVICE_PORT_DIR3_(mode);
			DEVICE_PORT_OUT3_(0);
			break;
		case 4:
			DEVICE_PORT_DIR4_(mode);
			DEVICE_PORT_OUT4_(0);
			break;
		case 5:
			DEVICE_PORT_DIR5_(mode);
			DEVICE_PORT_OUT5_(0);
			break;
		case 6:
			DEVICE_PORT_DIR6_(mode);
			DEVICE_PORT_OUT6_(0);
			break;
		case 7:
			DEVICE_PORT_DIR7_(mode);
			DEVICE_PORT_OUT7_(0);
			break;
		default:
			return;
		}
		result_return->u.vboolean = 1;
	}
}

unsigned char device_port_out(unsigned char pin, unsigned char mode) {
	switch(pin) {
	case 0:
		DEVICE_PORT_OUT0_(mode);
		break;
	case 1:
		DEVICE_PORT_OUT1_(mode);
		break;
	case 2:
		DEVICE_PORT_OUT2_(mode);
		break;
	case 3:
		DEVICE_PORT_OUT3_(mode);
		break;
	case 4:
		DEVICE_PORT_OUT4_(mode);
		break;
	case 5:
		DEVICE_PORT_OUT5_(mode);
		break;
	case 6:
		DEVICE_PORT_OUT6_(mode);
		break;
	case 7:
		DEVICE_PORT_OUT7_(mode);
		break;
	default:
		return 1;
	}
	return 0;
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
		if(device_port_out(pin, mode)) {
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
