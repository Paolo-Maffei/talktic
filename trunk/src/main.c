#include "jsint.h"

#ifdef __AVR__
#include <avr/io.h>
#include <avr/interrupt.h>
#endif							/* __AVR__ */

/* ---------------------------------------------------------------------------------------------- */
/*
 * Global Method
 */

#if JS_DEBUG_MEMORY_LEAKS
static void
dump_global_method(JSVirtualMachine * vm, JSBuiltinInfo * builtin_info,
				   void *instance_context, JSNode * result_return, JSNode * args)
{
	js_alloc_dump_blocks();
	result_return->type = JS_UNDEFINED;
}
#endif							/* JS_DEBUG_MEMORY_LEAKS */

#ifdef __AVR__

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

#ifdef _MOXA
static void
led_global_method(JSVirtualMachine * vm, JSBuiltinInfo * builtin_info,
				  void *instance_context, JSNode * result_return, JSNode * args)
{
	unsigned char pin = 0;
	if (args->u.vinteger == 2 && args[1].type == JS_INTEGER && args[2].type == JS_BOOLEAN) {
		switch (args[1].u.vinteger) {
		case 1:
			pin = 4;
			break;
		case 2:
			pin = 7;
			break;
		}
		if (pin && args[2].u.vboolean) {
			PORTB |= (1 << pin);
		} else {
			PORTB &= ~(1 << pin);
		}
	}
	result_return->type = JS_UNDEFINED;
}
#endif							/* _MOXA */

#endif							/* __AVR__ */

static void add_global_method(JSVirtualMachine * vm)
{
	int i;
	JSNode *n;

	struct {
		char *name;
		JSBuiltinGlobalMethod method;
	} global_methods[] = {
#if JS_DEBUG_MEMORY_LEAKS
		{"dump", dump_global_method},
#endif							/* JS_DEBUG_MEMORY_LEAKS */
#ifdef __AVR__
		{"sei", sei_global_method},
#ifdef _MOXA
		{"led", led_global_method},
#endif							/* _MOXA */
#endif							/* __AVR__ */
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


/* ---------------------------------------------------------------------------------------------- */
/*
 * Class Define
 */

typedef struct hello_ctx_st {
	JSSymbol s_show;
	JSSymbol s_msg;
} HelloCtx;

static int hello_class_method(JSVirtualMachine * vm,
							  JSBuiltinInfo * builtin_info,
							  void *instance_context, JSSymbol method,
							  JSNode * result_return, JSNode * args)
{
	HelloCtx *ctx = builtin_info->obj_context;
	if (method == ctx->s_show) {
		printf(instance_context);
	} else {
		return JS_PROPERTY_UNKNOWN;
	}
	return JS_PROPERTY_FOUND;
}

static int
hello_class_property(JSVirtualMachine * vm, JSBuiltinInfo * builtin_info,
					 void *instance_context, JSSymbol property, int set, JSNode * node)
{
	HelloCtx *ctx = builtin_info->obj_context;

	if (instance_context && property == ctx->s_msg) {
		if (set)
			return 0;
		js_vm_make_string(vm, node, instance_context, strlen(instance_context));
	} else {
		if (!set)
			node->type = JS_UNDEFINED;
		return JS_PROPERTY_UNKNOWN;
	}
	return JS_PROPERTY_FOUND;
}

static void hello_class_new_proc(JSVirtualMachine * vm,
								 JSBuiltinInfo * builtin_info,
								 JSNode * args, JSNode * result_return)
{
	char *ictx;
	if (args->u.vinteger == 1) {
		if (args[1].type == JS_STRING) {
			int len = args[1].u.vstring->len;
			if ((ictx = js_malloc(vm, len + 1)) != NULL) {
				memcpy(ictx, args[1].u.vstring->data, len);
				ictx[len] = '\0';
				js_vm_builtin_create(vm, result_return, builtin_info, ictx);
				return;
			}
		}
	}
	js_vm_error(vm);
}

static void hello_class_delete_proc(JSBuiltinInfo * builtin_info, void *instance_context)
{
	if (instance_context) {
		js_free(instance_context);
	}
}

static void add_hello_class(JSVirtualMachine * vm)
{
	HelloCtx *ctx;
	JSNode *n;
	JSBuiltinInfo *info;

	ctx = js_calloc(vm, 1, sizeof(*ctx));
	ctx->s_show = js_vm_intern(vm, "show");
	ctx->s_msg = js_vm_intern(vm, "msg");

	info = js_vm_builtin_info_create(vm);
	info->method_proc = hello_class_method;
	info->property_proc = hello_class_property;
	info->new_proc = hello_class_new_proc;
	info->delete_proc = hello_class_delete_proc;
	info->obj_context = ctx;
	info->obj_context_delete = js_free;

	n = &vm->globals[js_vm_intern(vm, "Hello")];
	js_vm_builtin_create(vm, n, info, NULL);
}



/* ---------------------------------------------------------------------------------------------- */

volatile JSVirtualMachine *s_vm = 0;

#ifdef _MOXA
/*
static int interrupt5VMHandler(JSVirtualMachine * vm, void *data)
{
	printf("interrupt5");
	js_vm_apply(vm, "onDigitalIO", NULL, 0, NULL);
	return 0;
}

ISR(SIG_INTERRUPT5)
{
	if (s_vm) {
		if (!(s_vm->interrupt_table[1].fired)) {
			s_vm->interrupt_table[1].fired = 1;
		}
	}
}
*/
/*
ISR(SIG_INTERRUPT4)
{
	if (s_vm) {
		js_vm_apply(s_vm, "onDigitalIo2", NULL, 0, NULL);
	}
}
*/
#endif							/* _MOXA */

/* ---------------------------------------------------------------------------------------------- */
/*
 * Entry Point
 */

#ifdef __AVR__
extern void init_stdio();
extern void init_builtin_radio();
#endif
extern JSByteCode *init_bytecode();

int main()
{
#ifdef __AVR__
#ifdef _MOXA
	DDRB |= (1 << 7) | (1 << 4);
//  PORTB &= ~((1 << 7) | (1 << 4));
	PORTB |= (1 << 7) | (1 << 4);
/*
	// enable interrupt 5 on up edge
	EICRB |= (1 << 2) | (1 << 3);
	EIMSK |= (1 << 5);
	EICRB |= (1 << 0) | (1 << 1);
	EIMSK |= (1 << 4);
	sei();
*/
#endif							/* _MOXA */
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
		add_hello_class(vm);

#ifdef _MOXA_RADIO
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
