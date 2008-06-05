#include "jsint.h"


/* ---------------------------------------------------------------------------------------------- */
/*
 * Global Method
 */

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

static void add_global_method(JSVirtualMachine * vm)
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

volatile JSVirtualMachine *s_vm = 0;

/* ---------------------------------------------------------------------------------------------- */
/*
 * Entry Point
 */

#ifdef __AVR__
extern void init_stdio();
#endif
#ifdef _PROTO1_RADIO
extern void init_builtin_radio();
#endif
extern JSByteCode *init_bytecode();
extern void init_builtin_hello_class();

int main()
{
#ifdef __AVR__
	init_stdio();
#endif							/* __AVR __ */

	JSIOStream *s_stdin = NULL;
	JSIOStream *s_stdout = NULL;
	JSIOStream *s_stderr = NULL;

#if !(__AVR__ || __ICCAVR__)
	s_stdin = js_iostream_file(stdin, 1, 0, 0);
	s_stdout = js_iostream_file(stdout, 0, 1, 0);
	s_stderr = js_iostream_file(stderr, 0, 1, 0);
#endif							/* not __AVR__ || __ICCAVR__ */

	JSVirtualMachine *vm;
	vm = js_vm_create(256, 1, 1, s_stdin, s_stdout, s_stderr);

	if (vm != NULL) {
		s_vm = vm;
		JSByteCode *bc;

		bc = init_bytecode();

		add_global_method(vm);
		init_builtin_hello_class(vm);

#ifdef _PROTO1_RADIO
		init_builtin_radio(vm);
#endif
		vm->enable_interrupt = 1;
		js_vm_execute(vm, bc);

		js_bc_free(bc);
		s_vm = 0;
		js_vm_destroy(vm);

#if JS_DEBUG_MEMORY_LEAKS
		js_alloc_dump_blocks();
#endif							/* JS_DEBUG_MEMORY_LEAKS */

	}
#ifdef __AVR__
	while (1) {
		asm("sleep");
	}
#endif

	return 0;
}
