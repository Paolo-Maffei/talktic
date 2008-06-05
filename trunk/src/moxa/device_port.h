/*!
  @file
  @brief デバイスのI/Oポートに関する定義

  デバイスは接続する際にデバイスポート番号を指定する必要がありますが、
  デバイスポート番号はマイコンのI/Oポート番号と一対一で対応しているわけではありません。
  本ファイルでは、デバイスポート番号とI/Oポート番号とをマッピングさせるための定義を行なっており、
  使用するボードの種類によってマッピングを変更可能とすることを目的としています。
  なぜボードの種類によって定義を変更する必要があるのかというと、評価ボードにはあらかじめ実装され
  ているセンサーがあり、様々な事情で共通のポート定義をすることができないからです。

  @author Shinji Yamachika
  @date   2005/11/25
  @version 0.1
*/

#ifndef __DEVICE_PORT_H__
#define __DEVICE_PORT_H__

#include "moxa_config.h"

#if defined _CHIP_ATMEGA128_ | defined _CHIP_ATMEGA128L_

#define DEVICE_PORT_INPUT   0    //!< I/Oポートを入力として使用するときに指定するマクロ
#define DEVICE_PORT_OUTPUT  1    //!< I/Oポートを出力として使用するときに指定するマクロ

#ifndef DEVICE_PORT_N
#define DEVICE_PORT_N       8    //!< 使用可能なデバイスポートの数を表すマクロ
#endif



/*!
  指定したI/Oポートを初期化します。

  @param nPort    I/Oポート番号(0～7)
  @param nOutput  入力・出力の指定（0のとき入力、0以外のとき出力)
  @retval MOXA_SUCCESS  初期化に成功
  @retval MOXA_E_PARAM  引数で指定したI/Oポート番号が不正
*/
MRESULT DEVICE_port_init(UINT8 nPort, BOOL bOutput);


#if (MOXA_BOARD_TYPE == MOXA_BOARD_PROTO_1) | (MOXA_BOARD_TYPE == MOXA_BOARD_STK300)

/* PROTO1, STK300用ポート設定マクロ */
/*
  各デバイスポートの役割と制限

  デバイスポート０：汎用ポートかADCポートとして使用
  デバイスポート１：汎用ポートかADCポートとして使用
  デバイスポート２：汎用ポートかADCポートとして使用
  デバイスポート３：汎用ポートかADCポートとして使用
  デバイスポート４：汎用ポートかADCポートとして使用
  デバイスポート５：汎用ポートかADCポートとして使用
  デバイスポート６：汎用ポートかADCポートとして使用
  デバイスポート７：汎用ポートかADCポートとして使用
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

/* CC2420DBK用ポート設定マクロ */
/*
  各センサーポートの役割と制限

  デバイスポート０：D301のLEDか、ADCポート(PORTF.4)として使用
  デバイスポート１：D302のLEDか、ADCポート(PORTF.5)として使用
  デバイスポート２：D304のLEDか、ADCポート(PORTF.6)として使用
  デバイスポート３：D303のLEDとして使用（ADCは使用できない）
  デバイスポート４：S2のプッシュスイッチとして使用（ADCは使用できない）
  デバイスポート５：RT1をスライダー(PORTF.0)として使用（PIOは使用できない）
  デバイスポート６：U2を温度センサー(PORTF.3)として使用（PIOは使用できない）
  デバイスポート７：PIO7（汎用ポート）として、あるいはADCポート(PORTF.7)として使用
*/
static UINT8 s_DummyReg;                     // 無効なポートとしてアクセスさせるための変数
#define DEVICE_PORT_NULL  s_DummyReg         // 無効なポートの定義マクロ

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
#define DEVICE_PORT_ADC3    DEVICE_PORT_NULL          // 無効ポート

// Device port 4
#define DEVICE_PORT_DIR4_(s) __OUT(DDRE,5,s)
#define DEVICE_PORT_DIR4     __IN(DDRE,5)             // S1プッシュスイッチ
#define DEVICE_PORT_OUT4_(s) __OUT(PORTE,5,s)
#define DEVICE_PORT_OUT4     __IN(PORTE,5)
#define DEVICE_PORT_INP4_(s) __OUT(PINE,5,s)
#define DEVICE_PORT_INP4     __IN(PINE,5)
#define DEVICE_PORT_ADC4    DEVICE_PORT_NULL          // 無効ポート

// Device port 5
#define DEVICE_PORT_DIR5  DEVICE_PORT_NULL            // 無効ポート
#define DEVICE_PORT_OUT5  DEVICE_PORT_NULL            // 無効ポート
#define DEVICE_PORT_INP5  DEVICE_PORT_NULL            // 無効ポート
#define DEVICE_PORT_ADC5  __IN(PORTF,0)               // RT1スライダー

// Device port 6
#define DEVICE_PORT_DIR6  DEVICE_PORT_NULL            // 無効ポート
#define DEVICE_PORT_OUT6  DEVICE_PORT_NULL            // 無効ポート
#define DEVICE_PORT_INP6  DEVICE_PORT_NULL            // 無効ポート
#define DEVICE_PORT_ADC6  __IN(PORTF,3)               // U2温度センサー(LM61)

// Device port 7
#define DEVICE_PORT_DIR7_(s) __OUT(DDRE,7,s)
#define DEVICE_PORT_DIR7     __IN(DDRE,7)             // 汎用ポート(CC2420DB P3 14pin)
#define DEVICE_PORT_OUT7_(s) __OUT(PORTE,7,s)
#define DEVICE_PORT_OUT7     __IN(PORTE,7)            //           (CC2420DB GND 20pin)
#define DEVICE_PORT_INP7_(s) __OUT(PINE,7,s)
#define DEVICE_PORT_INP7     __IN(PINE,7)
#define DEVICE_PORT_ADC7_(s) __OUT(PORTF,7,s)
#define DEVICE_PORT_ADC7     __IN(PORTF,7)            // 汎用ADC7ポート

#endif // MOXA_BOARD_TYPE

#endif // _CHIP_ATMEGA128_, _CHIP_ATMEGA128L_

#endif // __DEVICE_PORT_H__
