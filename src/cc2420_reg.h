/*!
  @file
  @brief 無線通信チップCC2420のレジスタ情報定義
  @author Takaaki Ishizawa, Vistarica Designs Co.Ltd.
  @date   2006/02/20
  @version 0.1
 */

#ifndef CC2420_REG_H
#define CC2420_REG_H

// コンフィグレーションレジスタアドレス
#define CC2420_SNOP             0x00 //!< NOP
#define CC2420_SXOSCON          0x01 //!< クリスタル発振開始
#define CC2420_STXCAL           0x02 //!< 送信用周波数生成器を動作許可する
#define CC2420_SRXON            0x03 //!< 受信許可
#define CC2420_STXON            0x04 //!< 送信許可
#define CC2420_STXONCCA         0x05 //!< チャンネルが空いていたら送信許可
#define CC2420_SRFOFF           0x06 //!< 全ての送受信と発振を動作禁止
#define CC2420_SXOSCOFF         0x07 //!< 水晶発信器と無線機能の電源を切る
#define CC2420_SFLUSHRX         0x08 //!< 受信バッファのクリア
#define CC2420_SFLUSHTX         0x09 //!< 送信バッファのクリア
#define CC2420_SACK             0x0A //!< pending fieldをクリアしてACKフレームの送信
#define CC2420_SACKPEND         0x0B //!< pending fieldをセットしてACKフレームの送信
#define CC2420_SRXDEC           0x0C //!< 受信復号化の開始
#define CC2420_STXENC           0x0D //!< 送信暗号化の開始
#define CC2420_SAES             0x0E //!< AESストローブ
// not in use                   0x0F
#define CC2420_MAIN             0x10 //!< メインコントロールレジスタ
#define CC2420_MDMCTRL0         0x11 //!< モデムコントロールレジスタ0
#define CC2420_MDMCTRL1         0x12 //!< モデムコントロールレジスタ1
#define CC2420_RSSI             0x13 //!< RSSIとCCA
#define CC2420_SYNCWORD         0x14 //!< Synchronisation wordコントロールレジスタ
#define CC2420_TXCTRL           0x15 //!< 送信コントロールレジスタ
#define CC2420_RXCTRL0          0x16 //!< 受信コントロールレジスタ0
#define CC2420_RXCTRL1          0x17 //!< 受信コントロールレジスタ1
#define CC2420_FSCTRL           0x18 //!< 周波数生成器コントロールレジスタ
#define CC2420_SECCTRL0         0x19 //!< セキュリティコントロールレジスタ0
#define CC2420_SECCTRL1         0x1A //!< セキュリティコントロールレジスタ1
#define CC2420_BATTMON          0x1B //!< バッテリーモニタコントロール/ステータスレジスタ
#define CC2420_IOCFG0           0x1C //!< I/Oコントロールレジスタ0
#define CC2420_IOCFG1           0x1D //!< I/Oコントロールレジスタ1
#define CC2420_MANFIDL          0x1E //!< Manufacturer ID Low word
#define CC2420_MANFIDH          0x1F //!< Manufacturer ID High word
#define CC2420_FSMTC            0x20 //!< 有限ステートマシン時間定数
#define CC2420_MANAND           0x21 //!< ANDマスク手動設定
#define CC2420_MANOR            0x22 //!< ORマスク手動設定
#define CC2420_AGCCTRL          0x23 //!< AGCコントロールレジスタ
#define CC2420_AGCTST0          0x24 //!< AGCテストレジスタ0
#define CC2420_AGCTST1          0x25 //!< AGCテストレジスタ1
#define CC2420_AGCTST2          0x26 //!< AGCテストレジスタ2
#define CC2420_FSTST0           0x27 //!< 周波数生成器テストレジスタ0
#define CC2420_FSTST1           0x28 //!< 周波数生成器テストレジスタ1
#define CC2420_FSTST2           0x29 //!< 周波数生成器テストレジスタ2
#define CC2420_FSTST3           0x2A //!< 周波数生成器テストレジスタ3
#define CC2420_RXBPFTST         0x2B //!< 受信バンドパスフィルタテストレジスタ
#define CC2420_FSMSTATE         0x2C //!< 有限ステートマシンステータスレジスタ
#define CC2420_ADCTST           0x2D //!< ADCテストレジスタ
#define CC2420_DACTST           0x2E //!< DACテストレジスタ
#define CC2420_TOPTST           0x2F //!< トップレベルテストレジスタ
#define CC2420_RESERVED         0x30 //!< 予約
// not in use             from  0x31
//                        to    0x3D
#define CC2420_TXFIFO           0x3E //!< 送信FIFOバッファ
#define CC2420_RXFIFO           0x3F //!< 受信FIFOバッファ

// メモリサイズ定義
#define CC2420_RAM_SIZE         368 //!< RAMサイズ
#define CC2420_FIFO_SIZE        128 //!< FIFOサイズ

// RAMメモリ空間内アドレス
#define CC2420RAM_TXFIFO        0x000
#define CC2420RAM_RXFIFO        0x080
#define CC2420RAM_KEY0          0x100
#define CC2420RAM_RXNONCE       0x110
#define CC2420RAM_SABUF         0x120
#define CC2420RAM_KEY1          0x130
#define CC2420RAM_TXNONCE       0x140
#define CC2420RAM_CBCSTATE      0x150
#define CC2420RAM_IEEEADDR      0x160
#define CC2420RAM_PANID         0x168
#define CC2420RAM_SHORTADDR     0x16A

// ステータスバイトビットマスク
// reserved                     7
#define CC2420_XOSC16M_STABLE   6
#define CC2420_TX_UNDERFLOW     5
#define CC2420_ENC_BUSY         4
#define CC2420_TX_ACTIVE        3
#define CC2420_LOCK             2
#define CC2420_RSSI_VALID       1
// reserved                     0

#endif
