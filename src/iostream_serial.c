#ifdef __AVR__

#include "jsint.h"
#include "serial.h"

#define DEFAULT_BUFFER_SIZE 32

JSIOStream *js_iostream_new()
{
    JSIOStream *stream;

    stream = js_calloc(NULL, 1, sizeof(*stream));
    if (stream == NULL)
        return NULL;

    stream->buflen = DEFAULT_BUFFER_SIZE;
    stream->buffer = js_malloc(NULL, stream->buflen);
    if (stream->buffer == NULL) {
        js_free(stream);
        return NULL;
    }

    return stream;
}

static int serial_read(void *context, unsigned char *buffer, unsigned int todo, int *error_return)
{
	unsigned char nSerialPort = (unsigned char)context;
	unsigned char *p = buffer;

	int res;
	while(todo>0) {
		if((res = SERIAL_getchar(nSerialPort)) > 0) {
			*p = (unsigned char)res;
			p++;
			todo--;
		} else {
			break;
		}
	}
	return (p-buffer);
}


static int serial_write(void *context, unsigned char *buffer, unsigned int todo, int *error_return)
{
	unsigned char nSerialPort = (unsigned char)context;
	unsigned char *p = buffer;

    while (todo>0) {
        if (SERIAL_putchar(nSerialPort, *p) != MOXA_SUCCESS) {
			break;
        }
		p++;
		todo--;
    }
	return (p-buffer);
}

static void serial_close(void *context)
{
}

JSIOStream *js_iostream_serial(unsigned char nSerialPort, unsigned long nBaudrate)
{
    JSIOStream *stream;

    stream = js_iostream_new();
    if (stream == NULL)
        return NULL;

    stream->read = serial_read;
    stream->write = serial_write;

    stream->seek = NULL;
    stream->get_position = NULL;
    stream->get_length = NULL;
    stream->close = NULL;

    stream->context = nSerialPort;

	SERIAL_init(nSerialPort, nBaudrate);

    return stream;
}

#endif /* __AVR __ */
