#include "jsint.h"

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

void init_builtin_hello_class(JSVirtualMachine * vm)
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
