#include <avr/io.h>
#include <stdio.h>

#define BAUD_REG 51		// 9600bps
#define _(a,b) a##1##b	// define port number


#ifdef _PROTO1_MOXA_SERIAL
#include "serial.h"
#endif							/* _PROTO1_MOXA_SERIAL */

static int serial_stdio_putchar(char c, FILE * stream) {
#ifdef _PROTO1_MOXA_SERIAL
	SERIAL_putchar(UART, c);
#else
	loop_until_bit_is_set(_(UCSR,A), UDRE);
	_(UDR,) = c;
#endif
	return 0;
}

static int serial_stdio_getchar(FILE * stream) {
#ifdef _PROTO1_MOXA_SERIAL
	return SERIAL_getchar(UART);
#else
	loop_until_bit_is_set(_(UCSR,A), RXC);
	return (int) _(UDR,);
#endif
}

static FILE serial_stdio = FDEV_SETUP_STREAM(serial_stdio_putchar, serial_stdio_getchar, _FDEV_SETUP_RW);

void init_stdio() {
#ifdef _PROTO1_MOXA_SERIAL
	SERIAL_init(UART, BAUD_RATE);
#else							/* not _PROTO1_MOXA_SERIAL */
	_(UBRR,L) = BAUD_REG & 0xff;			// 9600bps, 8Mhz
	_(UBRR,H) = BAUD_REG >> 8;
	_(UCSR,A) = 0x00;
	_(UCSR,B) = 0x18;				// no interrupt, allow to send, recv
	_(UCSR,C) = 0x06;
#endif							/* _PROTO1_MOXA_SERIAL */
	stdin = stderr = stdout = &serial_stdio;
}
