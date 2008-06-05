#ifndef __DELAY_H__
#define __DELAY_H__
#define F_CPU MOXA_MCU_CLOCK
#include <util/delay.h>
#define delay_us(t) _delay_ms(t/1000)
#define delay_ms(t) { uint16_t dt=(t); while(dt--) { _delay_ms(1); } }
#endif
