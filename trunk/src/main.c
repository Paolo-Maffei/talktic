#include "jsint.h"

volatile JSVirtualMachine *s_vm = 0;

#ifdef __AVR__
extern void init_stdio();
#endif
#ifdef _PROTO1_RADIO
extern void init_builtin_radio();
#endif
extern JSByteCode *init_bytecode();
extern void init_builtin_globals();
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

		init_builtin_globals(vm);
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
