/*!
  @file
  @brief 無線通信チップCC2420の処理関数
  @author Shinji Yamachika, Vistarica Designs Co.Ltd.
  @date   2005/12/7
  @version 0.1
*/

#include "chip_cc2420.h"

#include "radio_packet.h"

#include <avr/interrupt.h>

static void CHIP_CC2420_setChannel(UINT8 nChannel);
static void CHIP_CC2420_waitForXtal(void);
static void CHIP_CC2420_wait(UINT16 timeout);

static RADIO_SETTINGS s_RfSettings;     //!< 無線送受信に関係する構造体変数
static volatile BOOL s_bRfReceived;     //!< 受信フラグ(パケットを受信したらTRUE)

//! パケット受信コールバック関数へのポインタ変数
static INT8 (*s_pReceivedHandler)(RADIO_PACKET_RX_INFO *pRRI) = NULL;

// 無線電波の送信レベルを設定します。
static MRESULT CHIP_CC2420_setPaLevel(UINT8 nPowerAmpLevel);


// 無線チップCC2420の初期化
MRESULT CHIP_CC2420_init(RADIO_PACKET_RX_INFO *pRRI,
                         UINT8 nChannel,
                         WORD nPanID,
                         WORD nAddress,
                         UINT8 nPowerAmpLevel)
{
    UINT8 n;

#ifdef MOXA_DEBUG_CHECK_PARAM
    if (pRRI == NULL) {
        return MOXA_E_PARAM;
    }
#endif
    // Make sure that the voltage regulator is on, and that the reset pin is inactive
    SET_VREG_ACTIVE();
    CHIP_CC2420_wait(1000);
    SET_RESET_ACTIVE();
    CHIP_CC2420_wait(1);
    SET_RESET_INACTIVE();
    CHIP_CC2420_wait(5);

    // Initialize the FIFOP external interrupt
    FIFOP_INT_INIT();
    ENABLE_FIFOP_INT();

    // Turn off all interrupts while we're accessing the CC2420 registers
	DISABLE_GLOBAL_INT();

    // Register modifications
    FASTSPI_STROBE(CC2420_SXOSCON);
    FASTSPI_SETREG(CC2420_MDMCTRL0, 0x0AF2); // Turn on automatic packet acknowledgment
    FASTSPI_SETREG(CC2420_MDMCTRL1, 0x0500); // Set the correlation threshold = 20
    FASTSPI_SETREG(CC2420_IOCFG0, 0x007F);   // Set the FIFOP threshold to maximum
    FASTSPI_SETREG(CC2420_SECCTRL0, 0x01C4); // Turn off "Security enable"

    // Set the RF channel
    CHIP_CC2420_setChannel(nChannel);

    // Set the Power Amplifier Level
    CHIP_CC2420_setPaLevel(nPowerAmpLevel);

    // Turn interrupts back on
	ENABLE_GLOBAL_INT();

    s_bRfReceived = FALSE;

	// Set the protocol configuration
	s_RfSettings.pRxInfo = pRRI;
	s_RfSettings.nPanID = nPanID;
	s_RfSettings.nAddress = nAddress;
	s_RfSettings.seqNumber = 0;
    s_RfSettings.bReceiveOn = FALSE;

	// Wait for the crystal oscillator to become stable
    CHIP_CC2420_waitForXtal();

	// Write the short address and the PAN ID to the CC2420 RAM (requires that the XOSC is on and stable)
   	DISABLE_GLOBAL_INT();
    FASTSPI_WRITE_RAM_LE(&nAddress, CC2420RAM_SHORTADDR, 2, n);
    FASTSPI_WRITE_RAM_LE(&nPanID, CC2420RAM_PANID, 2, n);
  	ENABLE_GLOBAL_INT();

    return MOXA_SUCCESS;
}

// 無線チップCC2420を受信可あるいは受信不可の状態にする
void CHIP_CC2420_setRecv(BOOL bEnable)
{
    s_RfSettings.bReceiveOn = bEnable;
    if (bEnable) {
        FASTSPI_STROBE(CC2420_SRXON);
        FASTSPI_STROBE(CC2420_SFLUSHRX);
        ENABLE_FIFOP_INT();
    } else {
        FASTSPI_STROBE(CC2420_SRFOFF);
        DISABLE_FIFOP_INT();
    }
}

// パケットを受信するまで待ちます。
void CHIP_CC2420_waitRecvPacket(void)
{
    while (s_bRfReceived == FALSE);
}

// パケットを受信したときに呼び出すコールバック関数を指定する
MRESULT CHIP_CC2420_setRecvHandler(MRESULT (*pFunc)(RADIO_PACKET_RX_INFO *pRRI))
{
#ifdef MOXA_DEBUG_CHECK_PARAM
    if (pFunc == NULL) {
        return MOXA_E_PARAM;
    }
#endif
    s_pReceivedHandler = pFunc;

    return MOXA_SUCCESS;
}

// 無線チップCC2420経由でパケットを送信する
MRESULT CHIP_CC2420_sendPacket(RADIO_PACKET_TX_INFO *pRTI)
{
    WORD frameControlField;
    UINT8 nPacketLength;
    MRESULT success;
    BYTE spiStatusByte;

    // Wait until the transceiver is idle
    while (FIFOP_IS_1 || SFD_IS_1);

    // Turn off global interrupts to avoid interference on the SPI interface
    DISABLE_GLOBAL_INT();

	// Flush the TX FIFO just in case...
	FASTSPI_STROBE(CC2420_SFLUSHTX);

    // Turn on RX if necessary
    if (!s_RfSettings.bReceiveOn) {
        FASTSPI_STROBE(CC2420_SRXON);
    }

    // Wait for the RSSI value to become valid
    do {
        FASTSPI_UPD_STATUS(spiStatusByte);
    } while (!(spiStatusByte & BM(CC2420_RSSI_VALID)));

	// TX begins after the CCA check has passed
    do {
		FASTSPI_STROBE(CC2420_STXONCCA);
		FASTSPI_UPD_STATUS(spiStatusByte);
		CHIP_CC2420_wait(100);
    } while (!(spiStatusByte & BM(CC2420_TX_ACTIVE)));

    // Write the packet to the TX FIFO (the FCS is appended automatically when AUTOCRC is enabled)
    nPacketLength = pRTI->nLength + CC2420_PACKET_HEADER_SIZE;
    FASTSPI_WRITE_FIFO((BYTE*)&nPacketLength, 1);              // Packet length
    frameControlField = pRTI->bAckRequest ? CC2420_FCF_ACK : CC2420_FCF_NOACK;
    FASTSPI_WRITE_FIFO((BYTE*) &frameControlField, 2);         // Frame control field
    FASTSPI_WRITE_FIFO((BYTE*) &s_RfSettings.seqNumber, 1);    // Sequence number
    FASTSPI_WRITE_FIFO((BYTE*) &s_RfSettings.nPanID, 2);       // Dest. PAN ID
    FASTSPI_WRITE_FIFO((BYTE*) &pRTI->destAddr, 2);            // Dest. address
    FASTSPI_WRITE_FIFO((BYTE*) &s_RfSettings.nAddress, 2);     // Source address
	FASTSPI_WRITE_FIFO((BYTE*) pRTI->pPayload, pRTI->nLength); // Payload

	// Wait for the transmission to begin before exiting (makes sure that this function cannot be called
	// a second time, and thereby cancelling the first transmission (observe the FIFOP + SFD test above).
	while (!SFD_IS_1);
	success = MOXA_SUCCESS;

	// Turn interrupts back on
	ENABLE_GLOBAL_INT();

    // Wait for the acknowledge to be received, if any
    if (pRTI->bAckRequest) {
		s_RfSettings.bAckReceived = FALSE;

		// Wait for the SFD to go low again
		while (SFD_IS_1);

        // We'll enter RX automatically, so just wait until we can be sure that the ack reception should have finished
        // The timeout consists of a 12-symbol turnaround time, the ack packet duration, and a small margin
        CHIP_CC2420_wait((12 * CC2420_SYMBOL_DURATION) + (CC2420_ACK_DURATION) + (2 * CC2420_SYMBOL_DURATION) + 100);

		// If an acknowledgment has been received (by the FIFOP interrupt), the bAckReceived flag should be set
		success = (s_RfSettings.bAckReceived) ? MOXA_SUCCESS : MOXA_E_FAIL;
    }

	// Turn off the receiver if it should not continue to be enabled
    DISABLE_GLOBAL_INT();
	if (!s_RfSettings.bReceiveOn) {
        FASTSPI_STROBE(CC2420_SRFOFF);
    }
    ENABLE_GLOBAL_INT();

    // Increment the sequence number, and return the result
    s_RfSettings.seqNumber++;

    return success;
}

/*!
  無線チップCC2420に対して、パケットを送信するチャンネルを設定します。

  @param nChannel  無線チャンネル番号(11～26)
*/
static void CHIP_CC2420_setChannel(UINT8 nChannel)
{
	UINT16 f;
	
	// Derive frequency programming from the given channel number
	f = (UINT16) (nChannel - 11);   // Subtract the base channel 
	f = f + (f << 2);    		    // Multiply with 5, which is the channel spacing
	f = f + 357 + 0x4000;		    // 357 is 2405-2048, 0x4000 is LOCK_THR = 1

    // Write it to the CC2420
	DISABLE_GLOBAL_INT();
	FASTSPI_SETREG(CC2420_FSCTRL, f);
	ENABLE_GLOBAL_INT();
}

/*!
  無線チップCC2420用の水晶振動子が安定するまで待ちます。
*/
static void CHIP_CC2420_waitForXtal(void)
{
    BYTE spiStatusByte;

    // Poll the SPI status byte until the crystal oscillator is stable
    do {
	    DISABLE_GLOBAL_INT();
	    FASTSPI_UPD_STATUS(spiStatusByte);
	    ENABLE_GLOBAL_INT();
    } while (!(spiStatusByte & (BM(CC2420_XOSC16M_STABLE))));
}

/*!
  無線チップCC2420用のウェイト関数です。
  将来削除される予定です。
*/
static void CHIP_CC2420_wait(UINT16 timeout)
{
    // This sequence uses exactly 8 clock cycle for each round
    do {
        NOP();
        NOP();
        NOP();
        NOP();
    } while (--timeout);
}


/*!
  実際の割り込みハンドラ関数。
*/
#if (MOXA_BOARD_TYPE == MOXA_BOARD_PROTO_1)
//interrupt [EXT_INT6] void SIG_INTERRUPT6(void)
ISR(SIG_INTERRUPT6)
#elif (MOXA_BOARD_TYPE == MOXA_BOARD_CC2420DBK)
//interrupt [EXT_INT0] void SIG_INTERRUPT0(void)
ISR(SIG_INTERRUPT0)
#endif
{
	WORD frameControlField;
	UINT8 nLength;
	BYTE pFooter[2];

    // Clean up and exit in case of FIFO overflow, which is indicated by FIFOP = 1 and FIFO = 0
	if ((FIFOP_IS_1) && (!(FIFO_IS_1))) {
	    FASTSPI_STROBE(CC2420_SFLUSHRX);
	    FASTSPI_STROBE(CC2420_SFLUSHRX);
	    return;
	}

	// Payload length
	FASTSPI_READ_FIFO_BYTE(nLength);
	nLength &= CC2420_LENGTH_MASK; // Ignore MSB

    // Ignore the packet if the length is too short
    if (nLength < CC2420_PACKET_ACK_SIZE) {
    	FASTSPI_READ_FIFO_GARBAGE(nLength);

    // Otherwise, if the length is valid, then proceed with the rest of the packet
    } else {
        // Register the payload length
        s_RfSettings.pRxInfo->nLength = nLength - CC2420_PACKET_HEADER_SIZE;

        // Read the frame control field and the data sequence number
        FASTSPI_READ_FIFO_NO_WAIT((BYTE*) &frameControlField, 2);
        s_RfSettings.pRxInfo->bAckRequest = !!(frameControlField & CC2420_FCF_ACK_BM);
    	FASTSPI_READ_FIFO_BYTE(s_RfSettings.pRxInfo->seqNumber);

		// Is this an acknowledgment packet?
    	if ((nLength == CC2420_PACKET_ACK_SIZE)
            && (frameControlField == CC2420_ACK_FCF)
            && (s_RfSettings.pRxInfo->seqNumber == s_RfSettings.seqNumber)) {

 	       	// Read the footer and check for CRC OK
			FASTSPI_READ_FIFO_NO_WAIT((BYTE*) pFooter, 2);

			// Indicate the successful ack reception (this flag is polled by the transmission routine)
			if (pFooter[1] & CC2420_CRC_OK_BM) {
                s_RfSettings.bAckReceived = TRUE;
            }
 
		// Too small to be a valid packet?
		} else if(nLength < CC2420_PACKET_HEADER_SIZE) {
			FASTSPI_READ_FIFO_GARBAGE(nLength - 3);
			return;

		// Receive the rest of the packet
		} else {
			// Skip the destination PAN and address (that's taken care of by harware address recognition!)
			FASTSPI_READ_FIFO_GARBAGE(4);

			// Read the source address
			FASTSPI_READ_FIFO_NO_WAIT((BYTE*) &s_RfSettings.pRxInfo->srcAddr, 2);

			// Read the packet payload
			FASTSPI_READ_FIFO_NO_WAIT(s_RfSettings.pRxInfo->pPayload, s_RfSettings.pRxInfo->nLength);

			// Read the footer to get the RSSI value
			FASTSPI_READ_FIFO_NO_WAIT((BYTE*) pFooter, 2);
			s_RfSettings.pRxInfo->rssi = pFooter[0];

			// Notify the application about the received _data_ packet if the CRC is OK
			if ((frameControlField & (CC2420_FCF_BM)) == CC2420_FCF_NOACK) {
                if (pFooter[1] & CC2420_CRC_OK_BM) {
                    if (s_pReceivedHandler != NULL) {
                        // 受信コールバック関数の実行
                        s_bRfReceived = TRUE;
                        s_pReceivedHandler(s_RfSettings.pRxInfo);
                    }
                }
			}
		}
    }
}

/*!
  無線電波の送信レベルを設定します。
  電波強度は0～31の値が指定可能で、値が大きいほど電波強度は強くなります。
  電波強度に0～31以外の値を指定したときは引数エラーになります。

  @param nPowerAmpLevel  電波強度(0～31)
  @retval MOXA_SUCCESS  設定に成功
  @retval MOXA_E_PARAM  引数に指定した電波強度の値が不正
*/
static MRESULT CHIP_CC2420_setPaLevel(UINT8 nPowerAmpLevel)
{
	UINT16 f;

#ifdef MOXA_DEBUG_CHECK_PARAM
    if (nPowerAmpLevel > 31) {
        return MOXA_E_PARAM;
    }
#endif
	// Derive frequency programming from the given channel number
	f = (UINT16)(0x1F & nPowerAmpLevel); 
	f = f | 0xA000;

    // Write it to the CC2420
	DISABLE_GLOBAL_INT();
	FASTSPI_SETREG(CC2420_TXCTRL, f);
	ENABLE_GLOBAL_INT();

    return MOXA_SUCCESS;
}
