/*!
  @file
  @brief ATMEGA128のレジスタ情報定義
  @author Shinji Yamachika, Vistarica Designs Co.Ltd.
  @date   2005/11/17
  @version 0.1
*/

#ifndef __MEGA128_REG_H__
#define __MEGA128_REG_H__

// TWIビットレートレジスター (TWI Bit Rate Register) TWBR
#define TWBR7  7      //!< TWIビットレート選択 bit7
#define TWBR6  6      //!< TWIビットレート選択 bit6
#define TWBR5  5      //!< TWIビットレート選択 bit5
#define TWBR4  4      //!< TWIビットレート選択 bit4
#define TWBR3  3      //!< TWIビットレート選択 bit3
#define TWBR2  2      //!< TWIビットレート選択 bit2
#define TWBR1  1      //!< TWIビットレート選択 bit1
#define TWBR0  0      //!< TWIビットレート選択 bit0


// TWI制御レジスタ (TWI Control Register) TWCR
#define TWINT  7      //!< TWI割り込み要求フラグ
#define TWEA   6      //!< 確認応答(ACK)許可
#define TWSTA  5      //!< 開始(START)条件生成許可
#define TWSTO  4      //!< 停止(STOP)条件生成許可
#define TWWC   3      //!< TWI上書きエラーフラグ
#define TWEN   2      //!< TWI動作許可
                      //   1bit目は予約されています
#define TWIE   0      //!< TWI割り込み許可


// TWIステータスレジスタ (TWI Status Register) TWSR
#define TWS7   7      //!< TWIステータス bit7
#define TWS6   6      //!< TWIステータス bit6
#define TWS5   5      //!< TWIステータス bit5
#define TWS4   4      //!< TWIステータス bit4
#define TWS3   3      //!< TWIステータス bit3
                      //   2bit目は予約されています
#define TWPS1  1      //!< TWI 前置分周選択
#define TWPS0  0      //!< TWI 前置分周選択


// TWIデータレジスタ (TWI Data Register) TWDR
#define TWD7   7      //!< TWIデータ bit7
#define TWD6   6      //!< TWIデータ bit6
#define TWD5   5      //!< TWIデータ bit5
#define TWD4   4      //!< TWIデータ bit4
#define TWD3   3      //!< TWIデータ bit3
#define TWD2   2      //!< TWIデータ bit2
#define TWD1   1      //!< TWIデータ bit1
#define TWD0   0      //!< TWIデータ bit0


// TWIスレーブアドレスレジスタ (TWI Slave Address Register) TWAR
#define TWA6   7      //!< TWIスレーブアドレス bit6
#define TWA5   6      //!< TWIスレーブアドレス bit5
#define TWA4   5      //!< TWIスレーブアドレス bit4
#define TWA3   4      //!< TWIスレーブアドレス bit3
#define TWA2   3      //!< TWIスレーブアドレス bit2
#define TWA1   2      //!< TWIスレーブアドレス bit1
#define TWA0   1      //!< TWIスレーブアドレス bit0
#define TWGCE  0      //!< 一斉呼び出し検出許可


// MCU制御レジスタ (MCU Control Register) MCUCR
#define SRE    7      //!< 外部メモリ許可
#define SRW    6      //!< ウェイト選択ビット
#define SRW10  6      //!< 上位領域ウェイト選択ビット0
#define SE     5      //!< スリープ許可
#define SM1    4      //!< スリープ種別選択 bit1
#define SM0    3      //!< スリープ種別選択 bit0
#define SM2    2      //!< スリープ種別選択 bit2
#define IVSEL  1      //!< 割り込みベクタ選択
#define IVCE   0      //!< 割り込みベクタ変更許可


// 外部メモリ制御レジスタA (External Memory Control Register A) XMCRA
                      //   7bit目は予約されています
#define SRL2   6      //!< 外部SRAM範囲選択 bit2
#define SRL1   5      //!< 外部SRAM範囲選択 bit1
#define SRL0   4      //!< 外部SRAM範囲選択 bit0
#define SRW01  3      //!< 下位領域ｳｪｲﾄ選択 bit1
#define SRW00  2      //!< 下位領域ｳｪｲﾄ選択 bit0
#define SRW11  1      //!< 上位領域ｳｪｲﾄ選択 bit1


// 外部メモリ制御レジスタB (External Memory Control Register B) XMCRB
#define XMBK   7      //!< バス保持許可
#define XMM2   2      //!< 上位アドレスマスク bit2
#define XMM1   1      //!< 上位アドレスマスク bit1
#define XMM0   0      //!< 上位アドレスマスク bit0


// クロック分周制御レジスタ (XTAL Divide Control Register) XDIV
#define XDIVEN 7      //!< クロック分周許可
#define XDIV6  6      //!< クロック分周値選択 bit6
#define XDIV5  5      //!< クロック分周値選択 bit5
#define XDIV4  4      //!< クロック分周値選択 bit4
#define XDIV3  3      //!< クロック分周値選択 bit3
#define XDIV2  2      //!< クロック分周値選択 bit2
#define XDIV1  1      //!< クロック分周値選択 bit1
#define XDIV0  0      //!< クロック分周値選択 bit0


// RAMページ選択レジスタ (RAM Page Z Select Register) RAMPZ
#define RAMPZ0 0      //!< 拡張RAMページ Zポインタ


// 外部割り込み制御レジスタA (External Interrupt Control Register A) EICRA
#define ISC31  7      //!< 外部割り込み3条件制御
#define ISC30  6      //!< 外部割り込み3条件制御
#define ISC21  5      //!< 外部割り込み2条件制御
#define ISC20  4      //!< 外部割り込み2条件制御
#define ISC11  3      //!< 外部割り込み1条件制御
#define ISC10  2      //!< 外部割り込み1条件制御
#define ISC01  1      //!< 外部割り込み0条件制御
#define ISC00  0      //!< 外部割り込み0条件制御


// 外部割り込み制御レジスタB (External Interrupt Control Register B) EICRB
#define ISC71  7      //!< 外部割り込み7条件制御
#define ISC70  6      //!< 外部割り込み7条件制御
#define ISC61  5      //!< 外部割り込み6条件制御
#define ISC60  4      //!< 外部割り込み6条件制御
#define ISC51  3      //!< 外部割り込み5条件制御
#define ISC50  2      //!< 外部割り込み5条件制御
#define ISC41  1      //!< 外部割り込み4条件制御
#define ISC40  0      //!< 外部割り込み4条件制御


// 外部割り込みマスクレジスタ (External Interrupt Mask Register) EIMSK
#define INT7   7      //!< 外部割り込み7 許可
#define INT6   6      //!< 外部割り込み6 許可
#define INT5   5      //!< 外部割り込み5 許可
#define INT4   4      //!< 外部割り込み4 許可
#define INT3   3      //!< 外部割り込み3 許可
#define INT2   2      //!< 外部割り込み2 許可
#define INT1   1      //!< 外部割り込み1 許可
#define INT0   0      //!< 外部割り込み0 許可


// 外部割り込み要求フラグレジスタ (External Interrupt Flag Register) EIFR
#define INTF7  7      //!< 外部割り込み7要求フラグ
#define INTF6  6      //!< 外部割り込み6要求フラグ
#define INTF5  5      //!< 外部割り込み5要求フラグ
#define INTF4  4      //!< 外部割り込み4要求フラグ
#define INTF3  3      //!< 外部割り込み3要求フラグ
#define INTF2  2      //!< 外部割り込み2要求フラグ
#define INTF1  1      //!< 外部割り込み1要求フラグ
#define INTF0  0      //!< 外部割り込み0要求フラグ


// SPM命令制御/ステータスレジスタ (Store Program Memory Controll and Status Register) SPMCRS
#define SPMIE  7      //!< SPM操作可割り込み許可
#define RWWSB  6      //!< RWW領域美ジー
#define RWWSRE 4      //!< RWW領域読み出し許可
#define BLBSET 3      //!< ブートロックビット設定
#define PGWRT  2      //!< ページ書き込み
#define PGERS  1      //!< ページ消去
#define SPMEN  0      //!< SPM操作許可


// タイマ/カウンタ0 制御レジスタ (Timer/Counter0 Control Register) TCCR0
#define FOC0   7      //!< OC0強制変更
#define WGM00  6      //!< 波形生成種別
#define COM01  5      //!< 比較0出力選択
#define COM00  4      //!< 比較0出力選択
#define WGM01  3      //!< 波形生成種別
#define CS02   2      //!< クロック選択2
#define CS01   1      //!< クロック選択1
#define CS00   0      //!< クロック選択0


// タイマ/カウンタ割り込みマスク レジスタ (Timer/Counter Interrupt Mask Register) TIMSK
#define OCIE2  7      //!< タイマ/カウンタ2 比較割り込み許可
#define TOIE2  6      //!< タイマ/カウンタ2 オーバーフロー割り込み許可
#define TICIE1 5      //!< タイマ/カウンタ1 捕獲(キャプチャ)割り込み許可
#define OCIE1A 4      //!< タイマ/カウンタ1 比較A割り込み許可
#define OCIE1B 3      //!< タイマ/カウンタ1 比較B割り込み許可
#define TOIE1  2      //!< タイマ/カウンタ1 オーバーフロー割り込み許可
#define OCIE0  1      //!< タイマ/カウンタ0 比較割り込み許可
#define TOIE0  0      //!< タイマ/カウンタ0 オーバーフロー割り込み許可


// タイマ/カウンタ割り込み要求フラグレジスタ (Timer/Counter Interrupt Flag Register) TIFR
#define OCF2   7      //!< タイマ/カウンタ2 比較割り込み要求フラグ
#define TOV2   6      //!< タイマ/カウンタ2 オーバーフロー割り込み要求フラグ
#define ICF1   5      //!< キャプチャ割込み要求フラグ
#define OCF1A  4      //!< 比較要求割込みフラグ1A
#define OCF1B  3      //!< 比較要求割込みフラグ1B
#define TOV1   2      //!< タイマ/カウンタ オーバーフローフラグ
#define OCF0   1      //!< タイマ/カウンタ0 比較割り込み要求フラグ
#define TOV0   0      //!< タイマ/カウンタ0 オーバーフロー割り込み要求フラグ


// タイマ/カウンタ0非同期ステータスレジスタ (Timer/Counter0 Asynchronous Status Register) ASSR
#define AS0    3      //!< タイマ/カウンタ0非同期動作許可
#define TCN0UB 2      //!< タイマ/カウンタ0更新中フラグ
#define OCR0UB 1      //!< 比較0レジスタ更新中フラグ
#define TCR0UB 0      //!< タイマ/カウンタ0制御レジスタ更新中フラグ


// 特殊I/O機能レジスタ (Special Function I/O Register) SFIOR
#define TSM    7      //!< タイマ/カウンタ同時動作モード
#define ADHSM  4      //!< この機能は削除されました、現在4bit目は予約されています
#define ACME   3      //!< アナログ比較器マルチプレクサ許可
#define PUD    2      //!< プルアップ禁止ビット
#define PSR0   1      //!< タイマ/カウンタ0 前置分周器リセット
#define PSR321 0      //!< タイマ/カウンタ3,2,1 前置分周器リセット


// タイマ/カウンタ1制御レジスタA (Timer/Counter1 Control Register A) TCCR1A
#define COM1A1 7      //!< 比較1A出力選択 bit1
#define COM1A0 6      //!< 比較1A出力選択 bit0
#define COM1B1 5      //!< 比較1B出力選択 bit1
#define COM1B0 4      //!< 比較1B出力選択 bit0
#define COM1C1 3      //!< 比較1C出力選択 bit1
#define COM1C0 2      //!< 比較1C出力選択 bit0
#define WGM11  1      //!< 波形生成種別 bit1
#define WGM10  0      //!< 波形生成種別 bit0


// タイマ/カウンタ3制御レジスタA (Timer/Counter3 Control Register A) TCCR3A
#define COM3A1 7      //!< 比較3A出力選択 bit1
#define COM3A0 6      //!< 比較3A出力選択 bit0
#define COM3B1 5      //!< 比較3B出力選択 bit1
#define COM3B0 4      //!< 比較3B出力選択 bit0
#define COM3C1 3      //!< 比較3C出力選択 bit1
#define COM3C0 2      //!< 比較3C出力選択 bit0
#define WGM31  1      //!< 波形生成種別 bit1
#define WGM30  0      //!< 波形生成種別 bit0


// タイマ/カウンタ1制御レジスタB (Timer/Counter1 Control Register B) TCCR1B
#define ICNC1  7      //!< キャプチャ起動入力1 ノイズ消去許可
#define ICES1  6      //!< キャプチャ起動入力1 エッジ選択
                      //   5bit目は予約されています
#define WGM13  4      //!< 波形生成モードの指定
#define WGM12  3      //!< 波形生成モードの指定
#define CS12   2      //!< クロック選択2
#define CS11   1      //!< クロック選択1
#define CS10   0      //!< クロック選択0


// タイマ/カウンタ3制御レジスタB (Timer/Counter3 Control Register B) TCCR3B
#define ICNC3  7      //!< キャプチャ起動入力3 ノイズ消去許可
#define ICES3  6      //!< キャプチャ起動入力3 エッジ選択
                      //   5bit目は予約されています
#define WGM33  4      //!< 波形生成モードの指定
#define WGM32  3      //!< 波形生成モードの指定
#define CS32   2      //!< クロック選択2
#define CS31   1      //!< クロック選択1
#define CS30   0      //!< クロック選択0


// タイマ/カウンタ1制御レジスタC (Timer/Counter1 Control Register C) TCCR1C
#define FOC1A  7      //!< OC1A強制変更
#define FOC1B  6      //!< OC1B強制変更
#define FOC1C  5      //!< OC1B強制変更


// タイマ/カウンタ3制御レジスタC (Timer/Counter3 Control Register C) TCCR1C
#define FOC3A  7      //!< OC3A強制変更
#define FOC3B  6      //!< OC3B強制変更
#define FOC3C  5      //!< OC3C強制変更


// 拡張タイマ/カウンタ割り込みマスクレジスタ
// (Extended Timer/Counter Interrupt Mask Register) ETIMSK
                      //   7,6bit目は予約されています
#define TICIE3 5      //!< タイマ/カウンタ3 キャプチャ割り込み許可
#define OCIE3A 4      //!< タイマ/カウンタ3 比較A割り込み許可
#define OCIE3B 3      //!< タイマ/カウンタ3 比較B割り込み許可
#define TOIE3  2      //!< タイマ/カウンタ3 オーバーフロー割り込み許可
#define OCIE3C 1      //!< タイマ/カウンタ3 比較C割り込み許可
#define OCIE1C 0      //!< タイマ/カウンタ1 比較C割り込み許可


// 拡張タイマ/カウンタ割り込み要求フラグレジスタ
// (Extended Timer/Counter Interrupt Flag Register) ETIFR
                      //   7,6bit目は予約されています
#define ICF3   5      //!< タイマ/カウンタ3 キャプチャ割り込み要求フラグ
#define OCF3A  4      //!< タイマ/カウンタ3 比較A割り込み要求フラグ
#define OCF3B  3      //!< タイマ/カウンタ3 比較B割り込み要求フラグ
#define TOV3   2      //!< タイマ/カウンタ3 オーバーフロー割り込み要求フラグ
#define OCF3C  1      //!< タイマ/カウンタ3 比較C割り込み要求フラグ
#define OCF1C  0      //!< タイマ/カウンタ1 比較C割り込み要求フラグ


// 8bit タイマ/カウンタ2制御レジスタ (Timer/Counter2 Control Register) TCCR2
#define FOC2   7      //!< OC2強制変更
#define WGM20  6      //!< 波形生成モードの指定 bit0
#define COM21  5      //!< 比較2出力選択モードの指定 bit1
#define COM20  4      //!< 比較2出力選択モードの指定 bit0
#define WGM21  3      //!< 波形生成モードの指定 bit1
#define CS22   2      //!< クロック選択2 bit2
#define CS21   1      //!< クロック選択2 bit1
#define CS20   0      //!< クロック選択2 bit0


// SPI制御レジスタ (SPI Control Register) SPCR
#define SPIE   7      //!< SPI割り込み許可
#define SPE    6      //!< SPI許可
#define DORD   5      //!< データ順選択
#define MSTR   4      //!< マスタ/スレーブ選択
#define CPOL   3      //!< SCK極性選択
#define CPHA   2      //!< SCK位相選択
#define SPR1   1      //!< SPIクロック選択 bit1
#define SPR0   0      //!< SPIクロック選択 bit0


// タイマ/カウンタ 制御レジスタ
#define FOC    7      //!< OC0強制変更
#define WGM0   6      //!< 波形生成種別
#define COM1   5      //!< 比較0出力選択
#define COM0   4      //!< 比較0出力選択
#define WGM1   3      //!< 波形生成種別
#define CS2    2      //!< クロック選択2
#define CS1    1      //!< クロック選択1
#define CS0    0      //!< クロック選択0


// タイマ/カウンタ 制御レジスタA
#define COMA1  7
#define COMA0  6
#define COMB1  5
#define COMB0  4
#define COMC1  3
#define COMC0  2
#define WGMA1  1
#define WGMA0  0


// タイマ/カウンタ 制御/ステータスレジスタB
#define ICNC   7
#define ICES   6
#define WGMB3  4
#define WGMB2  3
#define CSB2   2
#define CSB1   1
#define CSB0   0


// タイマ/カウンタ 制御レジスタC
#define FOCA   7
#define FOCB   6
#define FOCC   5


// 内蔵デバッグレジスタ (On-chip Debug Register) OCDR
#define IDRD   7
#define OCDR7  7
#define OCDR6  6
#define OCDR5  5
#define OCDR4  4
#define OCDR3  3
#define OCDR2  2
#define OCDR1  1
#define OCDR0  0


// ウォッチドッグタイマ制御レジスタ (Watchdog Timer Control Register) WDTCR
                      //   7,6,5bit目は予約されています
#define WDCE   4      //!< ウォッチドッグ変更許可
#define WDE    3      //!< ウォッチドッグ許可
#define WDP2   2      //!< ウォッチドッグタイマ前置分周選択 bit2
#define WDP1   1      //!< ウォッチドッグタイマ前置分周選択 bit1
#define WDP0   0      //!< ウォッチドッグタイマ前置分周選択 bit0


// SPIステータスレジスタ (SPI Status Register) SPSR
#define SPIF   7      //!< SPI割り込み要求フラグ
#define WCOL   6      //!< 上書きエラーフラグ
                      //   5,4,3,2,1bit目は予約されています
#define SPI2X  0      //!< SPI倍速許可


// 汎用USART制御レジスタA (USART Control Register A)
#define RXC    7      //!< USART受信完了フラグ
#define TXC    6      //!< USART0送信完了フラグ
#define UDRE   5      //!< USART0送信データレジスタ空きフラグ
#define FE     4      //!< フレーミングエラーフラグ
#define DOR    3      //!< データオーバーランエラーフラグ
#define UPE    2      //!< パリティエラーフラグ
#define U2X    1      //!< 倍速許可
#define MPCM   0      //!< マルチプロセッサ通信モード


// USART0制御/ステータスレジスタA (USART0 Control and Status Register A) UCSR0A
#define RXC0   7      //!< USART0受信完了フラグ
#define TXC0   6      //!< USART0送信完了フラグ
#define UDRE0  5      //!< USART0送信データレジスタ空きフラグ
#define FE0    4      //!< フレーミングエラーフラグ
#define DOR0   3      //!< データオーバーランエラーフラグ
#define UPE0   2      //!< パリティエラーフラグ
#define U2X0   1      //!< 倍速許可
#define MPCM0  0      //!< マルチプロセッサ通信モード


// USART1制御/ステータスレジスタA (USART1 Control and Status Register A) UCSR1A
#define RXC1   7      //!< USART1受信完了フラグ
#define TXC1   6      //!< USART1送信完了フラグ
#define UDRE1  5      //!< USART1送信データレジスタ空きフラグ
#define FE1    4      //!< フレーミングエラーフラグ
#define DOR1   3      //!< データオーバーランエラーフラグ
#define UPE1   2      //!< パリティエラーフラグ
#define U2X1   1      //!< 倍速許可
#define MPCM1  0      //!< マルチプロセッサ通信モード


// 汎用USART制御レジスタB (USART Control Register B)
#define RXCIE  7      //!< 受信完了割り込み許可
#define TXCIE  6      //!< 送信完了割り込み許可
#define UDRIE  5      //!< 送信データレジスタ空き割り込み許可
#define RXEN   4      //!< 受信許可
#define TXEN   3      //!< 送信許可
#define UCSZ   2      //!< データビット長選択
#define UCSZ2  2      //!< データビット長選択2
#define RXB8   1      //!< 受信データビット
#define TXB8   0      //!< 送信データビット


// USART0制御/ステータスレジスタB (USART0 Control and Status Register B) UCSR0B
#define RXCIE0 7      //!< 受信完了割り込み許可
#define TXCIE0 6      //!< 送信完了割り込み許可
#define UDRIE0 5      //!< 送信データレジスタ空き割り込み許可
#define RXEN0  4      //!< 受信許可
#define TXEN0  3      //!< 送信許可
#define UCSZ02 2      //!< データビット長選択2
#define RXB80  1      //!< 受信データビット
#define TXB80  0      //!< 送信データビット


// USART1制御/ステータスレジスタB (USART1 Control and Status Register B) UCSR1B
#define RXCIE1 7      //!< 受信完了割り込み許可
#define TXCIE1 6      //!< 送信完了割り込み許可
#define UDRIE1 5      //!< 送信データレジスタ空き割り込み許可
#define RXEN1  4      //!< 受信許可
#define TXEN1  3      //!< 送信許可
#define UCSZ12 2      //!< データビット長選択2
#define RXB81  1      //!< 受信データビット
#define TXB81  0      //!< 送信データビット


// 汎用USARTレジスタC (USART Register C)
                      //   7bit目は予約されています
#define UMSEL  6      //!< USART0動作選択
#define UPM1   5      //!< パリティ選択 1bit
#define UPM0   4      //!< パリティ選択 0bit
#define USBS   3      //!< ストップビット選択
#define UCSZ1  2      //!< データビット長選択 1bit
#define UCSZ0  1      //!< データビット長選択 0bit
#define UCPOL  0      //!< クロック極性選択


// USART0制御/ステータスレジスタC (USART0 Control and Status Register C) UCSR0C
                      //   7bit目は予約されています
#define UMSEL0 6      //!< USART0動作選択
#define UPM01  5      //!< パリティ選択 1bit
#define UPM00  4      //!< パリティ選択 0bit
#define USBS0  3      //!< ストップビット選択
#define UCSZ01 2      //!< データビット長選択 1bit
#define UCSZ00 1      //!< データビット長選択 0bit
#define UCPOL0 0      //!< クロック極性選択


// USART1制御/ステータスレジスタC (USART1 Control and Status Register C) UCSR1C
                      //   7bit目は予約されています
#define UMSEL1 6      //!< USART1動作選択
#define UPM11  5      //!< パリティ選択 1bit
#define UPM10  4      //!< パリティ選択 0bit
#define USBS1  3      //!< ストップビット選択
#define UCSZ11 2      //!< データビット長選択 1bit
#define UCSZ10 1      //!< データビット長選択 0bit
#define UCPOL1 0      //!< クロック極性選択


// A/D変換チャンネル選択レジスタ (ADC Multiplexer Select Register) ADMUX
#define REFS1  7      //!< 基準電圧選択 bit1
#define REFS0  6      //!< 基準電圧選択 bit0
#define ADLAR  5      //!< 左揃え選択
#define MUX4   4      //!< A/Dチャンネル選択bit4
#define MUX3   3      //!< A/Dチャンネル選択bit3
#define MUX2   2      //!< A/Dチャンネル選択bit2
#define MUX1   1      //!< A/Dチャンネル選択bit1
#define MUX0   0      //!< A/Dチャンネル選択bit0


// A/D変換 制御/ステータスレジスタA (ADC Control and Status Register A) ADCSRA
#define ADEN   7      //!< A/D許可
#define ADSC   6      //!< A/D変換開始
#define ADFR   5      //!< 連続/単独変換動作選択
#define ADIF   4      //!< A/D変換完了割り込み要求フラグ
#define ADIE   3      //!< A/D変換完了割り込み許可
#define ADPS2  2      //!< A/D変換クロック選択 bit2
#define ADPS1  1      //!< A/D変換クロック選択 bit1
#define ADPS0  0      //!< A/D変換クロック選択 bit0


// アナログ比較器 制御/ステータスレジスタ (Analog Comparator Control and Status Register) ACSR
#define ACD    7      //!< アナログ比較器禁止
#define ACBG   6      //!< 基準電圧選択
#define ACO    5      //!< アナログ比較器出力
#define ACI    4      //!< アナログ比較器割り込み要求フラグ
#define ACIE   3      //!< アナログ比較器割り込み許可
#define ACIC   2      //!< アナログ比較器キャプチャ起動許可
#define ACIS1  1      //!< アナログ比較器割り込み条件 bit1
#define ACIS0  0      //!< アナログ比較器割り込み条件 bit0


// MCU制御/ステータスレジスタ (MCU Control and Status Register) MCUCSR
#define JTD    7      //!< JTAGインターフェイス禁止
                      //   5,6bit目は予約されています
#define JTRF   4      //!< JTAGリセットフラグ
#define WDRF   3      //!< ウォッチドッグリセットフラグ
#define BORF   2      //!< 低電圧リセットフラグ
#define EXTRF  1      //!< 外部リセットフラグ
#define PORF   0      //!< 電源ONリセットフラグ


// ポートA 出力レジスタ (Port A Data Register) PORTA
#define PA7    7
#define PA6    6
#define PA5    5
#define PA4    4
#define PA3    3
#define PA2    2
#define PA1    1
#define PA0    0


// ポートA データ方向レジスタ (Port A Data Direction Register) DDRA
#define DDA7   7
#define DDA6   6
#define DDA5   5
#define DDA4   4
#define DDA3   3
#define DDA2   2
#define DDA1   1
#define DDA0   0


// ポートA 入力レジスタ (Port A Input Address) PINA
#define PINA7  7
#define PINA6  6
#define PINA5  5
#define PINA4  4
#define PINA3  3
#define PINA2  2 
#define PINA1  1
#define PINA0  0


// ポートB 出力レジスタ (Port B Data Register) PORTB
#define PB7    7
#define PB6    6
#define PB5    5
#define PB4    4
#define PB3    3
#define PB2    2
#define PB1    1
#define PB0    0


// ポートB データ方向レジスタ (Port B Data Direction Register) DDRB
#define DDB7   7
#define DDB6   6
#define DDB5   5
#define DDB4   4
#define DDB3   3
#define DDB2   2
#define DDB1   1
#define DDB0   0


// ポートB 入力レジスタ (Port B Input Address) PINB
#define PINB7  7
#define PINB6  6
#define PINB5  5
#define PINB4  4
#define PINB3  3
#define PINB2  2 
#define PINB1  1
#define PINB0  0


// ポートC 出力レジスタ (Port C Data Register) PORTC
#define PC7    7
#define PC6    6
#define PC5    5
#define PC4    4
#define PC3    3
#define PC2    2
#define PC1    1
#define PC0    0


// ポートC データ方向レジスタ (Port C Data Direction Register) DDRC
#define DDC7   7
#define DDC6   6
#define DDC5   5
#define DDC4   4
#define DDC3   3
#define DDC2   2
#define DDC1   1
#define DDC0   0


// ポートC 入力レジスタ (Port C Input Address) PINC
#define PINC7  7
#define PINC6  6
#define PINC5  5
#define PINC4  4
#define PINC3  3
#define PINC2  2 
#define PINC1  1
#define PINC0  0


// ポートD 出力レジスタ (Port D Data Register) PORTD
#define PD7    7
#define PD6    6
#define PD5    5
#define PD4    4
#define PD3    3
#define PD2    2
#define PD1    1
#define PD0    0


// ポートD データ方向レジスタ (Port D Data Direction Register) DDRD
#define DDD7   7
#define DDD6   6
#define DDD5   5
#define DDD4   4
#define DDD3   3
#define DDD2   2
#define DDD1   1
#define DDD0   0


// ポートD 入力レジスタ (Port D Input Address) PIND
#define PIND7  7
#define PIND6  6
#define PIND5  5
#define PIND4  4
#define PIND3  3
#define PIND2  2 
#define PIND1  1
#define PIND0  0


// ポートE 出力レジスタ (Port E Data Register) PORTE
#define PE7    7
#define PE6    6
#define PE5    5
#define PE4    4
#define PE3    3
#define PE2    2
#define PE1    1
#define PE0    0


// ポートE データ方向レジスタ (Port E Data Direction Register) DDRE
#define DDE7   7
#define DDE6   6
#define DDE5   5
#define DDE4   4
#define DDE3   3
#define DDE2   2
#define DDE1   1
#define DDE0   0


// ポートE 入力レジスタ (Port E Input Address) PINE
#define PINE7  7
#define PINE6  6
#define PINE5  5
#define PINE4  4
#define PINE3  3
#define PINE2  2 
#define PINE1  1
#define PINE0  0


// ポートF 出力レジスタ (Port F Data Register) PORTF
#define PF7    7
#define PF6    6
#define PF5    5
#define PF4    4
#define PF3    3
#define PF2    2
#define PF1    1
#define PF0    0


// ポートF データ方向レジスタ (Port F Data Direction Register) DDRF
#define DDF7   7
#define DDF6   6
#define DDF5   5
#define DDF4   4
#define DDF3   3
#define DDF2   2
#define DDF1   1
#define DDF0   0


// ポートF 入力レジスタ (Port F Input Address) PINF
#define PINF7  7
#define PINF6  6
#define PINF5  5
#define PINF4  4
#define PINF3  3
#define PINF2  2 
#define PINF1  1
#define PINF0  0


// ポートG 出力レジスタ (Port G Data Register) PORTG
#define PG4    4
#define PG3    3
#define PG2    2
#define PG1    1
#define PG0    0


// ポートG データ方向レジスタ (Port G Data Direction Register) DDRG
#define DDG4   4
#define DDG3   3
#define DDG2   2
#define DDG1   1
#define DDG0   0


// ポートG 入力レジスタ (Port G Input Address) PING
#define PING4  4
#define PING3  3
#define PING2  2 
#define PING1  1
#define PING0  0

/* Constants */
#define SPM_PAGESIZE  256
#define RAMEND        0x10FF     //!< 内蔵SRAMの終端を表します
#define XRAMEND       0xFFFF     //!< RAMメモリ空間の終端を表します
#define E2END         0x0FFF
#define FLASHEND      0x1FFFF

#endif /* __MEGA128_REG_H__ */
