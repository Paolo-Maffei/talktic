/*!
  @file
  @brief 無線通信チップCC2420の処理関数定義
  @author Shinji Yamachika, Vistarica Designs Co.Ltd.
  @date   2005/12/7
  @version 0.1
*/
#ifndef __CHIP_CC2420_H__
#define __CHIP_CC2420_H__

#include "moxa_config.h"

//#include <io.h>
#include <string.h>

#include "mega128_macro.h"
#include "cc2420_macro.h"
#include "cc2420_reg.h"
#include "board.h"

#include "radio_packet.h"

//#pragma used+

// Constants concerned with the RF packet format

// Packet overhead
// ((frame control field, sequence number, PAN ID, destination and source) + (footer))
// Note that the length byte itself is not included included in the packet length
#define CC2420_PACKET_HEADER_SIZE   ((2 + 1 + 2 + 2 + 2) + (2))        //  11 Bytes
#define CC2420_PACKET_ACK_SIZE      5                                  //   5 Bytes
#define CC2420_PACKET_PAYLOAD_SIZE  (127 - CC2420_PACKET_HEADER_SIZE)  // 116 Bytes

// The time it takes for the acknowledgment packet to be received after the data packet has been
// transmitted
#define CC2420_ACK_DURATION        (0.5 * 32 * 2 * ((4 + 1) + (1) + (2 + 1) + (2)))
#define CC2420_SYMBOL_DURATION     (32 * 0.5)

// The length byte
#define CC2420_LENGTH_MASK         0x7F

// Frame control field
#define CC2420_FCF_NOACK           0x8841
#define CC2420_FCF_ACK             0x8861
#define CC2420_FCF_ACK_BM          0x0020
#define CC2420_FCF_BM              (~CC2420_FCF_ACK_BM)
#define CC2420_ACK_FCF             0x0002

// Footer
#define CC2420_CRC_OK_BM           0x80

/*!
  無線チップCC2420を初期化します。
  電波強度は0～31の値が指定可能で、値が大きいほど電波強度は強くなります。
  無線チャンネルに11(2405MHz)～26(2480MHz)以外の値を指定したときは引数エラーになります。
  電波強度に0～31以外の値を指定したときは引数エラーになります。

  @param pRRI      受信パケット構造体へのポインタ
  @param nChannel  無線チャンネル番号(11～26)
  @param nPanID    Personal Area Network(PAN) ID
  @param nAddress  自身のボードに設定するアドレス
  @param nPowerAmpLevel  電波強度(0～31)
*/
MRESULT CHIP_CC2420_init(RADIO_PACKET_RX_INFO *pRRI,
                         UINT8 nChannel,
                         WORD nPanID,
                         WORD nAddress,
                         UINT8 nPowerAmpLevel);

/*!
  無線チップCC2420を受信可あるいは受信不可の状態にします。

  @param bEnable  受信可能は1を、受信不可能とするときは0を指定
*/
void CHIP_CC2420_setRecv(BOOL bEnable);

/*!
  パケットを受信するまで待ちます。
*/
void CHIP_CC2420_waitRecvPacket(void);

/*!
  無線チップCC2420経由でパケットを受信したときに呼び出すコールバック関数を指定します。
  指定する受信コールバック関数の型は、戻り値がMRESULT・引数がRADIO_PACKET_RX_INFOポインタで
  ある必要があります。

  @param pFunc  受信コールバック関数へのポインタ
  @retval MOXA_SUCCESS  受信コールバック関数の設定に成功
  @retval MOXA_E_PARAM  引数である受信コールバック関数へのポインタがNULL
*/
MRESULT CHIP_CC2420_setRecvHandler(MRESULT (*pFunc)(RADIO_PACKET_RX_INFO *pRRI));

/*!
  無線チップCC2420経由でパケットを送信します。

  @param pRTI  無線送信パケット構造体へのポインタ
  @retval MOXA_SUCCESS  受信コールバック関数の設定に成功
  @retval MOXA_E_PARAM  引数である受信コールバック関数へのポインタがNULL
*/
MRESULT CHIP_CC2420_sendPacket(RADIO_PACKET_TX_INFO *pRTI);

//#pragma used-

#endif // __CHIP_CC2420_H__
