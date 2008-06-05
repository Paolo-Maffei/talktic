/*!
  @file
  @brief MOXAライブラリの設定マクロ

  本ファイルは、MOXAライブラリ全般に関係する設定マクロを記述するヘッダファイルです。
  MOXAライブラリに対して設定を変更する場合は本ファイルを編集し、ライブラリ本体のファイルは
  なるべく変更しないでください。また、新しく基板を開発した場合は新しいボードタイプを追加し
  、それに関係する設定を新たに追加してください。
  
  @author Shinji Yamachika
  @date   2005/12/16
  @version 0.1
 */
#ifndef __MOXA_CONFIG_H__
#define __MOXA_CONFIG_H__

#ifdef __AVR_ATmega128__
#define _CHIP_ATMEGA128_
#endif
#define flash

#define __OUT(pin,bit,state) pin = state ? (pin | (1 << bit)) : (pin & ~(1 << bit))
#define __IN(pin,bit)        ((pin & (1 << bit)) != 0)

/**************************************************************************************
  Target board settings
***************************************************************************************/

/*
  ボードタイプの値定義（開発者以外は変更しないでください）
また、新しく基板を開発したときは重複しない値でボードタイプを追加してください
*/
#define MOXA_BOARD_PROTO_1     1              //!< CREST prototype board 1
#define MOXA_BOARD_STK300      10             //!< Kanda STK300 Development Kit
#define MOXA_BOARD_CC2420DBK   11             //!< Chipcon CC2420DB 1.2

/*!
  使用するボードタイプを指定してください
  ただし、なるべくプロジェクトの設定"Globally #define"で指定することをお勧めします。
*/
#ifndef MOXA_BOARD_TYPE
#define MOXA_BOARD_TYPE  MOXA_BOARD_PROTO_1
#endif

/**************************************************************************************
  Include files
***************************************************************************************/

#include "include.h"
#include "error.h"
//#include "device_proto.h"

/**************************************************************************************
  Target board settings
***************************************************************************************/

/* Micro controller unit settings */

#ifdef _MCU_CLOCK_FREQUENCY_
#define MOXA_MCU_CLOCK  _MCU_CLOCK_FREQUENCY_   //!< MCU Clock (Hz)
/*
  _MCU_CLOCK_FREQUENCY_マクロはCodeVisionのプロジェクト設定で指定します。
  通常は_MCU_CLOCK_FREQUENCY_の値をMOXA_MCU_CLOCKに設定して使用してください。
  else以下の値はプロジェクト設定で各ボードに設定すべきクロックをメモする程度の
  意味で記述してあります。新しくボードを開発したときは動作クロックを追加してください。
*/
#elif defined F_CPU
#define MOXA_MCU_CLOCK  F_CPU
#elif (MOXA_BOARD_TYPE == MOXA_BOARD_PROTO_1)
#define MOXA_MCU_CLOCK  8000000                 //!< PROTO1 Board MCU Clock (Hz)
#elif (MOXA_BOARD_TYPE == MOXA_BOARD_STK300)
#define MOXA_MCU_CLOCK  4000000                 //!< STK300 Board MCU Clock (Hz)
#elif (MOXA_BOARD_TYPE == MOXA_BOARD_CC2420DBK)
#define MOXA_MCU_CLOCK  8000000                 //!< CC2420DBK Board MCU Clock (Hz)
#endif // _MCU_CLOCK_FREQUENCY_

#if defined _CHIP_ATMEGA128_ | defined _CHIP_ATMEGA128L_
//#include <mega128.h>
#include <avr/io.h>
#include "mega128_macro.h"
//#include "mega128_reg.h"
#else
#error MCU type is not specified.
#endif

/**************************************************************************************
  Debug settings
***************************************************************************************/

/* Debug options */
#define MOXA_DEBUG_CHECK_INIT     //!< 初期化処理の２重呼び出しをチェックします
//#define MOXA_DEBUG_CHECK_PARAM    //!< 関数呼び出し時に引数をチェックします

/**************************************************************************************
   Radio communication settings
***************************************************************************************/

#define MOXA_USE_CHIP_CC2420     //!< 無線チップにCC2420を使用します

/**************************************************************************************
  Memory settings
***************************************************************************************/

/*
  新しく基板を作成したときはSRAMサイズを設定してください
  SRAMサイズには0, 32, 64の値を指定することができます
*/
#if (MOXA_BOARD_TYPE == MOXA_BOARD_PROTO_1)
#define MEMORY_EXT_SRAM_SIZE  32                     //!< PROTO1基板の外部SRAMサイズ
#elif (MOXA_BOARD_TYPE == MOXA_BOARD_STK300)
#define MEMORY_EXT_SRAM_SIZE  0                      //!< STK300基板の外部SRAMサイズ
#elif (MOXA_BOARD_TYPE == MOXA_BOARD_CC2420DBK)
#define MEMORY_EXT_SRAM_SIZE  0                      //!< CC2420DBK基板の外部SRAMサイズ
#endif

/**************************************************************************************
  Serial settings
***************************************************************************************/

/*!
  可変長引数処理のバッファサイズです。SERIAL_printf, SERIAL_scanfの関数で扱う文字列の
  長さがSERIAL_VARARG_SIZEを超えるとき、正しく処理することができません。
  そのときは数値を大きな値に変更してください。
*/
#define SERIAL_VARARG_SIZE  64

/*!
  シリアル送信を通常の２倍の速度で処理します。（非同期モードでしか使用来ません）
*/
#undef SERIAL_DOUBLE_SPEED

#if (MOXA_BOARD_TYPE == MOXA_BOARD_PROTO_1)
#define SERIAL_PORT_N  2                             //!< PROTO1基板のシリアルポート数
#elif (MOXA_BOARD_TYPE == MOXA_BOARD_STK300)
#define SERIAL_PORT_N  2                             //!< STK300基板のシリアルポート数
#elif (MOXA_BOARD_TYPE == MOXA_BOARD_CC2420DBK)
#define SERIAL_PORT_N  2                             //!< CC2420DBK基板のシリアルポート数
                                                     // ただし0番ポートは使用できません
#endif

/*
  バッファオーバーフローが発生したとき、サイズを大きくしてみてください。
*/
#define SERIAL_TX_BUFSIZE  32                        //!< シリアル送信バッファサイズ
#define SERIAL_RX_BUFSIZE  32                        //!< シリアル受信バッファサイズ

/**************************************************************************************
  Device settings
***************************************************************************************/

#define DEVICE_PORT_N   8    //!< 使用可能なデバイスポートの数

/**************************************************************************************
  Temperature sensor settings
***************************************************************************************/

#define MOXA_TEMP_USE_LM61   //!< 温度センサーとしてLM61を使用するとき有効にしてください

#endif // __MOXA_CONFIG_H__
