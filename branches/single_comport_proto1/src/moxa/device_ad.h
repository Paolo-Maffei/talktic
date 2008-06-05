/*!
  @file
  @brief デバイスのAD変換処理関数定義

  使用方法は、初期化関数DEVICE_ad_initで初期化を行い、DEVICE_ad_getで引数にチャンネル番号を
  指定してAD変換を行ないます。

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
  デバイスポート番号をADCポート番号に変換する配列です。
  添え字にデバイスポート番号を指定すると、その配列の中身はADCポート番号を指しています。
  ADCポート番号として-1が格納されているデバイスポート番号は、A/Dコンバートすることが
  できないデバイスポートであることを示しています。
  （これは評価用ボードの制限で、最終的なボード基板にはこの制約はないはずです）
  配列の定義はsensor_port.cをご覧ください。
*/
#if ! ((MOXA_BOARD_TYPE == MOXA_BOARD_PROTO_1) | (MOXA_BOARD_TYPE == MOXA_BOARD_STK300))
extern INT8 g_DeviceAdMapping[DEVICE_PORT_N];
#endif

#if defined _CHIP_ATMEGA128_ | defined _CHIP_ATMEGA128L_

//! AD変換を開始するレジスタの初期化を行なうマクロ
#define DEVICE_ADC_INIT() \
    { \
        ADCSRA = BM(ADPS0) | BM(ADPS1); \
        ADMUX = BM(REFS0); \
    }

//! AD変換を停止するレジスタの初期化を行なうマクロ
#define DEVICE_ADC_UNINIT() \
    { \
        ADCSRA = 0x00; \
        ADMUX = 0x00; \
    }

//! AD変換の初期化が行なわれているか調べるマクロ
#define DEVICE_ADC_CHECK()  (ADCSRA == (BM(ADPS0) | BM(ADPS1)))
 
//! AD変換するチャンネルを指定するマクロ（0～7: PORTF.0～PORTF.7）
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
  AD変換の初期化関数です。
  AD変換機能を使用するには本関数を呼ぶ必要があります。

  @param nPort  デバイスポート番号
  @retval MOXA_SUCCESS  初期化に成功
  @retval MOXA_E_FAIL   指定したポートはA/D変換することができない
  @retval MOXA_E_PARAM  引数の指定に間違いがある
*/
MRESULT DEVICE_ad_init(UINT8 nPort);

/*!
  デバイスポート番号を指定してAD変換を行ないます。

  @param nPort  デバイスポート番号
  @return AD変換した結果(0～1023の値、10bitAD)
*/
UINT16 DEVICE_ad_get(UINT8 nPort);

//#pragma used-

#endif // __DEVICE_AD_H__
