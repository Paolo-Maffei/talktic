/*
 * alternative for js/iostream.c
 */

#include "jsint.h"

size_t js_iostream_write(JSIOStream * stream, void *ptr, size_t size) {
    return 0;
}

int js_iostream_close(JSIOStream * stream) {
	return 0;
}
