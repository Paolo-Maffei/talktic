/*!
  @file
  @brief 無線通信の処理関数定義
  @author Shinji Yamachika, Vistarica Designs Co.Ltd.
  @date   2005/12/7
  @version 0.1
*/
#ifndef __RADIO_H__
#define __RADIO_H__

#include "moxa_config.h"

#include "radio_packet.h"

#ifdef MOXA_USE_CHIP_CC2420
#include "chip_cc2420.h"

#define RADIO_PAYLOAD_SIZE  CC2420_PACKET_PAYLOAD_SIZE
#endif // MOXA_USE_CHIP_CC2420

//#pragma used+

/*!
  無線機能の初期化を行ないます。
  無線チャンネル番号、PAN ID、アドレス、電波強度を変更するときは再度初期化を行なってください。
  電波強度は0～31の値が指定可能で、値が大きいほど電波強度は強くなります。
  無線チップにCC2420を使用しているとき、無線チャンネルに11(2405MHz)～26(2480MHz)以外を
  指定したときは引数エラーになります。

  @param nChannel  無線チャンネル番号(11～26)
  @param nPanID    Personal Area Network(PAN) ID
  @param nAddress  自身のボードに設定するアドレス
  @param nPowerAmpLevel  電波強度(0～31)
  @retval MOXA_SUCCESS  初期化に成功
  @retval MOXA_E_PARAM  無線チャンネル番号が11～26の範囲から外れている
*/
MRESULT RADIO_init(UINT8 nChannel, WORD nPanID, WORD nAddress, UINT8 nPowerAmpLevel);

/*!
  パケットを受信したときに呼び出すコールバック関数を指定します。
  必ずRADIO_init関数を呼んだ後に本関数を呼んでください。
  指定する受信コールバック関数の型は、戻り値がMRESULT・引数がRADIO_PACKET_RX_INFOポインタで
  ある必要があります。
  引数pRRIにNULLを指定すると以前に設定したコールバック関数を無効にします。

  @param pFunc  受信コールバック関数へのポインタ
  @retval MOXA_SUCCESS  受信コールバック関数の設定に成功
  @retval MOXA_E_FAIL   コールバックの仕組みが実装されてない(see moxa_config.h)
*/
MRESULT RADIO_setRecvHandler(MRESULT (*pFunc)(RADIO_PACKET_RX_INFO *pRRI));

/*!
  パケットの受信を行ないます。
  この関数はパケットを受信するまでブロッキングします。
  RADIO_setRecvHandler関数で受信コールバック関数を設定しているときは、この関数を呼んでも
  何も起きません。RADIO_setRecvHandler関数の引数にNULLを設定すると再びこの関数が使用できます。

  @param pAddress  送信元のアドレス
  @param pPayload  パケットを受信したときにデータを格納する領域へのポインタ
  @param pLength   受信したデータの長さ(単位:byte)
  @retval MOXA_SUCCESS  受信に成功
  @retval MOXA_E_FAIL   受信に失敗
  @retval MOXA_E_PARAM  引数pRRIにNULLを指定した
*/
MRESULT RADIO_recvPacket(WORD *pAddress, BYTE *pPayload, UINT8 *pLength);

/*!
  パケットの送信を行ないます。
  nAddressにはパケットの送信先を表すアドレスを記述してください。
  pPayloadには送信するデータを指すポインタを指定し、nLengthはpPayloadに格納したデータの長さを
  バイト長で指定する必要があります。

  @param nAddress  送信先のアドレス
  @param pPayload  パケットとして送信するデータへのポインタ
  @param nLength   送信するデータの長さ(単位:byte)
  @retval MOXA_SUCCESS  送信に成功
  @retval MOXA_E_PARAM  pPalyloadがNULLか、nLengthが最大payload長を超えている
*/
MRESULT RADIO_sendPacket(WORD nAddress, const BYTE *pPayload, UINT8 nLength);

//#pragma used-

#endif // __RADIO_H__
