/*!
  @file
  @brief �����ʐM�̏����֐���`
  @author Shinji Yamachika, Vistarica Designs Co.Ltd.
  @date   2005/12/7
  @version 0.1
*/

#include "radio.h"

static RADIO_PACKET_TX_INFO s_rfTxInfo;          //!< ���M�p�P�b�g���
static RADIO_PACKET_RX_INFO s_rfRxInfo;          //!< ��M�p�P�b�g���
static BYTE s_rfRxBuffer[RADIO_PAYLOAD_SIZE];    //!< ��M�p�o�b�t�@

// �����@�\�̏��������s�Ȃ�
MRESULT RADIO_init(UINT8 nChannel, WORD nPanID, WORD nAddress, UINT8 nPowerAmpLevel)
{
#ifdef MOXA_DEBUG_CHECK_PARAM
    // ��@����(JAPAN)�̃`�F�b�N
    if (nChannel < 11 || nChannel > 26) {
        return MOXA_E_PARAM;
    }
#endif

#if (MOXA_BOARD_TYPE == MOXA_BOARD_CC2420DBK)
    DDRB  |= BM(RESET_N) | BM(VREG_EN) | BM(MOSI) | BM(SCK) | BM(CSN);
    PORTB |= BM(RESET_N) | BM(MOSI) | BM(SCK) | BM(CSN);
#elif (MOXA_BOARD_TYPE == MOXA_BOARD_PROTO_1)
    DDRB  |= BM(RESET_N) | BM(VREG_EN) | BM(MOSI) | BM(SCK) | BM(CSN);
    PORTB |= BM(RESET_N) | BM(MOSI) | BM(SCK) | BM(CSN);
#endif

    // Enables SPI, selects "master", clock rate FCK / 2, and SPI mode 0
    SPCR |= BM(SPE) | BM(MSTR);
    SPSR |= BM(SPI2X);

    // Initalize common protocol parameters
    s_rfTxInfo.nLength = 10;
    s_rfTxInfo.bAckRequest = TRUE;
    s_rfRxInfo.pPayload = s_rfRxBuffer;

    CHIP_CC2420_init(&s_rfRxInfo, nChannel, nPanID, nAddress, nPowerAmpLevel);

    // Turn on RX mode
    CHIP_CC2420_setRecv(TRUE);

    return MOXA_SUCCESS;
}

// �p�P�b�g����M�����Ƃ��ɌĂяo���R�[���o�b�N�֐����w�肵�܂��B
MRESULT RADIO_setRecvHandler(MRESULT (*pFunc)(RADIO_PACKET_RX_INFO *pRRI))
{
#ifdef MOXA_USE_CHIP_CC2420
    return CHIP_CC2420_setRecvHandler(pFunc);
#else
    return MOXA_E_FAIL;
#endif
}

// �p�P�b�g�̎�M���s�Ȃ�
MRESULT RADIO_recvPacket(WORD *pAddress, BYTE *pPayload, UINT8 *pLength)
{
#ifdef MOXA_DEBUG_CHECK_PARAM
    if (pAddress == NULL || pPayload == NULL || pLength == NULL) {
        return MOXA_E_PARAM;
    }
#endif
    CHIP_CC2420_waitRecvPacket();

    // ��M�p�P�b�g�̃f�[�^���R�s�[���Ɏ�M�p�P�b�g���荞�݂���������Ƃ܂����̂Ŋ��荞�݋֎~
    DISABLE_GLOBAL_INT();
    *pAddress = s_rfRxInfo.srcAddr;
    *pLength = s_rfRxInfo.nLength;
    memcpy(pPayload, s_rfRxInfo.pPayload, s_rfRxInfo.nLength);
    ENABLE_GLOBAL_INT();

    return MOXA_SUCCESS;
}

// �p�P�b�g�̑��M���s�Ȃ�
MRESULT RADIO_sendPacket(WORD nAddress, const BYTE *pPayload, UINT8 nLength)
{
#ifdef MOXA_DEBUG_CHECK_PARAM
    if (pPayload == NULL || nLength > RADIO_PAYLOAD_SIZE) {
        return MOXA_E_PARAM;
    }
#endif
    s_rfTxInfo.destAddr = nAddress;
    s_rfTxInfo.pPayload = (BYTE *)pPayload;
    s_rfTxInfo.nLength = nLength;
    
    return CHIP_CC2420_sendPacket(&s_rfTxInfo);
}
