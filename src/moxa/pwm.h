#ifndef __PWM_H_
#define __PWM_H_

#include "moxa_config.h"

// PWM標準マクロ
// PWM0はOC0, PWM1はOC2を利用

#define TIMER0_CLK_STOP          0x00 // Stop mode (the timer is not counting)
#define TIMER0_CLK_DIV1          0x01 // Total period = Clock freq / 256
#define TIMER0_CLK_DIV8          0x02 // Total period = Clock freq / (256 * 8)
#define TIMER0_CLK_DIV32         0x03 // Total period = Clock freq / (256 * 32)
#define TIMER0_CLK_DIV64         0x04 // Total period = Clock freq / (256 * 64)
#define TIMER0_CLK_DIV128        0x05 // Total period = Clock freq / (256 * 125)
#define TIMER0_CLK_DIV256        0x06 // Total period = Clock freq / (256 * 256)
#define TIMER0_CLK_DIV1024       0x07 // Total period = Clock freq / (256 * 1024)

#define TIMER2_CLK_STOP          0x00 // Stop mode (the timer is not counting)
#define TIMER2_CLK_DIV1          0x01 // Total period = Clock freq / 256
#define TIMER2_CLK_DIV8          0x02 // Total period = Clock freq / (256 * 8)
#define TIMER2_CLK_DIV64         0x03 // Total period = Clock freq / (256 * 64)
#define TIMER2_CLK_DIV256        0x04 // Total period = Clock freq / (256 * 256)
#define TIMER2_CLK_DIV1024       0x05 // Total period = Clock freq / (256 * 1024)
#define TIMER2_CLK_T_FALL        0x06 // External Clock on T(x) pin (falling edge)
#define TIMER2_CLK_T_RISE        0x07 // External Clock on T(x) pin (rising edge)

#define __JOIN__(a,b) a##b
#define __JOIN3__(a,b,c) a##b##c 

#define _PWM_init(pin, num, ttcr, period) \
	__OUT(DDRB,pin,1); \
	__OUT(PORTB,pin,0); \
	__JOIN__(OCR,num) = 0; \
	__JOIN__(TCCR,num) = (ttcr); \
	__JOIN__(TCCR,num) = (__JOIN__(TCCR,num) & ~0x07) | (period);

// 位相基準PWM動作にする
#define _PWM0_init _PWM_init(4,0,BM(WGM00)|BM(COM01)|BM(COM00),TIMER0_CLK_DIV64)
#define _PWM1_init _PWM_init(7,2,BM(WGM20)|BM(COM21)|BM(COM20),TIMER2_CLK_DIV64)

// 比較一致タイマ/カウンタ
#define _SOUND0_init _PWM_init(4,0,BM(WGM01)|BM(COM00),TIMER0_CLK_DIV64)
#define _SOUND1_init _PWM_init(7,2,BM(WGM21)|BM(COM20),TIMER2_CLK_DIV64)

#define _PWM0_is_inited (TCCR0 != 0)
#define _PWM1_is_inited (TCCR2 != 0)

#define _PWM0_SET_DUTY_CYCLE(dutyCycle) (OCR0 = (dutyCycle))
#define _PWM1_SET_DUTY_CYCLE(dutyCycle) (OCR2 = (dutyCycle))

#define _PWM0_off \
	OCR0 = 0; \
	TCCR0 = 0;
#define _PWM1_off \
	OCR2 = 0; \
	TCCR2 = 0;

#define PWM_init(a) __JOIN3__(_PWM,a,_init)
#define PWM_is_inited(a) __JOIN3__(_PWM,a,_is_inited)
#define PWM_out(a,v) __JOIN3__(_PWM,a,_SET_DUTY_CYCLE)(v)
#define PWM_off(a) __JOIN3__(_PWM,a,_off)

// FIXME: PWMとの同時使用で、inited?でinitを判断すると問題あり
#define SOUND_init(a) __JOIN3__(_SOUND,a,_init)
#define SOUND_is_inited(a) __JOIN3__(_PWM,a,_is_inited)
#define SOUND_out(a,v) __JOIN3__(_PWM,a,_SET_DUTY_CYCLE)(MOXA_MCU_CLOCK/(2*64*(v))-1)
#define SOUND_off(a) __JOIN3__(_PWM,a,_off)

#endif
