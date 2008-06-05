/*!
  @file
  @brief ドライバ関係の設定マクロ

  MOXAライブラリでは、MCUと特別な結線で接続しているデバイスの処理を規定したソフトウェアの
  ことをドライバと呼んでいます。
  通常のデバイスはデバイスポートと呼ぶ抽象ポートに対して接続されますが、ドライバは特別な
  事情により接続をMCUのI/Oポート単位で指定する必要があります。
  その指定を本ファイルで行なってください。
  各ドライバごとに接続I/Oポートの設定を記述してください。
  また、新しくデバイスを作成したとき、それをドライバとして定義する場合は本ファイルに設定を
  追加してください。
  
  @author Shinji Yamachika
  @date   2005/12/16
  @version 0.1
 */
#ifndef __MOXA_DRIVER_H__
#define __MOXA_DRIVER_H__

/**************************************************************************************
  SHT11 (humidity and temperature sensor) settings
***************************************************************************************/

// SHT11 I/O settings
#define	CHIP_SHT11_CLK_OUT_BIT      __IN(PORTE,4)       //!< クロックビット番号の指定
#define	CHIP_SHT11_CLK_DIR_BIT      __IN(DDRE,4)        //!< クロック方向の指定
#define	CHIP_SHT11_DATA_OUT_BIT     __IN(PORTE,5)       //!< 出力ビット番号の指定
#define	CHIP_SHT11_DATA_IN_BIT      __IN(PINE,5)        //!< 入力ビット番号の指定
#define	CHIP_SHT11_DATA_DIR_BIT     __IN(DDRE,5)        //!< データ方向の指定

#define	CHIP_SHT11_CLK_OUT_BIT_(s)      __OUT(PORTE,4,s)       //!< クロックビット番号の指定
#define	CHIP_SHT11_CLK_DIR_BIT_(s)      __OUT(DDRE,4,s)        //!< クロック方向の指定
#define	CHIP_SHT11_DATA_OUT_BIT_(s)     __OUT(PORTE,5,s)       //!< 出力ビット番号の指定
#define	CHIP_SHT11_DATA_IN_BIT_(s)      __OUT(PINE,5,s)        //!< 入力ビット番号の指定
#define	CHIP_SHT11_DATA_DIR_BIT_(s)     __OUT(DDRE,5,s)        //!< データ方向の指定

#undef CHIP_SHT11_USE_DEW_POINT   //!< 結露温度を求める関数を使用するマクロ

#endif // __MOXA_DRIVER_H__
