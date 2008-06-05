/*!
  @file
  @brief �����ʐM�̃p�P�b�g�\����`
  @author Shinji Yamachika, Vistarica Designs Co.Ltd.
  @date   2005/12/8
  @version 0.1
*/

#ifndef __RADIO_PACKET_H__
#define __RADIO_PACKET_H__

/*!
  �������M�p�P�b�g�\���̂ł��B
  �p�P�b�g�𑗐M����ۂɕK�v�ȃf�[�^���i�[���邽�߂Ɏg�p���܂��B
*/
typedef struct {
    WORD  destPanId;      //!< ���M���鈶���PAN ID
	WORD  destAddr;       //!< ���M���鈶��̃A�h���X
	UINT8 nLength;        //!< �p�P�b�g��(Bytes)
    BYTE *pPayload;       //!< �p�P�b�g�f�[�^�ւ̃|�C���^
	BOOL  bAckRequest;    //!< ���M�p�P�b�g����M������ACK��Ԃ����ǂ����̎w��
} RADIO_PACKET_TX_INFO;

/*!
  ������M�p�P�b�g�\���̂ł��B
  �p�P�b�g����M�����Ƃ��A��M�����f�[�^���i�[���邽�߂Ɏg�p���܂��B
*/
typedef struct {
    UINT8 seqNumber;      //!< �p�P�b�g�̃V�[�P���X�i���o�[
	WORD  srcAddr;        //!< ���M���̃A�h���X
	WORD  srcPanId;       //!< ���M����PAN ID
	UINT8 nLength;        //!< �p�P�b�g��(Bytes)
    BYTE *pPayload;       //!< �p�P�b�g�f�[�^�ւ̃|�C���^
	BOOL  bAckRequest;    //!< ���̃p�P�b�g����M������ACK��Ԃ����ǂ����̎w��
	INT8  rssi;           //!< �d�g��M���x(0�`31)
} RADIO_PACKET_RX_INFO;

/*!
  ��������M�Ɋ֌W����\���̂ł��B
  �����@�\�������������Ƃ��̐ݒ���i�[���邽�߂Ɏg�p���܂��B
*/
typedef struct {
    RADIO_PACKET_RX_INFO *pRxInfo;    //!< ������M�p�P�b�g�\���̂ւ̃|�C���^
    UINT8  seqNumber;                 //!< ���M�p�̃V�[�P���X�i���o�[
    BOOL   bAckReceived;              //!< �p�P�b�g�𑗐M����ACK���Ԃ��Ă������ǂ�����\��
    WORD   nPanID;                    //!< ���g��PAN ID
    WORD   nAddress;                  //!< ���g�̃A�h���X
    BOOL   bReceiveOn;                //!< �p�P�b�g����M�����Ă��邩�ǂ���
} RADIO_SETTINGS;

#endif // __RADIO_PACKET_H__
