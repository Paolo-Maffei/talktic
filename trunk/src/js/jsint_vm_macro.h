/*
 * General VM macros.
 */

/* STACKFRAME */

#define JS_SP0          sp
#define JS_SP1          (sp + 1)
#define JS_SP2          (sp + 2)
#define JS_SP(n)        (sp + (n))

#define JS_LOCAL(n)     (fp - 4 - (n))
#define JS_ARG(n)       (fp + 1 + (n))

#define JS_WITHPTR      (fp - 2)
#define JS_ARGS_FIXP    (fp - 1)

#define JS_PUSH()       sp--
#define JS_POP()        sp++
#define JS_POP_N(n)     sp += (n)

#define JS_COPY(to, from) \
    do { \
        (to)->type = (from)->type; \
        (to)->u.copy.a = (from)->u.copy.a; \
        (to)->u.copy.b = (from)->u.copy.b; \
    } while (0)

#define JS_CONST(n)    (&vm->consts[(n)])
#define JS_GLOBAL(n)   (&vm->globals[(n)])

#define JS_SAVE_REGS() \
    do { \
        vm->sp = sp; \
        vm->pc = pc; \
    } while (0)

#ifdef _RUNTIME_WARNING

#define JS_CALL_HOOK(event) \
    do { \
        int hook_result; \
 \
        if (vm->hook) \
            if ((hook_result = (*vm->hook) ((event), vm->hook_context)) != 0) { \
                JS_SAVE_REGS (); \
                sprintf (vm->error, "hook break %d", hook_result); \
                js_vm_error (vm); \
                /* NOTREACHED */ \
            } \
    } while (0)

#define JS_VM_ALLOCATE_FD(vm, where) \
    do { \
        if ((vm)->fd_count == 0) { \
            sprintf ((vm)->error, "%s: no more file descriptors allowed", (where)); \
            js_vm_error (vm); \
        } \
        (vm)->fd_count--; \
    } while (0)

#else /* not _RUNTIME_WARNING */

#define JS_CALL_HOOK(event) \
    do { \
        int hook_result; \
 \
        if (vm->hook) \
            if ((hook_result = (*vm->hook) ((event), vm->hook_context)) != 0) { \
                JS_SAVE_REGS (); \
                js_vm_error (vm); \
                /* NOTREACHED */ \
            } \
    } while (0)

#define JS_VM_ALLOCATE_FD(vm, where) \
    do { \
        if ((vm)->fd_count == 0) { \
            js_vm_error (vm); \
        } \
        (vm)->fd_count--; \
    } while (0)

#endif /* not _RUNTIME_WARNING */

#define JS_VM_FREE_FD(vm) \
    do { \
        (vm)->fd_count++; \
    } while (0)

#define JS_MAYBE_GC() \
    do { \
        if (vm->gc.bytes_allocated >= vm->gc.trigger) { \
            js_vm_garbage_collect (vm, fp, sp); \
            JS_CALL_HOOK (JS_VM_EVENT_GARBAGE_COLLECT); \
        } \
    } while (0)

#define JS_IS_TRUE(n) \
    ((n)->type > JS_INTEGER \
        || ((n)->type == JS_BOOLEAN && (n)->u.vboolean) \
        || ((n)->type == JS_INTEGER && (n)->u.vinteger))

#define JS_IS_FALSE(n) \
    ((n)->type < JS_BOOLEAN \
        || ((n)->type == JS_BOOLEAN && !(n)->u.vboolean) \
        || ((n)->type == JS_INTEGER && !(n)->u.vinteger))

#define JS_RESERVE_STACK_FOR_FUNCTION 10

#define JS_SUBROUTINE_CALL(function) \
    do { \
        /* Check that we have enought space in the stack. */ \
        if (sp - JS_RESERVE_STACK_FOR_FUNCTION < vm->stack) \
            ERROR ("stack overflow"); \
 \
        /* STACKFRAME */ \
 \
        /* Save frame pointer. */ \
        JS_SP0->type = JS_IPTR; \
        JS_SP0->u.iptr = fp; \
 \
        /* Update fp. */ \
        fp = JS_SP0; \
        JS_PUSH (); \
 \
        /* Insert an empty args_fix. */ \
        JS_SP0->type = JS_ARGS_FIX; \
        JS_SP0->u.args_fix.argc = 0; \
        JS_SP0->u.args_fix.delta = 0; \
        JS_PUSH (); \
 \
        /* Insert empty with pointer. */ \
        JS_SP0->type = JS_IPTR; \
        JS_SP0->u.iptr = NULL; \
        JS_PUSH (); \
 \
        /* Save return address. */ \
        JS_SP0->type = JS_IPTR; \
        JS_SP0->u.iptr = pc; \
        JS_PUSH (); \
 \
        /* And finally, jump to the method code. */ \
        CALL_USER_FUNC ((function)); \
    } while (0)

#define JS_OPERAND_CMP_REL(_OP_) \
    do { \
        if (JS_SP2->type == JS_STRING && JS_SP1->type == JS_STRING) { \
            JS_SP2->u.vboolean = js_compare_strings (JS_SP2, JS_SP1) _OP_ 0; \
            JS_SP2->type = JS_BOOLEAN; \
            JS_POP (); \
        } else if (JS_SP2->type == JS_INTEGER && JS_SP1->type == JS_INTEGER) { \
            JS_SP2->u.vboolean = JS_SP2->u.vinteger _OP_ JS_SP1->u.vinteger; \
            JS_SP2->type = JS_BOOLEAN; \
            JS_POP (); \
        } else { \
            JSNode l, r; \
 \
            /* Do it the hard way. */ \
            switch (JS_SP2->type) { \
            case JS_INTEGER: \
            case JS_FLOAT: \
            case JS_NAN: \
                JS_COPY (&l, JS_SP2); \
                break; \
 \
            default: \
                js_vm_to_number (vm, JS_SP2, &l); \
                break; \
            } \
 \
            switch (JS_SP1->type) { \
            case JS_INTEGER: \
            case JS_FLOAT: \
            case JS_NAN: \
                JS_COPY (&r, JS_SP1); \
                break; \
 \
            default: \
                js_vm_to_number (vm, JS_SP1, &r); \
                break; \
            } \
 \
            /* Do the comparison. */ \
            JS_POP (); \
 \
            if (l.type == JS_NAN || r.type == JS_NAN) \
                JS_SP1->type = JS_UNDEFINED; \
            else if (l.type == JS_INTEGER && r.type == JS_INTEGER) { \
                JS_SP1->type = JS_BOOLEAN; \
                JS_SP1->u.vboolean = l.u.vinteger _OP_ r.u.vinteger; \
            } else { \
                double ld, rd; \
 \
                if (l.type == JS_FLOAT) \
                    ld = l.u.vfloat; \
                else \
                    ld = (double) l.u.vinteger; \
 \
                if (r.type == JS_FLOAT) \
                    rd = r.u.vfloat; \
                else \
                    rd = (double) r.u.vinteger; \
 \
                JS_SP1->type = JS_BOOLEAN; \
                JS_SP1->u.vboolean = ld _OP_ rd; \
            } \
        } \
    } while (0)

#define JS_OPERAND_CMP_EQ(_OP_, _VAL_) \
    while (1) { \
        int res; \
        if (JS_SP2->type == JS_SP1->type) { \
            /* Comparsion between same types. */ \
            switch (JS_SP2->type) { \
            case JS_INTEGER: \
                res = JS_SP2->u.vinteger _OP_ JS_SP1->u.vinteger; \
                break; \
            case JS_STRING: \
                res = js_compare_strings (JS_SP2, JS_SP1) _OP_ 0; \
                break; \
            case JS_FLOAT: \
                res = JS_SP2->u.vfloat _OP_ JS_SP1->u.vfloat; \
                break; \
            case JS_NAN: \
                /* 11.9.3: cases 5 and 6 */ \
                res = !_VAL_; \
                break; \
            case JS_BOOLEAN: \
                res = JS_SP2->u.vboolean _OP_ JS_SP1->u.vboolean; \
                break; \
            case JS_OBJECT: \
                res = JS_SP2->u.vobject _OP_ JS_SP1->u.vobject; \
                break; \
            case JS_BUILTIN: \
                res = ((JS_SP2->u.vbuiltin->info == JS_SP1->u.vbuiltin->info \
                    && (JS_SP2->u.vbuiltin->instance_context == JS_SP1->u.vbuiltin->instance_context)) \
                    ? _VAL_ : !_VAL_); \
                break; \
            case JS_FUNC: \
                res = JS_SP2->u.vfunction _OP_ JS_SP1->u.vfunction; \
                break; \
            case JS_SYMBOL: \
                res = JS_SP2->u.vsymbol _OP_ JS_SP1->u.vsymbol; \
                break; \
            case JS_IPTR: \
                res = JS_SP2->u.iptr _OP_ JS_SP1->u.iptr; \
                break; \
            default: \
                res = _VAL_; \
                break; \
            } \
        } else { \
            /* Type conversions between different types. */ \
 \
            if ((JS_SP2->type == JS_UNDEFINED || JS_SP2->type == JS_NULL) \
                && (JS_SP1->type == JS_UNDEFINED || JS_SP1->type == JS_NULL)) \
                res = _VAL_; \
 \
            /* Numbers. */ \
            else if (JS_IS_NUMBER (JS_SP2) && JS_IS_NUMBER (JS_SP1)) { \
                if (JS_SP2->type == JS_NAN || JS_SP1->type == JS_NAN) \
                    /* 11.9.3: cases 5 and 6 */ \
                    res = !_VAL_; \
                else if (JS_SP2->type == JS_INTEGER) \
                    /* Integer-integer was already handled. */ \
                    res = (double) JS_SP2->u.vinteger _OP_ JS_SP1->u.vfloat; \
                else \
                    /* Integer-integer was already handled. */ \
                    res = JS_SP2->u.vfloat _OP_ (double) JS_SP1->u.vinteger; \
            } else { \
                JSNode l, r; \
 \
                /* Must perform type casts. */ \
 \
                if ((JS_SP2->type == JS_STRING || JS_SP2->type == JS_BOOLEAN || JS_IS_NUMBER (JS_SP2)) \
                    && (JS_SP1->type == JS_STRING || JS_SP1->type == JS_BOOLEAN || JS_IS_NUMBER (JS_SP1))) {\
                    js_vm_to_number (vm, JS_SP2, &l); \
                    js_vm_to_number (vm, JS_SP1, &r); \
 \
                    if (l.type == JS_NAN || r.type == JS_NAN) \
                        res = !_VAL_; \
                    else if (l.type == JS_INTEGER) { \
                        if (r.type == JS_INTEGER) \
                            res = l.u.vinteger _OP_ r.u.vinteger; \
                        else \
                            res = (double) l.u.vinteger _OP_ r.u.vfloat; \
                    } else { \
                        if (r.type == JS_INTEGER) \
                            res = l.u.vfloat _OP_ (double) r.u.vinteger; \
                        else \
                            res = l.u.vfloat _OP_ r.u.vfloat; \
                    } \
                } else if (JS_SP2->type == JS_OBJECT \
                    && (JS_SP1->type == JS_STRING || JS_IS_NUMBER (JS_SP1))) { \
                    JSNode cvt; \
 \
                    /* ECMA 11.9.3 21. No preferred type specified. */ \
                    js_vm_to_primitive (vm, JS_SP2, &cvt, JS_UNDEFINED); \
                    JS_COPY (JS_SP2, &cvt); \
                    continue; \
                } else if (JS_SP1->type == JS_OBJECT \
                    && (JS_SP2->type == JS_STRING || JS_IS_NUMBER (JS_SP2))) { \
                    JSNode cvt; \
 \
                    /* ECMA 11.9.3 20. No preferred type specified. */ \
                    js_vm_to_primitive (vm, JS_SP1, &cvt, JS_UNDEFINED); \
                    JS_COPY (JS_SP1, &cvt); \
                    continue; \
                } else \
                    res = !_VAL_; \
            } \
        } \
 \
        JS_SP2->type = JS_BOOLEAN; \
        JS_SP2->u.vboolean = res; \
        JS_POP (); \
        break; \
    }

#define JS_OPERAND_CMP_SEQ(_OP_, _VAL_) \
    do { \
        int res; \
        if (JS_SP2->type == JS_SP1->type) { \
            switch (JS_SP2->type) { \
            case JS_INTEGER: \
                res = JS_SP2->u.vinteger _OP_ JS_SP1->u.vinteger; \
                break; \
 \
            case JS_FLOAT: \
                res = JS_SP2->u.vfloat _OP_ JS_SP1->u.vfloat; \
                break; \
 \
            case JS_NAN: \
                /* 11.9.6: cases 3 and 4 */ \
                res = !_VAL_; \
                break; \
 \
            case JS_STRING: \
                res = js_compare_strings (JS_SP2, JS_SP1) _OP_ 0; \
                break; \
 \
            case JS_BOOLEAN: \
                res = JS_SP2->u.vboolean _OP_ JS_SP1->u.vboolean; \
                break; \
 \
            case JS_OBJECT: \
                res = JS_SP2->u.vobject _OP_ JS_SP1->u.vobject; \
                break; \
 \
            case JS_BUILTIN: \
                res = ((JS_SP2->u.vbuiltin->info == JS_SP1->u.vbuiltin->info \
                    && (JS_SP2->u.vbuiltin->instance_context == JS_SP1->u.vbuiltin->instance_context)) \
                    ? _VAL_ : !_VAL_); \
                break; \
 \
            case JS_FUNC: \
                res = JS_SP2->u.vfunction _OP_ JS_SP1->u.vfunction; \
                break; \
 \
            default: \
                /* 11.9.6: case 12 */ \
                res = !_VAL_; \
                break; \
            } \
        } else { \
            /* Only numbers are allowed here. */ \
            if (JS_IS_NUMBER (JS_SP2) && JS_IS_NUMBER (JS_SP1)) \
            { \
                if (JS_SP2->type == JS_NAN || JS_SP1->type == JS_NAN) \
                    /* 11.9.6: cases 3 and 4 */ \
                    res = !_VAL_; \
                else if (JS_SP2->type == JS_INTEGER) \
                    res = (double) JS_SP2->u.vinteger _OP_ JS_SP1->u.vfloat; \
                else \
                    res = JS_SP2->u.vfloat _OP_ (double) JS_SP1->u.vinteger; \
            } else \
                res = !_VAL_; \
        } \
 \
        JS_SP2->type = JS_BOOLEAN; \
        JS_SP2->u.vboolean = res; \
        JS_POP (); \
 \
    } while (0)

#define JS_OPERAND_BINARY(_OP_) \
    do { \
        if (JS_SP2->type == JS_INTEGER && JS_SP1->type == JS_INTEGER) { \
            JS_SP2->u.vinteger = ((JSInt32) JS_SP2->u.vinteger \
                _OP_ (JSInt32) JS_SP1->u.vinteger); \
            JS_POP (); \
        } else { \
            JSInt32 l, r; \
 \
            l = js_vm_to_int32 (vm, JS_SP2); \
            r = js_vm_to_int32 (vm, JS_SP1); \
 \
            JS_SP2->u.vinteger = (l _OP_ r); \
            JS_SP2->type = JS_INTEGER; \
            JS_POP (); \
        } \
    } while (0)

#define JS_IS_NUMBER(n) \
    ((n)->type == JS_INTEGER || (n)->type == JS_FLOAT || (n)->type == JS_NAN)



