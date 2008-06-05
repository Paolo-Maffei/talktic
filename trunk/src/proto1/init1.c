#include <avr/io.h>

void init1 (void) __attribute__ ((naked)) __attribute__ ((section (".init1")));
void init1 (void) {
	// Enable external memory
	MCUCR |= (1 << SRE);
	XMCRA = 0x00;
	XMCRB |= (1 << XMM0);
}
