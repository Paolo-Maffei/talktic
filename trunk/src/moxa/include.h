/*!
  @file
  @brief MOXA共通型の定義
  @author Shinji Yamachika, Vistarica Designs Co.Ltd.
  @date   2005/12/7
  @version 0.1
*/
#ifndef __INCLUDE_H__
#define __INCLUDE_H__

// データ長定義型
// MCUを変更したときはここの定義を一度見直してください
#if defined _CHIP_ATMEGA128_ | defined _CHIP_ATMEGA128L_
typedef unsigned char		BOOL;     //!< 二値を明示するとき使用してください

typedef unsigned char		BYTE;     //!< 符号なし1Byte型を明示するとき使用してください
typedef unsigned short		WORD;     //!< 符号なし2Byte型を明示するとき使用してください
typedef unsigned long		DWORD;    //!< 符号なし4Byte型を明示するとき使用してください

typedef unsigned char		UINT8;    //!< 符号なし1Byte型を明示するとき使用してください
typedef unsigned short		UINT16;   //!< 符号なし2Byte型を明示するとき使用してください
typedef unsigned long		UINT32;   //!< 符号なし4Byte型を明示するとき使用してください

typedef signed char			INT8;     //!< 符号あり1Byte型を明示するとき使用してください
typedef signed short		INT16;    //!< 符号あり2Byte型を明示するとき使用してください
typedef signed long			INT32;    //!< 符号あり4Byte型を明示するとき使用してください
#endif

// 共通値
#ifndef FALSE
#define FALSE 0    //!< BOOL型に対して偽の値を明示するとき使用してください
#endif

#ifndef TRUE
#define TRUE 1     //!< BOOL型に対して真の値を明示するとき使用してください
#endif

#ifndef NULL
#define NULL 0     //!< ANSIで規定されているNULL型です（stdio.hを使用しないときのために定義してあります）
#endif

// 汎用マクロ
#define BM(n)     (1 << (n))                 //!< nに指定したビットだけ立っている値を生成します
#define BF(x,b,s) (((x) & (b)) >> (s))       //!< xとbの論理積をsビット右シフトした値を生成します
#define MIN(n,m)  (((n) < (m)) ? (n) : (m))  //!< nとmのうち小さい方の値を返します
#define MAX(n,m)  (((n) < (m)) ? (m) : (n))  //!< nとmのうち大きい方の値を返します
#define ABS(n)    (((n) < 0) ? (-(n)) : (n)) //!< nの絶対値を返します

// 関数ポインタ型
typedef void (*VFPTR)(void);   //!< VFPTRが、戻り値void・引数voidの関数ポインタ型を表します

#endif // __INCLUDE_H__
