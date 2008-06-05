#include "jsint.h"

JSVirtualMachine *s_vm = 0;

#ifdef _PROTO1
extern void init_stdio();
#endif
#ifdef _PROTO1_RADIO
extern void init_builtin_radio();
#endif
#ifdef _PROTO1_DIGITALIO
extern void init_builtin_digitalio();
#endif
#ifdef _PROTO1_ANALOGIO
extern void init_builtin_analogio();
#endif

#ifdef _AKI3068NET_NET
extern void init_builtin_net_class();
#endif

extern JSByteCode *init_bytecode();
extern void init_builtin_globals();
extern void init_builtin_hello_class();

int main()
{
	JSVirtualMachine *vm;

#ifdef _PROTO1
	init_stdio();
#endif

#ifdef JS_IOSTREAM
	JSIOStream *s_stdin, *s_stdout, *s_stderr;
	s_stdin = js_iostream_file(stdin, 1, 0, 0);
	s_stdout = js_iostream_file(stdout, 0, 1, 0);
	s_stderr = js_iostream_file(stderr, 0, 1, 0);

	vm = js_vm_create(256, 1, 1, s_stdin, s_stdout, s_stderr);
#else
	vm = js_vm_create(256, 1, 1);
#endif


	if (vm != NULL) {
		s_vm = vm;
		JSByteCode *bc;

		bc = init_bytecode();

		init_builtin_globals(vm);
		init_builtin_hello_class(vm);

#ifdef _PROTO1_RADIO
		init_builtin_radio(vm);
#endif
#ifdef _PROTO1_DIGITALIO
		init_builtin_digitalio(vm);
#endif
#ifdef _PROTO1_ANALOGIO
		init_builtin_analogio(vm);
#endif
#ifdef _AKI3068NET_NET
		init_builtin_net_class(vm);
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

#if _PROTO1 && __AVR__
	while (1) {
		__asm__ __volatile__ ("sleep"::);
	}
#endif

	return 0;
}
