/*!
  @file
  @brief �f�o�C�X��I/O�|�[�g�Ɋւ����`

  �f�o�C�X�͐ڑ�����ۂɃf�o�C�X�|�[�g�ԍ����w�肷��K�v������܂����A
  �f�o�C�X�|�[�g�ԍ��̓}�C�R����I/O�|�[�g�ԍ��ƈ�Έ�őΉ����Ă���킯�ł͂���܂���B
  �{�t�@�C���ł́A�f�o�C�X�|�[�g�ԍ���I/O�|�[�g�ԍ��Ƃ��}�b�s���O�����邽�߂̒�`���s�Ȃ��Ă���A
  �g�p����{�[�h�̎�ނɂ���ă}�b�s���O��ύX�\�Ƃ��邱�Ƃ�ړI�Ƃ��Ă��܂��B
  �Ȃ��{�[�h�̎�ނɂ���Ē�`��ύX����K�v������̂��Ƃ����ƁA�]���{�[�h�ɂ͂��炩���ߎ�������
  �Ă���Z���T�[������A�l�X�Ȏ���ŋ��ʂ̃|�[�g��`�����邱�Ƃ��ł��Ȃ�����ł��B

  @author Shinji Yamachika
  @date   2005/11/25
  @version 0.1
*/

#ifndef __DEVICE_PORT_H__
#define __DEVICE_PORT_H__

#include "moxa_config.h"

#if defined _CHIP_ATMEGA128_ | defined _CHIP_ATMEGA128L_

#define DEVICE_PORT_INPUT   0    //!< I/O�|�[�g����͂Ƃ��Ďg�p����Ƃ��Ɏw�肷��}�N��
#define DEVICE_PORT_OUTPUT  1    //!< I/O�|�[�g���o�͂Ƃ��Ďg�p����Ƃ��Ɏw�肷��}�N��

#ifndef DEVICE_PORT_N
#define DEVICE_PORT_N       8    //!< �g�p�\�ȃf�o�C�X�|�[�g�̐���\���}�N��
#endif



/*!
  �w�肵��I/O�|�[�g�����������܂��B

  @param nPort    I/O�|�[�g�ԍ�(0�`7)
  @param nOutput  ���́E�o�͂̎w��i0�̂Ƃ����́A0�ȊO�̂Ƃ��o��)
  @retval MOXA_SUCCESS  �������ɐ���
  @retval MOXA_E_PARAM  �����Ŏw�肵��I/O�|�[�g�ԍ����s��
*/
MRESULT DEVICE_port_init(UINT8 nPort, BOOL bOutput);


#if (MOXA_BOARD_TYPE == MOXA_BOARD_PROTO_1) | (MOXA_BOARD_TYPE == MOXA_BOARD_STK300)

/* PROTO1, STK300�p�|�[�g�ݒ�}�N�� */
/*
  �e�f�o�C�X�|�[�g�̖����Ɛ���

  �f�o�C�X�|�[�g�O�F�ėp�|�[�g��ADC�|�[�g�Ƃ��Ďg�p
  �f�o�C�X�|�[�g�P�F�ėp�|�[�g��ADC�|�[�g�Ƃ��Ďg�p
  �f�o�C�X�|�[�g�Q�F�ėp�|�[�g��ADC�|�[�g�Ƃ��Ďg�p
  �f�o�C�X�|�[�g�R�F�ėp�|�[�g��ADC�|�[�g�Ƃ��Ďg�p
  �f�o�C�X�|�[�g�S�F�ėp�|�[�g��ADC�|�[�g�Ƃ��Ďg�p
  �f�o�C�X�|�[�g�T�F�ėp�|�[�g��ADC�|�[�g�Ƃ��Ďg�p
  �f�o�C�X�|�[�g�U�F�ėp�|�[�g��ADC�|�[�g�Ƃ��Ďg�p
  �f�o�C�X�|�[�g�V�F�ėp�|�[�g��ADC�|�[�g�Ƃ��Ďg�p
*/
#define DEVICE_SCL_(s) __OUT(PORTD,0,s)
#define DEVICE_SCL     __IN(PORTD,0)
#define DEVICE_SDA_(s) __OUT(PORTD,1,s)
#define DEVICE_SDA     __IN(PORTD,1)

// Device port 0
#define DEVICE_PORT_DIR0_(s) __OUT(DDRB,4,s)
#define DEVICE_PORT_DIR0     __IN(DDRB,4)
#define DEVICE_PORT_OUT0_(s) __OUT(PORTB,4,s)
#define DEVICE_PORT_OUT0     __IN(PORTB,4)
#define DEVICE_PORT_INP0_(s) __OUT(PINB,4,s)
#define DEVICE_PORT_INP0     __IN(PINB,4)
#define DEVICE_PORT_ADC0_(s) __OUT(PORTF,0,s)
#define DEVICE_PORT_ADC0     __IN(PORTF,0)

// Device port 1
#define DEVICE_PORT_DIR1_(s) __OUT(DDRB,7,s)
#define DEVICE_PORT_DIR1     __IN(DDRB,7)
#define DEVICE_PORT_OUT1_(s) __OUT(PORTB,7,s)
#define DEVICE_PORT_OUT1     __IN(PORTB,7)
#define DEVICE_PORT_INP1_(s) __OUT(PINB,7,s)
#define DEVICE_PORT_INP1     __IN(PINB,7)
#define DEVICE_PORT_ADC1_(s) __OUT(PORTF,1,s)
#define DEVICE_PORT_ADC1     __IN(PORTF,1)

// Device port 2
#define DEVICE_PORT_DIR2_(s) __OUT(DDRD,5,s)
#define DEVICE_PORT_DIR2     __IN(DDRD,5)
#define DEVICE_PORT_OUT2_(s) __OUT(PORTD,5,s)
#define DEVICE_PORT_OUT2     __IN(PORTD,5)
#define DEVICE_PORT_INP2_(s) __OUT(PIND,5,s)
#define DEVICE_PORT_INP2     __IN(PIND,5)
#define DEVICE_PORT_ADC2_(s) __OUT(PORTF,2,s)
#define DEVICE_PORT_ADC2     __IN(PORTF,2)

// Device port 3
#define DEVICE_PORT_DIR3_(s) __OUT(DDRD,7,s)
#define DEVICE_PORT_DIR3     __IN(DDRD,7)
#define DEVICE_PORT_OUT3_(s) __OUT(PORTD,7,s)
#define DEVICE_PORT_OUT3     __IN(PORTD,7)
#define DEVICE_PORT_INP3_(s) __OUT(PIND,7,s)
#define DEVICE_PORT_INP3     __IN(PIND,7)
#define DEVICE_PORT_ADC3_(s) __OUT(PORTF,3,s)
#define DEVICE_PORT_ADC3     __IN(PORTF,3)

// Device port 4
#define DEVICE_PORT_DIR4_(s) __OUT(DDRE,2,s)
#define DEVICE_PORT_DIR4     __IN(DDRE,2)
#define DEVICE_PORT_OUT4_(s) __OUT(PORTE,2,s)
#define DEVICE_PORT_OUT4     __IN(PORTE,2)
#define DEVICE_PORT_INP4_(s) __OUT(PINE,2,s)
#define DEVICE_PORT_INP4     __IN(PINE,2)
#define DEVICE_PORT_ADC4_(s) __OUT(PORTF,4,s)
#define DEVICE_PORT_ADC4     __IN(PORTF,4)

// Device port 5
#define DEVICE_PORT_DIR5_(s) __OUT(DDRE,3,s)
#define DEVICE_PORT_DIR5     __IN(DDRE,3)
#define DEVICE_PORT_OUT5_(s) __OUT(PORTE,3,s)
#define DEVICE_PORT_OUT5     __IN(PORTE,3)
#define DEVICE_PORT_INP5_(s) __OUT(PINE,3,s)
#define DEVICE_PORT_INP5     __IN(PINE,3)
#define DEVICE_PORT_ADC5_(s) __OUT(PORTF,5,s)
#define DEVICE_PORT_ADC5     __IN(PORTF,5)

// Device port 6
#define DEVICE_PORT_DIR6_(s) __OUT(DDRE,4,s)
#define DEVICE_PORT_DIR6     __IN(DDRE,4)
#define DEVICE_PORT_OUT6_(s) __OUT(PORTE,4,s)
#define DEVICE_PORT_OUT6     __IN(PORTE,4)
#define DEVICE_PORT_INP6_(s) __OUT(PINE,4,s)
#define DEVICE_PORT_INP6     __IN(PINE,4)
#define DEVICE_PORT_ADC6_(s) __OUT(PORTF,6,s)
#define DEVICE_PORT_ADC6     __IN(PORTF,6)

// Device port 7
#define DEVICE_PORT_DIR7_(s) __OUT(DDRE,5,s)
#define DEVICE_PORT_DIR7     __IN(DDRE,5)
#define DEVICE_PORT_OUT7_(s) __OUT(PORTE,5,s)
#define DEVICE_PORT_OUT7     __IN(PORTE,5)
#define DEVICE_PORT_INP7_(s) __OUT(PINE,5,s)
#define DEVICE_PORT_INP7     __IN(PINE,5)
#define DEVICE_PORT_ADC7_(s) __OUT(PORTF,7,s)
#define DEVICE_PORT_ADC7     __IN(PORTF,7)

#elif (MOXA_BOARD_TYPE == MOXA_BOARD_CC2420DBK)

/* CC2420DBK�p�|�[�g�ݒ�}�N�� */
/*
  �e�Z���T�[�|�[�g�̖����Ɛ���

  �f�o�C�X�|�[�g�O�FD301��LED���AADC�|�[�g(PORTF.4)�Ƃ��Ďg�p
  �f�o�C�X�|�[�g�P�FD302��LED���AADC�|�[�g(PORTF.5)�Ƃ��Ďg�p
  �f�o�C�X�|�[�g�Q�FD304��LED���AADC�|�[�g(PORTF.6)�Ƃ��Ďg�p
  �f�o�C�X�|�[�g�R�FD303��LED�Ƃ��Ďg�p�iADC�͎g�p�ł��Ȃ��j
  �f�o�C�X�|�[�g�S�FS2�̃v�b�V���X�C�b�`�Ƃ��Ďg�p�iADC�͎g�p�ł��Ȃ��j
  �f�o�C�X�|�[�g�T�FRT1���X���C�_�[(PORTF.0)�Ƃ��Ďg�p�iPIO�͎g�p�ł��Ȃ��j
  �f�o�C�X�|�[�g�U�FU2�����x�Z���T�[(PORTF.3)�Ƃ��Ďg�p�iPIO�͎g�p�ł��Ȃ��j
  �f�o�C�X�|�[�g�V�FPIO7�i�ėp�|�[�g�j�Ƃ��āA���邢��ADC�|�[�g(PORTF.7)�Ƃ��Ďg�p
*/
static UINT8 s_DummyReg;                     // �����ȃ|�[�g�Ƃ��ăA�N�Z�X�����邽�߂̕ϐ�
#define DEVICE_PORT_NULL  s_DummyReg         // �����ȃ|�[�g�̒�`�}�N��

#define DEVICE_SCL_(s) __OUT(PORTD,0,s)
#define DEVICE_SCL     __IN(PORTD,0)
#define DEVICE_SDA_(s) __OUT(PORTD,1,s)
#define DEVICE_SDA     __IN(PORTD,1)

// Device port 0
#define DEVICE_PORT_DIR0_(s) __OUT(DDRB,7,s)
#define DEVICE_PORT_DIR0     __IN(DDRB,7)             // D301 LED (green)
#define DEVICE_PORT_OUT0_(s) __OUT(PORTB,7,s)
#define DEVICE_PORT_OUT0     __IN(PORTB,7)
#define DEVICE_PORT_INP0_(s) __OUT(PINB,7,s)
#define DEVICE_PORT_INP0     __IN(PINB,7)
#define DEVICE_PORT_ADC0_(s) __OUT(PORTF,4,s)
#define DEVICE_PORT_ADC0     __IN(PORTF,4)

// Device port 1
#define DEVICE_PORT_DIR1_(s) __OUT(DDRB,4,s)
#define DEVICE_PORT_DIR1     __IN(DDRB,4)             // D302 LED (orange)
#define DEVICE_PORT_OUT1_(s) __OUT(PORTB,4,s)
#define DEVICE_PORT_OUT1     __IN(PORTB,4)
#define DEVICE_PORT_INP1_(s) __OUT(PINB,4,s)
#define DEVICE_PORT_INP1     __IN(PINB,4)
#define DEVICE_PORT_ADC1_(s) __OUT(PORTF,5,s)
#define DEVICE_PORT_ADC1     __IN(PORTF,5)

// Device port 2
#define DEVICE_PORT_DIR2_(s) __OUT(DDRE,3,s)
#define DEVICE_PORT_DIR2     __IN(DDRE,3)             // D304 LED (red)
#define DEVICE_PORT_OUT2_(s) __OUT(PORTE,3,s)
#define DEVICE_PORT_OUT2     __IN(PORTE,3)
#define DEVICE_PORT_INP2_(s) __OUT(PINE,3,s)
#define DEVICE_PORT_INP2     __IN(PINE,3)
#define DEVICE_PORT_ADC2_(s) __OUT(PORTF,6,s)
#define DEVICE_PORT_ADC2     __IN(PORTF,6)

// Device port 3
#define DEVICE_PORT_DIR3_(s) __OUT(DDRE,4,s)
#define DEVICE_PORT_DIR3     __IN(DDRE,4)             // D303 LED (yellow)
#define DEVICE_PORT_OUT3_(s) __OUT(PORTE,4,s)
#define DEVICE_PORT_OUT3     __IN(PORTE,4)
#define DEVICE_PORT_INP3_(s) __OUT(PINE,4,s)
#define DEVICE_PORT_INP3     __IN(PINE,4)
#define DEVICE_PORT_ADC3    DEVICE_PORT_NULL          // �����|�[�g

// Device port 4
#define DEVICE_PORT_DIR4_(s) __OUT(DDRE,5,s)
#define DEVICE_PORT_DIR4     __IN(DDRE,5)             // S1�v�b�V���X�C�b�`
#define DEVICE_PORT_OUT4_(s) __OUT(PORTE,5,s)
#define DEVICE_PORT_OUT4     __IN(PORTE,5)
#define DEVICE_PORT_INP4_(s) __OUT(PINE,5,s)
#define DEVICE_PORT_INP4     __IN(PINE,5)
#define DEVICE_PORT_ADC4    DEVICE_PORT_NULL          // �����|�[�g

// Device port 5
#define DEVICE_PORT_DIR5  DEVICE_PORT_NULL            // �����|�[�g
#define DEVICE_PORT_OUT5  DEVICE_PORT_NULL            // �����|�[�g
#define DEVICE_PORT_INP5  DEVICE_PORT_NULL            // �����|�[�g
#define DEVICE_PORT_ADC5  __IN(PORTF,0)               // RT1�X���C�_�[

// Device port 6
#define DEVICE_PORT_DIR6  DEVICE_PORT_NULL            // �����|�[�g
#define DEVICE_PORT_OUT6  DEVICE_PORT_NULL            // �����|�[�g
#define DEVICE_PORT_INP6  DEVICE_PORT_NULL            // �����|�[�g
#define DEVICE_PORT_ADC6  __IN(PORTF,3)               // U2���x�Z���T�[(LM61)

// Device port 7
#define DEVICE_PORT_DIR7_(s) __OUT(DDRE,7,s)
#define DEVICE_PORT_DIR7     __IN(DDRE,7)             // �ėp�|�[�g(CC2420DB P3 14pin)
#define DEVICE_PORT_OUT7_(s) __OUT(PORTE,7,s)
#define DEVICE_PORT_OUT7     __IN(PORTE,7)            //           (CC2420DB GND 20pin)
#define DEVICE_PORT_INP7_(s) __OUT(PINE,7,s)
#define DEVICE_PORT_INP7     __IN(PINE,7)
#define DEVICE_PORT_ADC7_(s) __OUT(PORTF,7,s)
#define DEVICE_PORT_ADC7     __IN(PORTF,7)            // �ėpADC7�|�[�g

#endif // MOXA_BOARD_TYPE

#endif // _CHIP_ATMEGA128_, _CHIP_ATMEGA128L_

#endif // __DEVICE_PORT_H__
