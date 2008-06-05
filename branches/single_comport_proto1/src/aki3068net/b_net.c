#include "jsint.h"
#include <lwip/api.h>

extern JSVirtualMachine *s_vm;
static unsigned char http_request_flag = 0;

static void
httpRequest_global_method(JSVirtualMachine * vm, JSBuiltinInfo * builtin_info,
				  void *instance_context, JSNode * result_return, JSNode * args)
{
	result_return->type = JS_BOOLEAN;
	result_return->u.vboolean = 0;
	if (args->u.vinteger == 2) {
	}
}

static void
netInit_global_method(JSVirtualMachine * vm, JSBuiltinInfo * builtin_info,
				  void *instance_context, JSNode * result_return, JSNode * args)
{
	lwip_init();
	while(1) {
		u32_t a = netif_default->ip_addr.addr;
		if (a) {
			printf("ip_addr %d.%d.%d.%d\n", ((a >> 24) & 0xff), ((a >> 16) & 0xff), ((a >> 8) & 0xff), (a & 0xff));
			break;
		}
	}
	result_return->type = JS_INTEGER;
	result_return->u.vinteger = netif_default->ip_addr.addr;
}

void init_builtin_net(JSVirtualMachine * vm)
{
	JSBuiltinInfo *info;
	JSNode *n;
	unsigned char i;

	struct {
		char *name;
		JSBuiltinGlobalMethod method;
	} global_methods[] = {
		{"netInit", netInit_global_method},
		{NULL, NULL}
	};

	for (i = 0; global_methods[i].name; i++) {
		info = js_vm_builtin_info_create(vm);
		info->global_method_proc = global_methods[i].method;

		n = &vm->globals[js_vm_intern(vm, global_methods[i].name)];
		js_vm_builtin_create(vm, n, info, NULL);
	}
}
