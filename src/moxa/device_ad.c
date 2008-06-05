/*!
  @file
  @brief デバイスのAD変換処理関数

  本関数はA/D変換接続のデバイスに関する処理を行ないます。
  PIO接続のデバイスに関してはdevice_port.cに記述してあります。

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


// デバイスポート番号をADCポート番号に変換する配列
#if (MOXA_BOARD_TYPE == MOXA_BOARD_PROTO_1) | (MOXA_BOARD_TYPE == MOXA_BOARD_STK300)
const INT8 s_DeviceAdMapping[DEVICE_PORT_N] = {
    0, 1, 2, 3, 4, 5, 6, 7
};
#elif (MOXA_BOARD_TYPE == MOXA_BOARD_CC2420DBK)
const INT8 s_DeviceAdMapping[DEVICE_PORT_N] = {
    4, 5, 6, -1, -1, 0, 3, 7
};
#endif

// AD変換の初期化処理を行なう
MRESULT DEVICE_ad_init(UINT8 nPort)
{
#ifdef MOXA_DEBUG_CHECK_PARAM
    if (nPort >= DEVICE_PORT_N) {
        return MOXA_E_PARAM;
    }
#endif
    // A/D変換できないデバイスポートが指定されたときは初期化を失敗させる
    if (s_DeviceAdMapping[nPort] < 0) {
        return MOXA_E_FAIL;
    }

    DEVICE_ADC_INIT();
    DEVICE_ADC_ENABLE();

    return MOXA_SUCCESS;
}

// チャンネル番号を指定してAD変換を行なう
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

    // A/D変換できないデバイスポートが指定されたときは初期化を失敗させる
    if (nChannel < 0) {
        return MOXA_E_FAIL;
    }
    DEVICE_ADC_SET_CHANNEL(nChannel);

    // チャンネルを変更したときは最低7us待つ必要がある
    delay_us(7);

    DEVICE_ADC_SAMPLE_SINGLE();
    DEVICE_ADC_GET_SAMPLE_10BIT(val);

    return val;
}
