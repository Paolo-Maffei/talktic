#include "jsint.h"
#include "radio.h"

extern JSVirtualMachine *s_vm;

static void radioSend_global_method(JSVirtualMachine * vm, JSBuiltinInfo * builtin_info,
					 void *instance_context, JSNode * result_return, JSNode * args)
{
	JSNode n;
	result_return->type = JS_BOOLEAN;
	result_return->u.vboolean = 0;

	if (args->u.vinteger == 2) {
		js_vm_to_string(vm, &args[2], &n);
		if(RADIO_sendPacket((unsigned short)js_vm_to_int32(vm, &args[1]),
			n.u.vstring->data, n.u.vstring->len) == MOXA_SUCCESS) {
			result_return->u.vboolean = 1;
		}
	}
}

static int onRadioReceive_global_vm_interrupt(JSVirtualMachine * vm, void *data)
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

	js_vm_apply(vm, "onRadioReceive", NULL, 6, argv);
	js_free(data);

	return 0;
}

static MRESULT receiveHandler(RADIO_PACKET_RX_INFO * pRRI)
{
	if (s_vm) {
		if (!(s_vm->interrupt_table[0].fired)) {
			void *data;
			if ((data = js_malloc(s_vm, sizeof(RADIO_PACKET_RX_INFO))) != NULL) {
				memcpy(data, pRRI, sizeof(RADIO_PACKET_RX_INFO));
				s_vm->interrupt_table[0].data = data;
				s_vm->interrupt_table[0].fired = 1;
			}
		}
	}
	return 0;
}

static void radioInit_global_method(JSVirtualMachine * vm, JSBuiltinInfo * builtin_info,
					 void *instance_context, JSNode * result_return, JSNode * args)
{
	UINT8 channel = 11;
	UINT8 powerAmpLevel = 31;

	result_return->type = JS_BOOLEAN;
	result_return->u.vboolean = 0;

	if (args->u.vinteger >= 2) {
		if(args->u.vinteger >= 3) {
			channel = (UINT8)js_vm_to_int32(vm, &args[3]);
		}
		if(args->u.vinteger >= 4) {
			powerAmpLevel = (UINT8)js_vm_to_int32(vm, &args[4]);
		}
		RADIO_init(channel, (WORD)js_vm_to_int32(vm, &args[1]), (WORD)js_vm_to_int32(vm, &args[2]), powerAmpLevel);
		RADIO_setRecvHandler(&receiveHandler);
		vm->interrupt_table[0].enable = 1;

		result_return->u.vboolean = 1;
	}
}

void init_builtin_radio(JSVirtualMachine *vm) {
	JSBuiltinInfo *info;
	JSNode *n;
	unsigned char i;

	struct {
		char *name;
		JSBuiltinGlobalMethod method;
	} global_methods[] = {
		{"radioInit", radioInit_global_method},
		{"radioSend", radioSend_global_method},
		{NULL, NULL}
	};

	for (i = 0; global_methods[i].name; i++) {
		info = js_vm_builtin_info_create(vm);
		info->global_method_proc = global_methods[i].method;

		n = &vm->globals[js_vm_intern(vm, global_methods[i].name)];
		js_vm_builtin_create(vm, n, info, NULL);
	}

	n = &vm->globals[js_vm_intern(vm, "RADIO_BROADCAST")];
	n->type = JS_INTEGER;
	n->u.vinteger = 0xffff;

	vm->interrupt_table[0].handler = onRadioReceive_global_vm_interrupt;
}
