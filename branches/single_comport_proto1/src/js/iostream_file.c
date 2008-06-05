/*
 * I/O streams.
 * Copyright (c) 1998 New Generation Software (NGS)
 *
 * Author: Markku Rossi <mtr@ngs.fi>
 */

/*
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
 * MA 02111-1307, USA
 */

#include "jsint.h"

#ifdef JS_IOSTREAM

/* The `FILE *' stream. */
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


static int file_seek(void *context, long offset, int whence)
{
    return fseek((FILE *) context, offset, whence);
}


static long file_get_position(void *context)
{
    return ftell((FILE *) context);
}


static long file_get_length(void *context)
{
    FILE *fp = (FILE *) context;
    long cpos;
    long result = -1;

    // Save current position.
    cpos = ftell(fp);
    if (cpos >= 0) {
        // Seek to the end of the file.
        if (fseek(fp, 0, SEEK_END) >= 0) {
            // Fetch result.
            result = ftell(fp);

            // Seek back.
            if (fseek(fp, cpos, SEEK_SET) < 0)
                // Couldn't revert the fp to the original position.
                result = -1;
        }
    }

    return result;
}

static void file_close(void *context)
{
    fclose((FILE *) context);
}

JSIOStream *js_iostream_file(FILE * fp, int readp, int writep, int do_close)
{
    JSIOStream *stream;

    if (fp == NULL)
        return NULL;

    stream = js_iostream_new();
    if (stream == NULL)
        return NULL;

    if (readp)
        stream->read = file_read;
    if (writep)
        stream->write = file_write;

    stream->seek = file_seek;
    stream->get_position = file_get_position;
    stream->get_length = file_get_length;

    if (do_close)
        stream->close = file_close;

    stream->context = fp;

    return stream;
}

#endif
