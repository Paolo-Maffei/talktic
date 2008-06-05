/*!
  @file
  @brief �f�o�C�X��AD�ϊ������֐�

  �{�֐���A/D�ϊ��ڑ��̃f�o�C�X�Ɋւ��鏈�����s�Ȃ��܂��B
  PIO�ڑ��̃f�o�C�X�Ɋւ��Ă�device_port.c�ɋL�q���Ă���܂��B

  @author Shinji Yamachika, Vistarica Designs Co.Ltd.
  @date   2005/11/22
  @version 0.1
*/
#include "device_ad.h"
#include "device_port.h"

#define F_CPU MOXA_MCU_CLOCK
#define delay_us _delay_us
#define delay_ms _delay_ms

#include <util/delay.h>


// �f�o�C�X�|�[�g�ԍ���ADC�|�[�g�ԍ��ɕϊ�����z��
#if (MOXA_BOARD_TYPE == MOXA_BOARD_PROTO_1) | (MOXA_BOARD_TYPE == MOXA_BOARD_STK300)
const INT8 s_DeviceAdMapping[DEVICE_PORT_N] = {
    0, 1, 2, 3, 4, 5, 6, 7
};
#elif (MOXA_BOARD_TYPE == MOXA_BOARD_CC2420DBK)
const INT8 s_DeviceAdMapping[DEVICE_PORT_N] = {
    4, 5, 6, -1, -1, 0, 3, 7
};
#endif

// AD�ϊ��̏������������s�Ȃ�
MRESULT DEVICE_ad_init(UINT8 nPort)
{
#ifdef MOXA_DEBUG_CHECK_PARAM
    if (nPort >= DEVICE_PORT_N) {
        return MOXA_E_PARAM;
    }
#endif
    // A/D�ϊ��ł��Ȃ��f�o�C�X�|�[�g���w�肳�ꂽ�Ƃ��͏����������s������
    if (s_DeviceAdMapping[nPort] < 0) {
        return MOXA_E_FAIL;
    }

    DEVICE_ADC_INIT();
    DEVICE_ADC_ENABLE();

    return MOXA_SUCCESS;
}

// �`�����l���ԍ����w�肵��AD�ϊ����s�Ȃ�
UINT16 DEVICE_ad_get(UINT8 nPort)
{
    INT8 nChannel;
    UINT16 val;

#ifdef MOXA_DEBUG_CHECK_PARAM
    if (nPort >= DEVICE_PORT_N) {
        return MOXA_E_PARAM;
    }
#endif
    nChannel = s_DeviceAdMapping[nPort];

    // A/D�ϊ��ł��Ȃ��f�o�C�X�|�[�g���w�肳�ꂽ�Ƃ��͏����������s������
    if (nChannel < 0) {
        return MOXA_E_FAIL;
    }
    DEVICE_ADC_SET_CHANNEL(nChannel);

    // �`�����l����ύX�����Ƃ��͍Œ�7us�҂K�v������
    delay_us(7);

    DEVICE_ADC_SAMPLE_SINGLE();
    DEVICE_ADC_GET_SAMPLE_10BIT(val);

    return val;
}
