#include "jsint.h"

static void
sei_global_method(JSVirtualMachine * vm, JSBuiltinInfo * builtin_info,
				  void *instance_context, JSNode * result_return, JSNode * args)
{
	if (args->u.vinteger == 1 && args[1].type == JS_BOOLEAN) {
		if (args[1].u.vboolean) {
			vm->enable_interrupt = 1;
		} else {
			vm->enable_interrupt = 0;
		}
	}
	result_return->type = JS_UNDEFINED;
}

#if JS_DEBUG_MEMORY_LEAKS
static void
dump_global_method(JSVirtualMachine * vm, JSBuiltinInfo * builtin_info,
				   void *instance_context, JSNode * result_return, JSNode * args)
{
	js_alloc_dump_blocks();
	result_return->type = JS_UNDEFINED;
}
#endif							/* JS_DEBUG_MEMORY_LEAKS */

void init_builtin_globals(JSVirtualMachine * vm)
{
	int i;
	JSNode *n;

	struct {
		char *name;
		JSBuiltinGlobalMethod method;
	} global_methods[] = {
		{"sei", sei_global_method},
#if JS_DEBUG_MEMORY_LEAKS
		{"dump", dump_global_method},
#endif							/* JS_DEBUG_MEMORY_LEAKS */
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
