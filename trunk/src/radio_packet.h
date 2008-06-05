/*!
  @file
  @brief 無線通信のパケット構造定義
  @author Shinji Yamachika, Vistarica Designs Co.Ltd.
  @date   2005/12/8
  @version 0.1
*/

#ifndef __RADIO_PACKET_H__
#define __RADIO_PACKET_H__

/*!
  無線送信パケット構造体です。
  パケットを送信する際に必要なデータを格納するために使用します。
*/
typedef struct {
    WORD  destPanId;      //!< 送信する宛先のPAN ID
	WORD  destAddr;       //!< 送信する宛先のアドレス
	UINT8 nLength;        //!< パケット長(Bytes)
    BYTE *pPayload;       //!< パケットデータへのポインタ
	BOOL  bAckRequest;    //!< 送信パケットを受信したらACKを返すかどうかの指示
} RADIO_PACKET_TX_INFO;

/*!
  無線受信パケット構造体です。
  パケットを受信したとき、受信したデータを格納するために使用します。
*/
typedef struct {
    UINT8 seqNumber;      //!< パケットのシーケンスナンバー
	WORD  srcAddr;        //!< 送信元のアドレス
	WORD  srcPanId;       //!< 送信元のPAN ID
	UINT8 nLength;        //!< パケット長(Bytes)
    BYTE *pPayload;       //!< パケットデータへのポインタ
	BOOL  bAckRequest;    //!< このパケットを受信したらACKを返すかどうかの指示
	INT8  rssi;           //!< 電波受信強度(0～31)
} RADIO_PACKET_RX_INFO;

/*!
  無線送受信に関係する構造体です。
  無線機能を初期化したときの設定を格納するために使用します。
*/
typedef struct {
    RADIO_PACKET_RX_INFO *pRxInfo;    //!< 無線受信パケット構造体へのポインタ
    UINT8  seqNumber;                 //!< 送信用のシーケンスナンバー
    BOOL   bAckReceived;              //!< パケットを送信してACKが返ってきたかどうかを表す
    WORD   nPanID;                    //!< 自身のPAN ID
    WORD   nAddress;                  //!< 自身のアドレス
    BOOL   bReceiveOn;                //!< パケットを受信許可しているかどうか
} RADIO_SETTINGS;

#endif // __RADIO_PACKET_H__
