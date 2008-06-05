/* jsconfig.h.  Generated automatically by configure.  */
/* jsconfig.h.in.  Generated automatically from configure.in by autoheader.  */

/* Define if on AIX 3.
   System headers sometimes define this.
   We just want to avoid a redefinition error message.  */
#ifndef _ALL_SOURCE
/* #undef _ALL_SOURCE */
#endif

/* Define if using alloca.c.  */
/* #undef C_ALLOCA */

/* Define to empty if the keyword does not work.  */
/* #undef const */

/* Define to one of _getb67, GETB67, getb67 for Cray-2 and Cray-YMP systems.
   This function is required for alloca.c support on those systems.  */
/* #undef CRAY_STACKSEG_END */

/* Define if you have alloca, as a function or macro.  */
/* #undef HAVE_ALLOCA */

/* Define if you have <alloca.h> and it should be used (not on Ultrix).  */
/* #undef HAVE_ALLOCA_H */

/* Define as __inline if that's what the C compiler calls it.  */
/* #undef inline */

/* If using the C implementation of alloca, define if you know the
   direction of stack growth for your system; otherwise it will be
   automatically deduced at run-time.
 STACK_DIRECTION > 0 => grows toward higher addresses
 STACK_DIRECTION < 0 => grows toward lower addresses
 STACK_DIRECTION = 0 => direction of growth unknown
 */
/* #undef STACK_DIRECTION */

/* Define if you have the ANSI C header files.  */
/* #undef STDC_HEADERS */

/*
 * Define the PACKAGE and VERSION only if they are undefined.  This means
 * that we do not redefine them, when the library is used in another
 * GNU like package that defines PACKAGE and VERSION.
 */

/* Package name. */
#ifndef PACKAGE
#define PACKAGE "js"
#endif /* no PACKAGE */

/* Version number. */
#ifndef VERSION
#define VERSION "0.2.5"
#endif /* no VERSION */

/* Are C prototypes supported. */
/* #undef PROTOTYPES */

/* Canonical host name and its parts. */
/* #undef CANONICAL_HOST */
/* #undef CANONICAL_HOST_CPU */
/* #undef CANONICAL_HOST_VENDOR */
/* #undef CANONICAL_HOST_OS */

/* Do we want to build all instruction dispatchers? */
/* #undef ALL_DISPATCHERS */

/* Do we want to profile byte-code operands. */
/* #undef PROFILING */

/* Do we want the byte-code operand hooks. */
/* #undef BC_OPERAND_HOOKS */

/*
 * Unconditionall disable the jumps byte-code instruction dispatch
 * method.
 */
/* #undef DISABLE_JUMPS */

/* Does the struct stat has st_blksize member? */
#define HAVE_STAT_ST_ST_BLKSIZE 1

/* Does the struct stat has st_blocks member? */
#define HAVE_STAT_ST_ST_BLOCKS 1

/* Does the asctime_r() function take three arguments. */
/* #undef ASCTIME_R_WITH_THREE_ARGS */

/* Does the drand48_r() work with DRAND48D data. */
/* #undef DRAND48_R_WITH_DRAND48D */

/* How the attribute structures are passed to the init functions. */
/* #undef CONDATTR_BY_VALUE */
/* #undef MUTEXATTR_BY_VALUE */
/* #undef THREADATTR_BY_VALUE */

/* JS */
/* #undef WITH_JS */

/* Curses. */
/* #undef WITH_CURSES */
/* #undef HAVE_CURSES_H */
/* #undef HAVE_NCURSES_H */

/* MD5 */
/* #undef WITH_MD5 */

/* The number of bytes in a int.  */
#if __AVR__ || __ICCAVR__
#define SIZEOF_INT 2
#else
#define SIZEOF_INT 4
#endif

/* The number of bytes in a long.  */
#define SIZEOF_LONG 4

/* Define if you have the drand48 function.  */
#define HAVE_DRAND48 1

/* Define if you have the lstat function.  */
#define HAVE_LSTAT 1

/* Define if you have the pthread_attr_create function.  */
/* #undef HAVE_PTHREAD_ATTR_CREATE */

/* Define if you have the pthread_attr_setscope function.  */
/* #undef HAVE_PTHREAD_ATTR_SETSCOPE */

/* Define if you have the pthread_attr_setstacksize function.  */
/* #undef HAVE_PTHREAD_ATTR_SETSTACKSIZE */

/* Define if you have the pthread_condattr_create function.  */
/* #undef HAVE_PTHREAD_CONDATTR_CREATE */

/* Define if you have the pthread_condattr_init function.  */
/* #undef HAVE_PTHREAD_CONDATTR_INIT */

/* Define if you have the pthread_mutexattr_create function.  */
/* #undef HAVE_PTHREAD_MUTEXATTR_CREATE */

/* Define if you have the sleep function.  */
#define HAVE_SLEEP 1

/* Define if you have the srand48 function.  */
#define HAVE_SRAND48 1

/* Define if you have the usleep function.  */
#define HAVE_USLEEP 1

/* Define if you have the <dlfcn.h> header file.  */
#define HAVE_DLFCN_H 1

/* Define if you have the <errno.h> header file.  */
#define HAVE_ERRNO_H 1

/* Define if you have the <float.h> header file.  */
#define HAVE_FLOAT_H 1

/* Define if you have the <limits.h> header file.  */
#define HAVE_LIMITS_H 1

/* Define if you have the <stdlib.h> header file.  */
#define HAVE_STDLIB_H 1

/* Define if you have the <string.h> header file.  */
#define HAVE_STRING_H 1

/* Define if you have the <unistd.h> header file.  */
#if __AVR__ || __ICCAVR__
/* #undef HAVE_UNISTD_H */
#else
#define HAVE_UNISTD_H 1
#endif

/* Define if don't remove runtime warning message formatted in sprintf */
#if __AVR__ || __ICCAVR__ || __H8300H__
/* #undef _RUNTIME_WARNING */
/* #undef JS_DEBUG_MEMORY_LEAKS */
#undef _ENABLE_STRING_REGEXP
#undef _ENABLE_STRING_CRC32
#undef _ENABLE_STRING_LOWERUPPER
#undef _ENABLE_STRING_PACKUNPACK
#else
#define _RUNTIME_WARNING 1
#define JS_DEBUG_MEMORY_LEAKS 1
#endif
