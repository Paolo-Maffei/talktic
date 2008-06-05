#include "jsint.h"

JSVirtualMachine *s_vm = 0;

#ifdef _PROTO1
extern void boot();
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
#ifdef _PROTO1_SERIAL
extern void init_builtin_serial();
#endif

#ifdef _AKI3068NET_NET
extern void init_builtin_net();
#endif
#ifdef _AKI3068NET_DIGITALIO
extern void init_builtin_digitalio();
#endif
#ifdef _AKI3068NET_ANALOGIO
extern void init_builtin_analogio();
#endif

extern JSByteCode *init_bytecode();
extern void init_builtin_globals();
extern void init_builtin_hello_class();

int main()
{
	JSVirtualMachine *vm;

#ifdef _PROTO1
	boot();
	init_stdio();
#endif

#ifdef JS_IOSTREAM
	JSIOStream *s_stdin, *s_stdout, *s_stderr;
	s_stdin = js_iostream_file(stdin, 1, 0, 0);
	s_stdout = js_iostream_file(stdout, 0, 1, 0);
	s_stderr = js_iostream_file(stderr, 0, 1, 0);
#define JS_VM_CREATE_IOSTREAM , s_stdin, s_stdout, s_stderr
#else
#define JS_VM_CREATE_IOSTREAM
#endif

#ifdef JS_RUNTIME_WARNING
#define JS_VM_CREATE_VERBOSE , 9
#else
#define JS_VM_CREATE_VERBOSE
#endif
#ifdef JS_RUNTIME_DEBUG
#define JS_VM_CREATE_STACKTRACE , 1
#else
#define JS_VM_CREATE_STACKTRACE
#endif

	vm = js_vm_create(
		256
		JS_VM_CREATE_VERBOSE
		JS_VM_CREATE_STACKTRACE
		JS_VM_CREATE_IOSTREAM
	);

	if (vm != NULL) {
		s_vm = vm;
		JSByteCode *bc;

		bc = init_bytecode();

		init_builtin_globals(vm);
		init_builtin_hello_class(vm);

#ifdef _PROTO1_RADIO
		init_builtin_radio(vm);
#endif
#ifdef _PROTO1_SERIAL
		init_builtin_serial(vm);
#endif
#ifdef _PROTO1_DIGITALIO
		init_builtin_digitalio(vm);
#endif
#ifdef _PROTO1_ANALOGIO
		init_builtin_analogio(vm);
#endif

#ifdef _AKI3068NET_NET
		init_builtin_net(vm);
#endif
#ifdef _AKI3068NET_DIGITALIO
		init_builtin_digitalio(vm);
#endif
#ifdef _AKI3068NET_ANALOGIO
		init_builtin_analogio(vm);
#endif

		vm->enable_interrupt = 1;
		printf("exit=%d\r\n", js_vm_execute(vm, bc));

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
