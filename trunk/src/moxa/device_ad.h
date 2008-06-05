/*!
  @file
  @brief �f�o�C�X��AD�ϊ������֐���`

  �g�p���@�́A�������֐�DEVICE_ad_init�ŏ��������s���ADEVICE_ad_get�ň����Ƀ`�����l���ԍ���
  �w�肵��AD�ϊ����s�Ȃ��܂��B

  UINT16 nVal;
  
  DEVICE_ad_init();

  while (1) {
      // Read from Port F7
      nVal = AD_ad_get(7);
  }

  @author Shinji Yamachika, Vistarica Designs Co.Ltd.
  @date   2005/11/22
  @version 0.1
*/
#ifndef __DEVICE_AD_H__
#define __DEVICE_AD_H__

#include "moxa_config.h"

/*!
  �f�o�C�X�|�[�g�ԍ���ADC�|�[�g�ԍ��ɕϊ�����z��ł��B
  �Y�����Ƀf�o�C�X�|�[�g�ԍ����w�肷��ƁA���̔z��̒��g��ADC�|�[�g�ԍ����w���Ă��܂��B
  ADC�|�[�g�ԍ��Ƃ���-1���i�[����Ă���f�o�C�X�|�[�g�ԍ��́AA/D�R���o�[�g���邱�Ƃ�
  �ł��Ȃ��f�o�C�X�|�[�g�ł��邱�Ƃ������Ă��܂��B
  �i����͕]���p�{�[�h�̐����ŁA�ŏI�I�ȃ{�[�h��ɂ͂��̐���͂Ȃ��͂��ł��j
  �z��̒�`��sensor_port.c���������������B
*/
#if ! ((MOXA_BOARD_TYPE == MOXA_BOARD_PROTO_1) | (MOXA_BOARD_TYPE == MOXA_BOARD_STK300))
extern INT8 g_DeviceAdMapping[DEVICE_PORT_N];
#endif

#if defined _CHIP_ATMEGA128_ | defined _CHIP_ATMEGA128L_

//! AD�ϊ����J�n���郌�W�X�^�̏��������s�Ȃ��}�N��
#define DEVICE_ADC_INIT() \
    { \
        ADCSRA = BM(ADPS0) | BM(ADPS1); \
        ADMUX = BM(REFS0); \
    }

//! AD�ϊ����~���郌�W�X�^�̏��������s�Ȃ��}�N��
#define DEVICE_ADC_UNINIT() \
    { \
        ADCSRA = 0x00; \
        ADMUX = 0x00; \
    }

//! AD�ϊ��̏��������s�Ȃ��Ă��邩���ׂ�}�N��
#define DEVICE_ADC_CHECK()  (ADCSRA == (BM(ADPS0) | BM(ADPS1)))
 
//! AD�ϊ�����`�����l�����w�肷��}�N���i0�`7: PORTF.0�`PORTF.7�j
#define DEVICE_ADC_SET_CHANNEL(channel) (ADMUX = (ADMUX & ~0x1F) | (UINT8)(channel))

//! Enables/disables the ADC
#define DEVICE_ADC_ENABLE()  (ADCSRA |= BM(ADEN))
#define DEVICE_ADC_DISABLE() (ADCSRA &= ~BM(ADEN))

//! Macro for taking a single sample in single-conversion mode (not required in continuous mode)
#define DEVICE_ADC_SAMPLE_SINGLE() \
    { \
        ADCSRA |= BM(ADSC); \
        while (!(ADCSRA & 0x10)); \
    }

//! Macros for obtaining the latest 10 sample value
#define DEVICE_ADC_GET_SAMPLE_10BIT(x) \
    { \
        x =  (UINT16)ADCL; \
        x |= (UINT16)ADCH << 8; \
    }

//! Macros for obtaining the latest 8 sample value
#define DEVICE_ADC_GET_SAMPLE_8BIT(x) \
    { \
        x =  (UINT8)ADCL >> 2; \
        x |= (UINT8)ADCH << 6; \
    }
#endif  // _CHIP_ATMEGA128_, _CHIP_ATMEGA128L_

//#pragma used+

/*!
  AD�ϊ��̏������֐��ł��B
  AD�ϊ��@�\���g�p����ɂ͖{�֐����ĂԕK�v������܂��B

  @param nPort  �f�o�C�X�|�[�g�ԍ�
  @retval MOXA_SUCCESS  �������ɐ���
  @retval MOXA_E_FAIL   �w�肵���|�[�g��A/D�ϊ����邱�Ƃ��ł��Ȃ�
  @retval MOXA_E_PARAM  �����̎w��ɊԈႢ������
*/
MRESULT DEVICE_ad_init(UINT8 nPort);

/*!
  �f�o�C�X�|�[�g�ԍ����w�肵��AD�ϊ����s�Ȃ��܂��B

  @param nPort  �f�o�C�X�|�[�g�ԍ�
  @return AD�ϊ���������(0�`1023�̒l�A10bitAD)
*/
UINT16 DEVICE_ad_get(UINT8 nPort);

//#pragma used-

#endif // __DEVICE_AD_H__
