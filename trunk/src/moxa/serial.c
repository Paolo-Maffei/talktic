/*!
  @file
  @brief デバッグ用シリアル通信の処理関数
  @author Shinji Yamachika
  @date   2005/11/28
  @version 0.1
*/

#include "serial.h"
#include <stdarg.h>
#include <avr/interrupt.h>

#define FRAMING_ERROR        (1 << FE)
#define PARITY_ERROR         (1 << UPE)
#define DATA_OVERRUN         (1 << DOR)   // renamed from OVR by txi
#define DATA_REGISTER_EMPTY  (1 << UDRE)
#define RX_COMPLETE          (1 << RXC)

/* バッファサイズを表現する変数の型定義（送信か受信のどちらか大きい方にあわせます） */
#if (SERIAL_TX_BUFSIZE < 256) | (SERIAL_RX_BUFSIZE < 256)
#define SERIAL_BUF  unsigned char   //!< バッファサイズが256未満のときは1Byteとする
#else
#define SERIAL_BUF  unsigned int    //!< バッファサイズが256以上のときは2Byteとする
#endif

// USART0 Transmitter buffer
static char s_TxBuffer0[SERIAL_TX_BUFSIZE];
static SERIAL_BUF s_TxWrIndex0, s_TxRdIndex0, s_TxCounter0;

// USART0 Receiver buffer
static char s_RxBuffer0[SERIAL_RX_BUFSIZE];
static SERIAL_BUF s_RxWrIndex0, s_RxRdIndex0, s_RxCounter0;

// USART1 Transmitter buffer
static char s_TxBuffer1[SERIAL_TX_BUFSIZE];
static SERIAL_BUF s_TxWrIndex1, s_TxRdIndex1, s_TxCounter1;

// USART1 Receiver buffer
static char s_RxBuffer1[SERIAL_RX_BUFSIZE];
static SERIAL_BUF s_rxWrIndex1, s_RxRdIndex1, s_RxCounter1;

// This flag is set on USART Receiver buffer overflow
static BOOL s_RxBufferOverFlow0;
static BOOL s_RxBufferOverflow1;

// interrupt [USART0_RXC] void SERIAL_rx0Handler(void);    //!< USART0の受信割り込みハンドラ
// interrupt [USART0_TXC] void SERIAL_tx0Handler(void);    //!< USART0の送信割り込みハンドラ
// interrupt [USART1_RXC] void SERIAL_rx1Handler(void);    //!< USART1の受信割り込みハンドラ
// interrupt [USART1_TXC] void SERIAL_tx1Handler(void);    //!< USART1の送信割り込みハンドラ

// デバッグ用のシリアルポートを初期化する
MRESULT SERIAL_init(UINT8 nSerialPort, UINT32 nBaudrate)
{
    UINT16 nUsartBaudRateReg;

#ifdef MOXA_DEBUG_CHECK_PARAM
#if (MOXA_BOARD_TYPE == MOXA_BOARD_CC2420DBK)
    if (nSerialPort == 0) {
        return MOXA_E_PARAM;
    }
#endif
    if (nSerialPort >= SERIAL_PORT_N) {
        return MOXA_E_PARAM;
    }
#endif
       // あとでビットマクロの記述に変更すること
    
    // ボーレートレジスタ値の計算
#ifdef SERIAL_DOUBLE_SPEED
    nUsartBaudRateReg = (UINT16)((MOXA_MCU_CLOCK / (8 * nBaudrate)) - 1);
#else
    nUsartBaudRateReg = (UINT16)((MOXA_MCU_CLOCK / (16 * nBaudrate)) - 1);
#endif

    if (nSerialPort == 0) {
        UBRR0L = (UINT8)(nUsartBaudRateReg & 0x00ff);
        UBRR0H = (UINT8)(nUsartBaudRateReg >> 8);
#ifdef SERIAL_DOUBLE_SPEED
        UCSR0A = 0x02;
#else
        UCSR0A = 0x00;
#endif
        UCSR0B = 0xD8;    // 送受信割込み許可、送受信機能有効
        UCSR0C = 0x06;

        s_TxWrIndex0 = 0;
        s_TxRdIndex0 = 0;
        s_TxCounter0 = 0;
        s_RxWrIndex0 = 0;
        s_RxRdIndex0 = 0;
        s_RxCounter0 = 0;
    } else if(nSerialPort == 1) {
        UBRR1L = (UINT8)(nUsartBaudRateReg & 0x00ff);
        UBRR1H = (UINT8)(nUsartBaudRateReg >> 8);
#ifdef SERIAL_DOUBLE_SPEED
        UCSR1A = 0x02;
#else
        UCSR1A = 0x00;
#endif
        UCSR1B = 0xD8;    // 送受信割込み許可、送受信機能有効
        UCSR1C = 0x06;

        s_TxWrIndex1 = 0;
        s_TxRdIndex1 = 0;
        s_TxCounter1 = 0;
        s_rxWrIndex1 = 0;
        s_RxRdIndex1 = 0;
        s_RxCounter1 = 0;
    } else {
        return MOXA_E_PARAM;
    }

    return MOXA_SUCCESS;
}

// 文字列をシリアル出力します
MRESULT SERIAL_puts(UINT8 nSerialPort, char flash *pStr)
{
#ifdef MOXA_DEBUG_CHECK_PARAM
#if (MOXA_BOARD_TYPE == MOXA_BOARD_CC2420DBK)
    if (nSerialPort == 0) {
        return MOXA_E_PARAM;
    }
#endif
    if (nSerialPort >= SERIAL_PORT_N || pStr == NULL) {
        return MOXA_E_PARAM;
    }
#endif
    while (*pStr != '\0') {
        if (SERIAL_putchar(nSerialPort, *pStr) != MOXA_SUCCESS) {
            return MOXA_E_FAIL;
        }
        pStr++;
    }
    SERIAL_putchar(nSerialPort, '\r');
    SERIAL_putchar(nSerialPort, '\n');

    return MOXA_SUCCESS;
}


// シリアル入力を文字列として取得します
MRESULT SERIAL_gets(UINT8 nSerialPort, char *pStr, UINT8 nLength)
{
    char ch;

#ifdef MOXA_DEBUG_CHECK_PARAM
#if (MOXA_BOARD_TYPE == MOXA_BOARD_CC2420DBK)
    if (nSerialPort == 0) {
        return MOXA_E_PARAM;
    }
#endif
    if (nSerialPort >= SERIAL_PORT_N || pStr == NULL) {
        return MOXA_E_PARAM;
    }
#endif
//    while (nLength-- > 1) { // buggy: nLength will not be evaluated at 1
    while (nLength-- > 0) {
        ch = SERIAL_getchar(nSerialPort);
        if (ch == '\r' || ch == '\n' || ch == '\0') {
            break;
        }
        *pStr++ = ch;
    }
    *pStr = '\0';

    return MOXA_SUCCESS;
}


// １文字をシリアル出力する
MRESULT SERIAL_putchar(UINT8 nSerialPort, char ch)
{
    uint8_t save_sreg;

#ifdef MOXA_DEBUG_CHECK_PARAM
#if (MOXA_BOARD_TYPE == MOXA_BOARD_CC2420DBK)
    if (nSerialPort == 0) {
        return MOXA_E_PARAM;
    }
#endif
    if (nSerialPort >= SERIAL_PORT_N) {
        return MOXA_E_PARAM;
    }
#endif
    if (nSerialPort == 0) {
        while (s_TxCounter0 == SERIAL_TX_BUFSIZE);

        save_sreg = SREG;
        DISABLE_GLOBAL_INT();
        if (s_TxCounter0 || ((UCSR0A & DATA_REGISTER_EMPTY) == 0)) {
            s_TxBuffer0[s_TxWrIndex0] = ch;

            if (++s_TxWrIndex0 == SERIAL_TX_BUFSIZE) {
                s_TxWrIndex0 = 0;
            }
            s_TxCounter0++;
        } else {
            UDR0 = ch;
        }
        SREG = save_sreg;
    } else if (nSerialPort == 1) {
        while (s_TxCounter1 == SERIAL_TX_BUFSIZE);

        save_sreg = SREG;
        DISABLE_GLOBAL_INT();
        if (s_TxCounter1 || ((UCSR1A & DATA_REGISTER_EMPTY) == 0)) {
            s_TxBuffer1[s_TxWrIndex1] = ch;

            if (++s_TxWrIndex1 == SERIAL_TX_BUFSIZE) {
                s_TxWrIndex1 = 0;
            }
            s_TxCounter1++;
        } else {
            UDR1 = ch;
        }
        SREG = save_sreg;
    } else {
        return MOXA_E_PARAM;
    }

    return MOXA_SUCCESS;
}


// シリアル入力した１文字を取得します（ブロッキング）
int SERIAL_getchar(UINT8 nSerialPort)
{
    int data;
    uint8_t save_sreg;

#ifdef MOXA_DEBUG_CHECK_PARAM
#if (MOXA_BOARD_TYPE == MOXA_BOARD_CC2420DBK)
    if (nSerialPort == 0) {
        return -1;
    }
#endif
    if (nSerialPort >= SERIAL_PORT_N) {
        return -1;
    }
#endif
    if (nSerialPort == 0) {
        while (s_RxCounter0 == 0);

        save_sreg = SREG;
        DISABLE_GLOBAL_INT();
        data = (int)s_RxBuffer0[s_RxRdIndex0];
        if (++s_RxRdIndex0 == SERIAL_RX_BUFSIZE) {
            s_RxRdIndex0 = 0;
        }
        s_RxCounter0--;
        SREG = save_sreg;
    } else if (nSerialPort == 1) {
        while (s_RxCounter1 == 0);

        save_sreg = SREG;
        DISABLE_GLOBAL_INT();
        data = (int)s_RxBuffer1[s_RxRdIndex1];
        if (++s_RxRdIndex1 == SERIAL_RX_BUFSIZE) {
            s_RxRdIndex1 = 0;
        }
        s_RxCounter1--;
        SREG = save_sreg;
    } else {
        data = -1;
    }

    return data;
}


// シリアル入力した１文字を取得します（ノンブロッキング）
int SERIAL_getch(UINT8 nSerialPort)
{
    int data;
    uint8_t save_sreg;

#ifdef MOXA_DEBUG_CHECK_PARAM
#if (MOXA_BOARD_TYPE == MOXA_BOARD_CC2420DBK)
    if (nSerialPort == 0) {
        return -1;
    }
#endif
    if (nSerialPort >= SERIAL_PORT_N) {
        return -1;
    }
#endif
    if (nSerialPort == 0) {
        if (s_RxCounter0 == 0) {
            return -1;
        }

        save_sreg = SREG;
        DISABLE_GLOBAL_INT();
        data = (int)s_RxBuffer0[s_RxRdIndex0];
        if (++s_RxRdIndex0 == SERIAL_RX_BUFSIZE) {
            s_RxRdIndex0 = 0;
        }
        s_RxCounter0--;
        SREG = save_sreg;
    } else if (nSerialPort == 1) {
        if (s_RxCounter1 == 0) {
            return -1;
        }

        save_sreg = SREG;
        DISABLE_GLOBAL_INT();
        data = (int)s_RxBuffer1[s_RxRdIndex1];
        if (++s_RxRdIndex1 == SERIAL_RX_BUFSIZE) {
            s_RxRdIndex1 = 0;
        }
        s_RxCounter1--;
        SREG = save_sreg;
    } else {
        data = -1;
    }

    return data;
}


// 受信バッファ溢れをチェックする
BOOL SERIAL_checkRxOverflow(UINT8 nSerialPort)
{
    BOOL bFlag;

    if (nSerialPort == 0) {
        bFlag = s_RxBufferOverFlow0;
        s_RxBufferOverFlow0 = FALSE;
    } if (nSerialPort == 1) {
        bFlag = s_RxBufferOverflow1;
        s_RxBufferOverflow1 = FALSE;
    } else {
        bFlag = FALSE;
    }

    return bFlag;
}

static char s_VarArgBuffer[SERIAL_VARARG_SIZE];

// 書式付シリアル出力関数です。
MRESULT SERIAL_printf(UINT8 nSerialPort, char flash *pFmt, ...)
{
    UINT8 n;
    va_list ap;

#ifdef MOXA_DEBUG_CHECK_PARAM
#if (MOXA_BOARD_TYPE == MOXA_BOARD_CC2420DBK)
    if (nSerialPort == 0) {
        return MOXA_E_PARAM;
    }
#endif
    if (nSerialPort >= SERIAL_PORT_N || pFmt == NULL) {
        return MOXA_E_PARAM;
    }
#endif
    va_start(ap, pFmt);
    vsprintf(s_VarArgBuffer, pFmt, ap);
    va_end(ap);

    for (n=0; n<SERIAL_VARARG_SIZE; n++) {
        if (s_VarArgBuffer[n] == '\0') {
            break;
        }
        SERIAL_putchar(nSerialPort, s_VarArgBuffer[n]);
    }
    
    return MOXA_SUCCESS;
}


/*!
  USART0の送信割り込みハンドラ
  USART0のシリアル送信割り込みが発生したとき本関数が呼ばれます。
*/
//interrupt [USART0_TXC] void SERIAL_tx0Handler(void)
ISR(SIG_UART0_TRANS)
{
    if (s_TxCounter0) {
        s_TxCounter0--;

        UDR0 = s_TxBuffer0[s_TxRdIndex0];
        if (++s_TxRdIndex0 == SERIAL_TX_BUFSIZE) {
            s_TxRdIndex0 = 0;
        }
    }
}


/*!
  USART0の受信割り込みハンドラ
  USART0のシリアル受信割り込みが発生したとき本関数が呼ばれます。
*/
//interrupt [USART0_RXC] void SERIAL_rx0Handler(void)
ISR(SIG_UART0_RECV)
{
    unsigned char status;
    char data;

    status = UCSR0A;
    data = UDR0;

    if ((status & (FRAMING_ERROR | PARITY_ERROR | DATA_OVERRUN)) == 0) {
        s_RxBuffer0[s_RxWrIndex0] = data;

        if (++s_RxWrIndex0 == SERIAL_RX_BUFSIZE) {
            s_RxWrIndex0 = 0;
        }
        if (++s_RxCounter0 == SERIAL_RX_BUFSIZE) {
            s_RxCounter0 = 0;
            s_RxBufferOverFlow0 = TRUE;
        }
    }
}


/*!
  USART1の送信割り込みハンドラ
  USART1のシリアル送信割り込みが発生したとき本関数が呼ばれます。
*/
//interrupt [USART1_TXC] void SERIAL_tx1Handler(void)
ISR(SIG_UART1_TRANS)
{
    if (s_TxCounter1) {
        s_TxCounter1--;

        UDR1 = s_TxBuffer1[s_TxRdIndex1];
        if (++s_TxRdIndex1 == SERIAL_TX_BUFSIZE) {
            s_TxRdIndex1 = 0;
        }
    }
}


/*!
  USART1の受信割り込みハンドラ
  USART1のシリアル受信割り込みが発生したとき本関数が呼ばれます。
*/
//interrupt [USART1_RXC] void SERIAL_rx1Handler(void)
ISR(SIG_UART1_RECV)
{
    unsigned char status;
    char data;

    status = UCSR1A;
    data = UDR1;

    if ((status & (FRAMING_ERROR | PARITY_ERROR | DATA_OVERRUN)) == 0) {
        s_RxBuffer1[s_rxWrIndex1] = data;

        if (++s_rxWrIndex1 == SERIAL_RX_BUFSIZE) {
            s_rxWrIndex1 = 0;
        }
        if (++s_RxCounter1 == SERIAL_RX_BUFSIZE) {
            s_RxCounter1 = 0;
            s_RxBufferOverflow1 = TRUE;
        }
    }
}
