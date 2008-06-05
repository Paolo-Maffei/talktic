#include "jsint.h"
#include "radio.h"

#define RADIO_CHANNEL 11
#define RADIO_PANID   0x2420
#define RADIO_ADDRESS 0x0002

extern volatile JSVirtualMachine *s_vm;

static void send_global_method(JSVirtualMachine * vm, JSBuiltinInfo * builtin_info,
					 void *instance_context, JSNode * result_return, JSNode * args)
{
	if (args->u.vinteger == 2) {
		if (args[1].type == JS_INTEGER && args[2].type == JS_STRING) {
			unsigned short addr = args[1].u.vinteger;
			RADIO_sendPacket(addr, args[2].u.vstring->data, args[2].u.vstring->len);
		}
	}
	result_return->type = JS_UNDEFINED;
}

static int receiveVMHandler(JSVirtualMachine * vm, void *data)
{
	RADIO_PACKET_RX_INFO *pRRI = (RADIO_PACKET_RX_INFO *) data;
	JSNode argv[6];
	argv[0].type = JS_INTEGER;
	argv[0].u.vinteger = 5;
	argv[1].type = JS_INTEGER;
	argv[1].u.vinteger = pRRI->seqNumber;
	argv[2].type = JS_INTEGER;
	argv[2].u.vinteger = pRRI->srcAddr;
	argv[3].type = JS_INTEGER;
	argv[3].u.vinteger = pRRI->srcPanId;
	js_vm_make_string(vm, &argv[4], pRRI->pPayload, pRRI->nLength);
	argv[5].type = JS_INTEGER;
	argv[5].u.vinteger = pRRI->rssi;
	js_vm_apply(vm, "onr", NULL, 6, argv);
	js_free(data);
	return 0;
}

static MRESULT receiveHandler(RADIO_PACKET_RX_INFO * pRRI)
{
	if (s_vm) {
		if (!(s_vm->interrupt_table[0].fired)) {
			void *data;
			if (data = js_malloc(s_vm, sizeof(RADIO_PACKET_RX_INFO))) {
				memcpy(data, pRRI, sizeof(RADIO_PACKET_RX_INFO));
				s_vm->interrupt_table[0].data = data;
				s_vm->interrupt_table[0].fired = 1;
			}
		}
	}
	return 0;
}

void init_builtin_radio(JSVirtualMachine *vm) {
	JSBuiltinInfo *info;
	JSNode *n;

	info = js_vm_builtin_info_create(vm);
	info->global_method_proc = send_global_method;
	n = &vm->globals[js_vm_intern(vm, "srd")];
	js_vm_builtin_create(vm, n, info, NULL);

	RADIO_init(RADIO_CHANNEL, RADIO_PANID, RADIO_ADDRESS, 31);
	RADIO_setRecvHandler(&receiveHandler);
	vm->interrupt_table[0].handler = receiveVMHandler;
	vm->interrupt_table[0].enable = 1;
}
