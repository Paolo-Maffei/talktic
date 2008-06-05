#include <avr/io.h>
#include <avr/eeprom.h>

#define BAUD_RATE 9600		// impossible at 115200bps at 8Mhz
#define BAUD_REG  (F_CPU/(BAUD_RATE*8L)-1)

#define HW_VER    0x02
#define SW_MAJOR  0x01
#define SW_MINOR  0x0f

#define SIG1      0x1E
#define SIG2      0x97
#define SIG3      0x02

typedef union address_union {
	uint16_t word;
	uint8_t  byte[2];
} address_t;

typedef union length_union {
	uint16_t word;
	uint8_t  byte[2];
} length_t;

typedef struct flags_struct {
	unsigned eeprom : 1;
	unsigned rampz  : 1;
} flags_t;

char rs_buff(void) {
	return (UCSR1A & _BV(RXC1));
}

void rs_putc(char ch) {
	while (!(UCSR1A & _BV(UDRE1)));
	UDR1 = ch;
}

char getch(void) {
	while(!(UCSR1A & _BV(RXC1)));
	return UDR1;
}

void getNch(uint8_t count) {
	uint8_t i;
	for(i=0;i<count;i++) {
		while(!(UCSR1A & _BV(RXC1)));
		UDR1;
	}
}

void byte_response(uint8_t val) {
	if (getch() == ' ') {
		rs_putc(0x14);
		rs_putc(val);
		rs_putc(0x10);
	}
}

void nothing_response(void) {
	if (getch() == ' ') {
		rs_putc(0x14);
		rs_putc(0x10);
	}
}

/* Onboard LED is connected to pin PB7 */
#define LED_DDR   DDRB
#define LED_PORT  PORTB
#define LED_PIN   PINB
#define LED       PINB7
#define cbi(addr,bit)			addr&=~_BV(bit)
#define sbi(addr,bit)			addr|=_BV(bit)

inline void blink() {
	uint32_t l;
	cbi(LED_PORT,LED);
	for(l=0; l<700000; ++l);
	sbi(LED_PORT,LED);
	for(l=0; l<7000000; ++l);
}

void end() {
	blink();

	UBRR1L = 0;
	UBRR1H = 0;
	UCSR1A = 0x20;
	UCSR1B = 0;
	UCSR1C = 0x06;
}

void boot()
{
	uint8_t ch, ch2;
	uint16_t w;
	uint32_t l;
	address_t address;
	length_t length;
	flags_t flags;
	uint8_t buff[256];

	UBRR1H = BAUD_REG >> 8;
	UBRR1L = (uint8_t)BAUD_REG;
	UCSR1A |= _BV(U2X1);
	UCSR1B |= _BV(TXEN1)|_BV(RXEN1);
	UCSR1C |= _BV(UCSZ11)|_BV(UCSZ10);

	sbi(LED_DDR,LED);
	sbi(LED_PORT,LED);

	ch2 = 0;
	for (w=0; w<25; ++w) {
		for(l=0; l<3000000; ++l);
		if (rs_buff()) {
			ch2 = 1;
			break;
		}
	}

	if(ch2 == 0) {
		end();
		return;
	}

	blink();
	blink();

	while(1) {
		if (rs_buff()) {
			ch = getch();

			// Hello is anyone home?
			if(ch == '0') {
				nothing_response();
			}

			// Request programmer ID
			// Yes i've heard of the switch statement, a bunch of else if's -> smaller code
			else if(ch == '1') {
				if (getch() == ' ') {
					// Not using PROGMEM string due to boot block in m128 being beyond 64kB boundry
					// Would need to selectively manipulate RAMPZ, and it's only 9 characters anyway so who cares.
					rs_putc(0x14);
					rs_putc('A');
					rs_putc('V');
					rs_putc('R');
					rs_putc(' ');
					rs_putc('I');
					rs_putc('S');
					rs_putc('P');
					rs_putc(0x10);
				}
			}

			// AVR ISP/STK500 board commands  DON'T CARE so default nothing_response
			else if(ch == '@') {
				ch2 = getch();
				if (ch2>0x85) {
					getch();
				}
				nothing_response();
			}

			// AVR ISP/STK500 board requests
			else if(ch=='A') {
				ch2 = getch();
				if(ch2==0x80)
					byte_response(HW_VER);		// Hardware version
				else if(ch2==0x81)
					byte_response(SW_MAJOR);	// Software major version
				else if(ch2==0x82)
					byte_response(SW_MINOR);	// Software minor version
				else if(ch2==0x98)
					byte_response(0x03);		// Unknown but seems to be required by avr studio 3.56
				else
					byte_response(0x00);		// Covers various unnecessary responses we don't care about
			}

			// Device Parameters  DON'T CARE, DEVICE IS FIXED
			else if(ch=='B') {
				getNch(20);
				nothing_response();
			}

			// Parallel programming stuff  DON'T CARE
			else if(ch=='E') {
				getNch(5);
				nothing_response();
			}

			// Enter programming mode
			else if(ch=='P') {
				nothing_response();
			}

			// Leave programming mode
			else if(ch=='Q') {
				nothing_response();
				end();
				return;
			}

			// Erase device, don't care as we will erase one page at a time anyway.
			else if(ch=='R') {
				nothing_response();
			}

			// Set address, little endian. EEPROM in bytes, FLASH in words
			else if(ch=='U') {
				//Perhaps extra address bytes may be added in future to support > 128kB FLASH.
				//This might explain why little endian was used here, big endian used everywhere else.
				address.byte[0] = getch();
				address.byte[1] = getch();
				nothing_response();
			}

			// Universal SPI programming command, disabled.  Would be used for fuses and lock bits.
			else if(ch=='V') {
				getNch(4);
				byte_response(0x00);
			}

			// Write memory, length is big endian and is in bytes
			else if(ch=='d') {
				length.byte[1] = getch();
				length.byte[0] = getch();

				flags.eeprom = 0;
				if (getch() == 'E')
					flags.eeprom = 1;

				for (w=0;w<length.word;w++) {
					// Store data in buffer, can't keep up with serial data stream whilst programming pages
					buff[w] = getch();
				}
				if (getch() == ' ') {
					//Write to EEPROM one byte at a time
					if (flags.eeprom) {
						for(w=0;w<length.word;w++) {
							eeprom_write_byte((uint8_t *)address.word, (uint8_t)buff[w]);
							address.word++;
						}
					} else {
						// nothing to do for FLASH
					}
					rs_putc(0x14);
					rs_putc(0x10);
				}
			}

			//Read memory block mode, length is big endian.
			else if(ch=='t') {
				length.byte[1] = getch();
				length.byte[0] = getch();

				flags.eeprom = 0;
				if (getch() == 'E')
					flags.eeprom = 1;

				// Command terminator
				if (getch() == ' ') {
					rs_putc(0x14);
					// Can handle odd and even lengths okay
					for (w=0;w < length.word;w++) {
						if (flags.eeprom) {
							// Byte access EEPROM read
							rs_putc(eeprom_read_byte((uint8_t *)address.word));
							address.word++;
						} else {
							// nothing to do for FLASH
							rs_putc(0x00);
						}
					}
					rs_putc(0x10);
				}
			}

			// Get device signature bytes
			else if(ch=='u') {
				if (getch() == ' ') {
					rs_putc(0x14);
					rs_putc(SIG1);
					rs_putc(SIG2);
					rs_putc(SIG3);
					rs_putc(0x10);
				}
			}

			// Read oscillator calibration byte
			else if(ch=='v') {
				byte_response(0x00);
			}
		}
	}
}
