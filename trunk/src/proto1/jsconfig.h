/* Define if you have the ANSI C header files.  */
/* #undef STDC_HEADERS */

/* Do we want to profile byte-code operands. */
/* #undef JS_PROFILING */

/* Do we want the byte-code operand hooks. */
/* #undef BC_OPERAND_HOOKS */

/*
 * Unconditionall disable the jumps byte-code instruction dispatch
 * method.
 */
/* #undef DISABLE_JUMPS */

/* The number of bytes in a int.  */
#define SIZEOF_INT 2

/* The number of bytes in a long.  */
#define SIZEOF_LONG 4

/* Define if you have the <errno.h> header file.  */
#define HAVE_ERRNO_H 1

/* Define if you have the <float.h> header file.  */
#define HAVE_FLOAT_H 1

/* Define if you have the <stdlib.h> header file.  */
#define HAVE_STDLIB_H 1

/* Define if you have the <string.h> header file.  */
#define HAVE_STRING_H 1

/* Define if you have the <unistd.h> header file.  */
/* #undef HAVE_UNISTD_H */

/* Define if don't remove runtime warning message formatted in sprintf */
/* #undef JS_RUNTIME_DEBUG */
/* #undef JS_RUNTIME_WARNING */
/* #undef JS_DEBUG_MEMORY_LEAKS */
/* #undef JS_ENABLE_STRING_LOWERUPPER */
/* #undef JS_ENABLE_STRING_PACKUNPACK */

/* vm.c */
#define GC_TRIGGER 1024L
