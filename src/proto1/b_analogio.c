#include "jsint.h"
#include "device_ad.h"
#include <avr/io.h>

void init_builtin_analogio(JSVirtualMachine *vm) {
	JSBuiltinInfo *info;
	JSNode *n;
	unsigned char i;

	struct {
		char *name;
		JSBuiltinGlobalMethod method;
	} global_methods[] = {
//		{"dpi", dpi_global_method},
//		{"dps", dps_global_method},
//		{"dpg", dpg_global_method},
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
