#include "jsint.h"

static int file_read(void *context, unsigned char *buffer, unsigned int todo, int *error_return)
{
    int got;

    errno = 0;
    got = fread(buffer, 1, todo, (FILE *) context);
    *error_return = errno;

    return got;
}


static int file_write(void *context, unsigned char *buffer, unsigned int todo, int *error_return)
{
    int wrote;

    errno = 0;
    wrote = fwrite(buffer, 1, todo, (FILE *) context);
    *error_return = errno;

    return wrote;
}

JSIOStream *js_iostream_file(FILE * fp, int readp, int writep, int do_close)
{
    JSIOStream *stream;

    stream = js_iostream_new();
    if (stream == NULL)
        return NULL;

    stream->read = file_read;
    stream->write = file_write;

    stream->seek = NULL;
    stream->get_position = NULL;
    stream->get_length = NULL;
    stream->close = NULL;

    stream->context = fp;

    return stream;
}
