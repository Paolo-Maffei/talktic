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

/* The number of bytes in a types  */
#define SIZEOF_INT 4
#define SIZEOF_LONG 4
#define SIZEOF_FLOAT 4
#define SIZEOF_DOUBLE 8

/* Define if you have the <errno.h> header file.  */
#define HAVE_ERRNO_H 1

/* Define if you have the <float.h> header file.  */
#define HAVE_FLOAT_H 1

/* Define if you have the <stdlib.h> header file.  */
#define HAVE_STDLIB_H 1

/* Define if you have the <string.h> header file.  */
#define HAVE_STRING_H 1

/* Define if you have the <unistd.h> header file.  */
#define HAVE_UNISTD_H 1

/* Define if don't remove runtime warning message formatted in sprintf */
#define JS_RUNTIME_DEBUG 1
#define JS_PROFILING 1
#define JS_RUNTIME_WARNING 1
#define JS_DEBUG_MEMORY_LEAKS 1
#define JS_ENABLE_STRING_LOWERUPPER
#define JS_ENABLE_STRING_PACKUNPACK