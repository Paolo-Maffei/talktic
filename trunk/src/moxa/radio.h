/*!
  @file
  @brief �����ʐM�̏����֐���`
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
  �����@�\�̏��������s�Ȃ��܂��B
  �����`�����l���ԍ��APAN ID�A�A�h���X�A�d�g���x��ύX����Ƃ��͍ēx���������s�Ȃ��Ă��������B
  �d�g���x��0�`31�̒l���w��\�ŁA�l���傫���قǓd�g���x�͋����Ȃ�܂��B
  �����`�b�v��CC2420���g�p���Ă���Ƃ��A�����`�����l����11(2405MHz)�`26(2480MHz)�ȊO��
  �w�肵���Ƃ��͈����G���[�ɂȂ�܂��B

  @param nChannel  �����`�����l���ԍ�(11�`26)
  @param nPanID    Personal Area Network(PAN) ID
  @param nAddress  ���g�̃{�[�h�ɐݒ肷��A�h���X
  @param nPowerAmpLevel  �d�g���x(0�`31)
  @retval MOXA_SUCCESS  �������ɐ���
  @retval MOXA_E_PARAM  �����`�����l���ԍ���11�`26�͈̔͂���O��Ă���
*/
MRESULT RADIO_init(UINT8 nChannel, WORD nPanID, WORD nAddress, UINT8 nPowerAmpLevel);

/*!
  �p�P�b�g����M�����Ƃ��ɌĂяo���R�[���o�b�N�֐����w�肵�܂��B
  �K��RADIO_init�֐����Ă񂾌�ɖ{�֐����Ă�ł��������B
  �w�肷���M�R�[���o�b�N�֐��̌^�́A�߂�l��MRESULT�E������RADIO_PACKET_RX_INFO�|�C���^��
  ����K�v������܂��B
  ����pRRI��NULL���w�肷��ƈȑO�ɐݒ肵���R�[���o�b�N�֐��𖳌��ɂ��܂��B

  @param pFunc  ��M�R�[���o�b�N�֐��ւ̃|�C���^
  @retval MOXA_SUCCESS  ��M�R�[���o�b�N�֐��̐ݒ�ɐ���
  @retval MOXA_E_FAIL   �R�[���o�b�N�̎d�g�݂���������ĂȂ�(see moxa_config.h)
*/
MRESULT RADIO_setRecvHandler(MRESULT (*pFunc)(RADIO_PACKET_RX_INFO *pRRI));

/*!
  �p�P�b�g�̎�M���s�Ȃ��܂��B
  ���̊֐��̓p�P�b�g����M����܂Ńu���b�L���O���܂��B
  RADIO_setRecvHandler�֐��Ŏ�M�R�[���o�b�N�֐���ݒ肵�Ă���Ƃ��́A���̊֐����Ă�ł�
  �����N���܂���BRADIO_setRecvHandler�֐��̈�����NULL��ݒ肷��ƍĂт��̊֐����g�p�ł��܂��B

  @param pAddress  ���M���̃A�h���X
  @param pPayload  �p�P�b�g����M�����Ƃ��Ƀf�[�^���i�[����̈�ւ̃|�C���^
  @param pLength   ��M�����f�[�^�̒���(�P��:byte)
  @retval MOXA_SUCCESS  ��M�ɐ���
  @retval MOXA_E_FAIL   ��M�Ɏ��s
  @retval MOXA_E_PARAM  ����pRRI��NULL���w�肵��
*/
MRESULT RADIO_recvPacket(WORD *pAddress, BYTE *pPayload, UINT8 *pLength);

/*!
  �p�P�b�g�̑��M���s�Ȃ��܂��B
  nAddress�ɂ̓p�P�b�g�̑��M���\���A�h���X���L�q���Ă��������B
  pPayload�ɂ͑��M����f�[�^���w���|�C���^���w�肵�AnLength��pPayload�Ɋi�[�����f�[�^�̒�����
  �o�C�g���Ŏw�肷��K�v������܂��B

  @param nAddress  ���M��̃A�h���X
  @param pPayload  �p�P�b�g�Ƃ��đ��M����f�[�^�ւ̃|�C���^
  @param nLength   ���M����f�[�^�̒���(�P��:byte)
  @retval MOXA_SUCCESS  ���M�ɐ���
  @retval MOXA_E_PARAM  pPalyload��NULL���AnLength���ő�payload���𒴂��Ă���
*/
MRESULT RADIO_sendPacket(WORD nAddress, const BYTE *pPayload, UINT8 nLength);

//#pragma used-

#endif // __RADIO_H__
