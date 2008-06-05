#include <avr/io.h>
#include <stdio.h>

#ifdef _MOXA_SERIAL
#include "serial.h"
#endif							/* _MOXA_SERIAL */

static int serial_stdio_putchar(char c, FILE * stream) {
#ifdef _MOXA_SERIAL
	SERIAL_putchar(1, c);
#else
	loop_until_bit_is_set(UCSR1A, UDRE);
	UDR1 = c;
#endif
	return 0;
}

static int serial_stdio_getchar(FILE * stream) {
#ifdef _MOXA_SERIAL
	return SERIAL_getchar(1);
#else
	loop_until_bit_is_set(UCSR1A, RXC);
	return (int) UDR1;
#endif
}

static FILE serial_stdio = FDEV_SETUP_STREAM(serial_stdio_putchar, serial_stdio_getchar, _FDEV_SETUP_RW);

void init_stdio() {
#ifdef _MOXA_SERIAL
	SERIAL_init(1, 9600);
#else							/* not _MOXA_SERIAL */
	UBRR1L = 51 & 0xff;			// 9600bps, 8Mhz
	UBRR1H = 51 >> 8;
	UCSR1A = 0x00;
	UCSR1B = 0x18;				// no interrupt, allow to send, recv
	UCSR1C = 0x06;
#endif							/* _MOXA_SERIAL */
	stdin = stderr = stdout = &serial_stdio;
}
