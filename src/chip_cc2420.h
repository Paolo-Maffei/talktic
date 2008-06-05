/*!
  @file
  @brief �����ʐM�`�b�vCC2420�̏����֐���`
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
  �����`�b�vCC2420�����������܂��B
  �d�g���x��0�`31�̒l���w��\�ŁA�l���傫���قǓd�g���x�͋����Ȃ�܂��B
  �����`�����l����11(2405MHz)�`26(2480MHz)�ȊO�̒l���w�肵���Ƃ��͈����G���[�ɂȂ�܂��B
  �d�g���x��0�`31�ȊO�̒l���w�肵���Ƃ��͈����G���[�ɂȂ�܂��B

  @param pRRI      ��M�p�P�b�g�\���̂ւ̃|�C���^
  @param nChannel  �����`�����l���ԍ�(11�`26)
  @param nPanID    Personal Area Network(PAN) ID
  @param nAddress  ���g�̃{�[�h�ɐݒ肷��A�h���X
  @param nPowerAmpLevel  �d�g���x(0�`31)
*/
MRESULT CHIP_CC2420_init(RADIO_PACKET_RX_INFO *pRRI,
                         UINT8 nChannel,
                         WORD nPanID,
                         WORD nAddress,
                         UINT8 nPowerAmpLevel);

/*!
  �����`�b�vCC2420����M���邢�͎�M�s�̏�Ԃɂ��܂��B

  @param bEnable  ��M�\��1���A��M�s�\�Ƃ���Ƃ���0���w��
*/
void CHIP_CC2420_setRecv(BOOL bEnable);

/*!
  �p�P�b�g����M����܂ő҂��܂��B
*/
void CHIP_CC2420_waitRecvPacket(void);

/*!
  �����`�b�vCC2420�o�R�Ńp�P�b�g����M�����Ƃ��ɌĂяo���R�[���o�b�N�֐����w�肵�܂��B
  �w�肷���M�R�[���o�b�N�֐��̌^�́A�߂�l��MRESULT�E������RADIO_PACKET_RX_INFO�|�C���^��
  ����K�v������܂��B

  @param pFunc  ��M�R�[���o�b�N�֐��ւ̃|�C���^
  @retval MOXA_SUCCESS  ��M�R�[���o�b�N�֐��̐ݒ�ɐ���
  @retval MOXA_E_PARAM  �����ł����M�R�[���o�b�N�֐��ւ̃|�C���^��NULL
*/
MRESULT CHIP_CC2420_setRecvHandler(MRESULT (*pFunc)(RADIO_PACKET_RX_INFO *pRRI));

/*!
  �����`�b�vCC2420�o�R�Ńp�P�b�g�𑗐M���܂��B

  @param pRTI  �������M�p�P�b�g�\���̂ւ̃|�C���^
  @retval MOXA_SUCCESS  ��M�R�[���o�b�N�֐��̐ݒ�ɐ���
  @retval MOXA_E_PARAM  �����ł����M�R�[���o�b�N�֐��ւ̃|�C���^��NULL
*/
MRESULT CHIP_CC2420_sendPacket(RADIO_PACKET_TX_INFO *pRTI);

//#pragma used-

#endif // __CHIP_CC2420_H__
