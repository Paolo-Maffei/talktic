/*!
  @file
  @brief デバッグ用シリアル通信の処理関数定義

  シリアルポートの入出力を行なう関数が定義してあります。
  初期化時には、シリアルポート番号とボーレートを指定してください。
  初期化後にシリアル入出力関数を使用する際にもシリアルポート番号を指定してください。
  例えば、シリアルポート０番を9600bpsで初期化して、入力した文字を大文字に変換して出力する
  プログラムは以下のようなコードになります。

  char ch;

  SERIAL_init(0, 9600);

  while (1) {
      ch = SERIAL_getchar(0);
      if (ch >= 'a' && ch <= 'z') {
          SERIAL_putchar(0, ch - 'a' + 'A');
      } else {
          SERIAL_putchar(0, ch);
      }
  }

  制限事項として、SERIAL_scanf関数は使用できません。
  SERIAL_printf関数はmoxa_config.hに定義してあるSERIAL_VARARG_SIZEの長さを超えて、
  一度に出力することはできません。
  また、SERIAL_sprintf, SERIAL_sscanf関数にはシリアルポートを指定する必要はありません。
  
  @author Shinji Yamachika
  @date   2005/11/28
  @version 0.1
*/

#ifndef __SERIAL_H__
#define __SERIAL_H__

#include "moxa_config.h"
#include "mega128_macro.h"

#include <stdio.h>

//#pragma used+

/*!
  デバッグ用のシリアルポートを初期化します。

  @param nSerialPort  シリアルポート番号を指定(0, 1)
  @param nBaudrate    ボーレートを指定
  @retval MOXA_SUCCESS  初期化に成功
  @retval MOXA_E_PARAM  引数として指定したポート番号に間違いがある
*/
MRESULT SERIAL_init(UINT8 nSerialPort, UINT32 nBaudrate);

/*
  stdio.hに定義してある関数の置き換えマクロです。
  入出力先がポインタのため、シリアルポートに関係なく使用することができます。
*/
#define SERIAL_sprintf  sprintf
#define SERIAL_sscanf   sscanf

/*!
  文字列をシリアル出力します。
  NULL文字がみつかるまでの文字をシリアル出力するので、pStrが指す配列は必ずNULL文字で
  終端している必要があります。

  @param nSerialPort  シリアルポート番号を指定(0, 1)
  @param pStr         表示文字列へのポインタ
  @retval MOXA_SUCCESS  初期化に成功
  @retval MOXA_E_PARAM  引数が不正
*/
MRESULT SERIAL_puts(UINT8 nSerialPort, char flash *pStr);

/*!
  シリアル入力を文字列として取得します。
  改行コードもしくはNULL文字を受け取るまでpStrに指定した配列に文字列を格納します。
  また、(nLength-1)文字を超えた場合も取得は終了します。
  改行コードはNULL文字に置き換えられ、文字列の最後は必ずNULL文字で終わります。
  したがって、nLengthには必要な文字数+1の長さを指定する必要があります。

  @param nSerialPort  シリアルポート番号を指定(0, 1)
  @param pStr         取得した文字列を格納する配列へのポインタ
  @param nLength      取得する文字列数(NULL文字を考慮して2以上を指定してください)
  @retval MOXA_SUCCESS  初期化に成功
  @retval MOXA_E_PARAM  引数が不正
*/
MRESULT SERIAL_gets(UINT8 nSerialPort, char *pStr, UINT8 nLength);

/*!
  引数chで指定した文字をシリアル出力します。

  @param nSerialPort  シリアルポート番号を指定(0, 1)
  @param ch           出力するASCII文字
  @retval MOXA_SUCCESS  初期化に成功
  @retval MOXA_E_PARAM  引数として指定したポート番号に間違いがある
*/
MRESULT SERIAL_putchar(UINT8 nSerialPort, char ch);

/*!
  シリアル入力した１文字を取得します。
  この関数を呼ぶと、文字が入力されるまでブロッキングします。
  ブロッキングしてほしくない場合はSERIAL_getchを使用してください。

  @param nSerialPort  シリアルポート番号を指定(0, 1)
  @return シリアル経由で取得したASCII文字
*/
int SERIAL_getchar(UINT8 nSerialPort);

/*!
  シリアル入力した１文字を取得します。
  SERIAL_getchar関数と異なり、文字が入力されるまでブロッキングしません。
  バッファにデータが存在しない場合は-1を返して処理を終了します。

  @param nSerialPort  シリアルポート番号を指定(0, 1)
  @retval 0～255  シリアル経由で取得したASCII文字
  @retval -1      バッファにデータが存在しなかった
*/
int SERIAL_getch(UINT8 nSerialPort);

/*!
  受信バッファが溢れたかチェックします。
  本関数を呼ぶことで多数の受信割込みにより受信バッファが溢れたかどうか調べることができます。
  本関数を一度呼ぶと受信バッファ溢れのフラグはクリアされます。
  受信バッファが溢れる要因として、データが入力されているにもかかわらず適度な頻度で取得関数
  を呼んでいないなどが考えられます。処理の都合上、頻繁に取得関数を呼ぶことができないなどの
  事情がある場合は、SERIAL_RX_BUFSIZE(moxa_config.hで定義)のサイズを大きくしてみることをお
  勧めします。
  なお、存在しないポート番号を指定したときの結果はFALSEです。

  @param nSerialPort  シリアルポート番号を指定(0, 1)
  @retval TRUE   受信バッファが溢れた
  @retval FALSE  受信バッファが溢れていない
*/
BOOL SERIAL_checkRxOverflow(UINT8 nSerialPort);

/*!
  書式付シリアル出力関数です。
  書式フォーマット文字列の記述はprintf関数に準拠します。
  ただし、CodeVisionのプロジェクト設定 (s)printf Featuresの値によっては使用できない
  出力フォーマットが存在します。
  
  @param nSerialPort  シリアルポート番号を指定(0, 1)
  @param pFmt         出力フォーマット文字列へのポインタ
  @param MOXA_SUCCESS 出力に成功
  @param MOXA_E_PARAM 引数が不正
*/
MRESULT SERIAL_printf(UINT8 nSerialPort, char flash *pFmt, ...);

//#pragma used-

#endif // __SERIAL_H__
