#include "jsint.h"

#ifdef __AVR__

#include <avr/io.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>
//#include "serial.h"

#define F_CPU 8000000
#include "delay.h"

#else							/* __AVR__ */

#define EEMEM

#endif							/* not __AVR__ */



#include "bytecode.h"

/* Linker Option Memo
 * Allocate heap to ext. memory
 *   -Wl,--defsym=__heap_start=0x801100,--defsym=__heap_end=0x8090FF
 * Allocate .data and .bss and heap to ext. memory
 *   -Wl,-Tdata=0x801100,--defsym=__heap_end=0x80ffff
 */

/* ---------------------------------------------------------------------------------------------- */
/*
 * Global Method
 */
/*
static void
trace_global_method(JSVirtualMachine * vm, JSBuiltinInfo * builtin_info,
                    void *instance_context, JSNode * result_return,
                    JSNode * args)
{
#ifdef __AVR__
	PORTB = 0b10010000;
#endif
    result_return->type = JS_UNDEFINED;
}

void add_global_method(JSVirtualMachine * vm)
{
    int i;
    JSNode *n;

    struct {
        char *name;
        JSBuiltinGlobalMethod method;
    } global_methods[] = {
        {
        "trace", trace_global_method}, {
        NULL, NULL}
    };

    for (i = 0; global_methods[i].name; i++) {
        JSBuiltinInfo *info;

        info = js_vm_builtin_info_create(vm);
        info->global_method_proc = global_methods[i].method;

        n = &vm->globals[js_vm_intern(vm, global_methods[i].name)];
        js_vm_builtin_create(vm, n, info, NULL);
    }
}
*/

/* ---------------------------------------------------------------------------------------------- */
/*
 * Class Define
 */

typedef struct hello_ctx_st {
	JSSymbol s_show;
	JSSymbol s_msg;
} HelloCtx;

static int hello_class_method(JSVirtualMachine * vm, JSBuiltinInfo * builtin_info,
							  void *instance_context, JSSymbol method, JSNode * result_return,
							  JSNode * args)
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
hello_class_property(JSVirtualMachine * vm, JSBuiltinInfo * builtin_info, void *instance_context,
					 JSSymbol property, int set, JSNode * node)
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

static void hello_class_new_proc(JSVirtualMachine * vm, JSBuiltinInfo * builtin_info, JSNode * args,
								 JSNode * result_return)
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

void add_hello_class(JSVirtualMachine * vm)
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
/*
 * Bytecode Reading from EEPROM
 */

#ifdef __AVR__

#define JS_BC_EEPROM_READ_INT32(cp, var) \
    (var) = eeprom_read_byte(cp); \
    (var) <<= 8; \
    (var) |= eeprom_read_byte(cp+1); \
    (var) <<= 8; \
    (var) |= eeprom_read_byte(cp+2); \
    (var) <<= 8; \
    (var) |= eeprom_read_byte(cp+3)

#define JS_BC_EEPROM_READ_INT16(cp, var) \
    (var) = eeprom_read_byte(cp); \
    (var) <<= 8; \
    (var) |= eeprom_read_byte(cp+1)

#define JS_BC_EEPROM_READ_INT8(cp, var) \
    (var) = eeprom_read_byte(cp)

JSByteCode *js_bc_read_eeprom(unsigned char *data)
{
	JSUInt32 ui = 0;
	JSUInt8 ub = 0;
	unsigned int pos = 0;
	int i, j;
	JSByteCode *bc = NULL;

	while (!eeprom_is_ready()) {
	};

	pos += 4;

	bc = js_calloc(NULL, 1, sizeof(*bc));
	if (bc == NULL)
		return NULL;

	JS_BC_EEPROM_READ_INT32(data + pos, ui);
	bc->num_sects = (unsigned int) ui;
	pos += 4;

	bc->sects = js_calloc(NULL, bc->num_sects, sizeof(JSBCSect));
	if (bc->sects == NULL) {
		js_free(bc);
		return NULL;
	}

	/* Read sections. */
	for (i = 0; i < bc->num_sects; i++) {
		/* Get type. */
		JS_BC_EEPROM_READ_INT32(data + pos, ui);
		bc->sects[i].type = (int) ui;
		pos += 4;

		/* Get section length. */
		JS_BC_EEPROM_READ_INT32(data + pos, ui);
		bc->sects[i].length = (unsigned int) ui;
		pos += 4;

		bc->sects[i].data = js_malloc(NULL, bc->sects[i].length + 1
									  /* +1 to avoid zero allocations */ );
		if (bc->sects[i].data == NULL) {
			for (i--; i >= 0; i--)
				js_free(bc->sects[i].data);

			js_free(bc->sects);
			js_free(bc);
			return NULL;
		}

		for (j = 0; j < bc->sects[i].length; j++) {
			JS_BC_EEPROM_READ_INT8(data + pos + j, ub);
			*(JSUInt8 *) (bc->sects[i].data + j) = ub;
		}
		pos += bc->sects[i].length;
	}
	return bc;
}
#endif							/* __AVR__ */

/* ---------------------------------------------------------------------------------------------- */
/*
 * STDIN/OUT handler for Serial
 */
#ifdef __AVR__

static int serial_stdio_putchar(char c, FILE * stream)
{
//  SERIAL_putchar(0, c);
	while (!(UCSR0A & (1 << UDRE)));
	UDR0 = c;
	return 0;
}

static int serial_stdio_getchar(FILE * stream)
{
//  return SERIAL_getchar(0);
	return 0;
}

static FILE serial_stdio = FDEV_SETUP_STREAM(serial_stdio_putchar, serial_stdio_getchar,
											 _FDEV_SETUP_RW);

#endif							/* __AVR__ */


/* ---------------------------------------------------------------------------------------------- */

static JSVirtualMachine *s_vm = 0;

#ifdef __AVR__
ISR(SIG_INTERRUPT5)
{
	if(s_vm) {
		js_vm_apply(s_vm, "test", NULL, 0, NULL);
	}
}
#endif

/* ---------------------------------------------------------------------------------------------- */
/*
 * Entry Point
 */
#ifdef __H8300H__
//#include <lwip/sys.h>
//#include <lwip/sockets.h>
//#include <lwip/inet.h>
#include <lwip/api.h>
#endif

int main()
{
#ifdef __H8300H__
	lwip_init();

	printf("wait...\n");
	while(1) {
		u32_t a = netif_default->ip_addr.addr;
		if(a) {
			printf("ip_addr %d.%d.%d.%d\n",
				((a >> 24) & 0xff), ((a >> 16) & 0xff), ((a >> 8) & 0xff), (a & 0xff));
			break;
		}
	}

	{
		char httpreq[] = "GET /\r\n\r\n";
		struct netconn *conn;
		struct ip_addr addr;
		struct netbuf *buf;
		void *data;
		u16_t len;
		char char_buf[256];

		conn = netconn_new(NETCONN_TCP);
		IP4_ADDR(&addr, 133, 27, 4, 127); // www.sfc.keio.ac.jp
		netconn_connect(conn, &addr, 80);
		printf("connect\n");
		netconn_write(conn, httpreq, sizeof(httpreq), NETCONN_COPY);
		printf("write\n");
		while((buf = netconn_recv(conn)) != NULL) {
			do {
				netbuf_data(buf, &data, &len);
				memcpy(char_buf, data, len < 256 ? len : 256);
				printf(char_buf);
			} while(netbuf_next(buf) >= 0);
		}
		netconn_close(conn);
		printf("close\n");
		netconn_delete(conn);
	}
#endif

#ifdef __AVR__
	/* enable extrenal ram */
	MCUCR |= (1 << SRE);
	XMCRA = 0x00;
	XMCRB |= (1 << XMM0);
	DDRB = 0b10010000;
	PORTB = 0b00000000;

//  ENABLE_GLOBAL_INT();
//  SERIAL_init(0, 9600);
	UBRR0L = 51 & 0xff;			// 9600bps, 8Mhz
	UBRR0H = 51 >> 8;
	UCSR0A = 0x00;
	UCSR0B = 0x18;				// äÑÇËçûÇ›Ç»ÇµëóéÛêMãñâ¬
	UCSR0C = 0x06;

	// enable interrupt 5 on up edge
	EICRB |= (1 << 2) | (1 << 3);
	EIMSK |= (1 << 5);

	stdin = &serial_stdio;
	stderr = stdout = &serial_stdio;
#endif

	JSIOStream *s_stdin = NULL;
	JSIOStream *s_stdout = NULL;
	JSIOStream *s_stderr = NULL;

#if !(__AVR__ || __ICCAVR__)
	s_stdin = js_iostream_file(stdin, 1, 0, 0);
	s_stdout = js_iostream_file(stdout, 0, 1, 0);
	s_stderr = js_iostream_file(stderr, 0, 1, 0);
#endif

	JSVirtualMachine *vm;
	vm = js_vm_create(128, JS_VM_DISPATCH_SWITCH_BASIC, 1, 1, s_stdin, s_stdout, s_stderr);
	if (vm != NULL) {
		s_vm = vm;
		JSByteCode *bc;

#ifdef __AVR__
		bc = js_bc_read_eeprom(0x00);
#else
		bc = js_bc_read_data(_bytecode, _bytecode_size);
#endif

//      add_global_method(vm);
		add_hello_class(vm);

#ifdef __AVR__
		sei();
#endif
		js_vm_execute(vm, bc);

		js_bc_free(bc);
		s_vm = 0;
		js_vm_destroy(vm);

#if JS_DEBUG_MEMORY_LEAKS
		js_alloc_dump_blocks();
#endif

	}
#ifdef __AVR__
	while (1) {
		asm("sleep");
	}
#endif

	return 0;
}
