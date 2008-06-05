/*!
  @file
  @brief �e����L�̃n�[�h�E�F�A�\���̒�`�t�@�C��

  �e��ɓ��L�̃n�[�h�E�F�A�\���A�s���z�u���`���Ă��܂��B

  @author Takaaki Ishizawa
  @date   2006/02/20
  @version 0.1
*/

#ifndef BOARD_H
#define BOARD_H


/***********************************************************************************
 * PROTO1�{�[�h
 ***********************************************************************************/
#if (MOXA_BOARD_TYPE == MOXA_BOARD_PROTO_1) | (MOXA_BOARD_TYPE == MOXA_BOARD_STK300)

// ATMEGA128�s���z�u

// PortB
#define CSN             0   //!< PB.0 - Output: SPI Chip Select (CS_N)
#define SCK             1   //!< PB.1 - Output: SPI Serial Clock (SCLK)
#define MOSI            2   //!< PB.2 - Output: SPI Master out - slave in (MOSI)
#define MISO            3   //!< PB.3 - Input:  SPI Master in - slave out (MISO)
#define SPPIO_0         4   //!< PB.4 - Output: General I/O SPPIO_0
#define VREG_EN         5   //!< PB.5 - Output: VREG_EN to CC2420
#define RESET_N         6   //!< PB.6 - Output: RESET_N to CC2420
#define SPPIO_1         7   //!< PB.7 - Output: General I/O SPPIO_1

// PortD
#define SCL             0   //!< PD.0 - Input:  I2C CLock
#define SDA             1   //!< PD.1 - Input:  I2C DAta
#define UART1_RXD       2   //!< PD.2 - Input:  UART1 RXD
#define UART1_TXD       3   //!< PD.3 - Output: UART1 TXD
#define SFD             4   //!< PD.4 - Input:  SFD from CC2420
#define SPPIO_2         5   //!< PD.5 - Output: General I/O SPPIO_2
#define CCA             6   //!< PD.6 - Input:  CCA from CC2420
#define SPPIO_3         7   //!< PD.7 - Output: General I/O SPPIO_3

// PortE
#define UART0_RXD       0   //!< PE.0 - Input:  UART0 RXD
#define UART0_TXD       1   //!< PE.1 - Output: UART0 TXD
#define SPPIO_4         2   //!< PE.2 - Output: General I/O SPPIO_4
#define SPPIO_5         3   //!< PE.3 - Output: General I/O SPPIO_5
#define SPPIO_6         4   //!< PE.4 - Output: General I/O SPPIO_6
#define SPPIO_7         5   //!< PE.5 - Output: General I/O SPPIO_7
#define FIFOP           6   //!< PE.6 - Input: FIFOP from CC2420
#define FIFO            7   //!< PE.7 - Input : FIFO from CC2420

// PortF
#define SPADC_0         0   //!< PF.0 - ADC0
#define SPADC_1         1   //!< PF.1 - ADC1
#define SPADC_2         2   //!< PF.2 - ADC2
#define SPADC_3         3   //!< PF.3 - ADC3
#define SPADC_4         4   //!< PF.4 - ADC4
#define SPADC_5         5   //!< PF.5 - ADC5
#define SPADC_6         6   //!< PF.6 - ADC6
#define SPADC_7         7   //!< PF.7 - ADC7

// for JTAG interface
//                               PF.4 - Input : JTAG TCK serial clock
//                               PF.5 - Input : JTAG TMS strobe enable
//                               PF.6 - Output: JTAG TDO serial data output
//                               PF.7 - Input : JTAG TDI serial data input

// PortA, PortC, PortG 
//                               PA and PC - Multiplexed address/data
//                               PG.0 - Output: Write enable: WR_N
//                               PG.1 - Output: Read enable: RD_N
//                               PG.2 - Output: Address Latch Enable: ALE

// SPI�ʐM����
#define SPI_ENABLE()                (PORTB &= ~BM(CSN))                      //!< SPI�ʐM����
#define SPI_DISABLE()               (PORTB |= BM(CSN))                       //!< SPI�ʐM���֎~

// CC2420�R���t�B�O

// �e�s���̏��
#define FIFO_IS_1                   (!!(PINE & BM(FIFO)))                    //!< FIFO�s����High���
#define CCA_IS_1                    (!!(PIND & BM(CCA)))                     //!< CCA�s����High���
#define RESET_IS_1                  (!!(PINB & BM(RESET_N)))                 //!< RESET_N�s����High���
#define VREG_IS_1                   (!!(PINB & BM(VREG_EN)))                 //!< VREG�s����High���
#define FIFOP_IS_1                  (!!(PINE & BM(FIFOP)))                   //!< FIFOP�s����High���
#define SFD_IS_1                    (!!(PIND & BM(SFD)))                     //!< SFD�s����High���

// RESET_N�s���̑���
#define SET_RESET_ACTIVE()          PORTB &= ~BM(RESET_N)                    //!< RESET_N�s����High��Ԃɐݒ�
#define SET_RESET_INACTIVE()        PORTB |= BM(RESET_N)                     //!< RESET_N�s����High��Ԃɐݒ�

// VREG�s���̑���
#define SET_VREG_ACTIVE()           PORTB |= BM(VREG_EN)                     //!< VREG�s����High��Ԃɐݒ�
#define SET_VREG_INACTIVE()         PORTB &= ~BM(VREG_EN)                    //!< VREG�s����High��Ԃɐݒ�

// FIFOP���荞�݁i���G�b�W�g���K�j
#define FIFOP_INT_INIT()            { EICRB |= 0x30; CLEAR_FIFOP_INT(); }    //!< FIFOP���荞�ݏ�����
#define ENABLE_FIFOP_INT()          (EIMSK |= 0x40)                          //!< FIFOP���荞�݋���
#define DISABLE_FIFOP_INT()         (EIMSK &= ~0x40)                         //!< FIFOP���荞�݋֎~
#define CLEAR_FIFOP_INT()           (EIFR = 0x40)                            //!< FIFOP���荞�݃t���O�̃N���A

// SFD���荞�݁i�^�C�}1�𗘗p�j
#define ENABLE_SFD_CAPTURE_INT()    (TIMSK |= BM(TICIE1))                    //!< SFD���荞�݋���
#define DISABLE_SFD_CAPTURE_INT()   (TIMSK &= ~BM(TICIE1))                   //!< SFD���荞�݋֎~
#define CLEAR_SFD_CAPTURE_INT()     (TIFR = BM(ICF1))                        //!< SFD���荞�݃t���O�̃N���A




/***********************************************************************************
 * CC2420DBK�{�[�h
 ***********************************************************************************/
#elif (MOXA_BOARD_TYPE == MOXA_BOARD_CC2420DBK)

// ATMEGA128�s���z�u

// PortB
#define CSN             0   //!< PB.0 - Output: SPI Chip Select (CS_N)
#define SCK             1   //!< PB.1 - Output: SPI Serial Clock (SCLK)
#define MOSI            2   //!< PB.2 - Output: SPI Master out - slave in (MOSI)
#define MISO            3   //!< PB.3 - Input:  SPI Master in - slave out (MISO)
#define SPPIO_1         4   //!< PB.4 - Output: General I/O SPPIO_1
#define VREG_EN         5   //!< PB.5 - Output: VREG_EN to CC2420
#define RESET_N         6   //!< PB.6 - Output: RESET_N to CC2420
#define SPPIO_0         7   //!< PB.7 - Output: General I/O SPPIO_0

// PortD
#define FIFOP           0   //!< PD.0 - Input:  FIFOP from CC2420
#define FIFO            1   //!< PD.1 - Input:  FIFO from CC2420
#define UART1_RXD       2   //!< PD.2 - Input:  UART1 RXD
#define UART1_TXD       3   //!< PD.3 - Output: UART1 TXD
#define SFD             4   //!< PD.4 - Input:  SFD from CC2420
#define UART1_RTS       5   //!< PD.5 - Output: UART HW handshaking: RTS
#define CCA             6   //!< PD.6 - Input:  CCA from CC2420
#define UART1_CTS       7   //!< PD.7 - Input:  UART HW handshaking: CTS

// PortE
#define SPPIO_2         3   //!< PE.3 - Output: General I/O SPPIO_2
#define SPPIO_3         4   //!< PE.4 - Output: General I/O SPPIO_3
#define SPPIO_4         5   //!< PE.5 - Output: General I/O SPPIO_4
#define SPPIO_7         7   //!< PE.7 - Output: General I/O SPPIO_7

// PortF
#define SPADC_0         0   //!< PF.0 - ADC0 (on-board potentiometer)
#define SPADC_1         1   //!< PF.1 - ADC1
#define SPADC_2         2   //!< PF.2 - ADC2
#define SPADC_3         3   //!< PF.3 - ADC3 (on-board temperature sensor)
#define SPADC_4         4   //!< PF.4 - ADC4
#define SPADC_5         5   //!< PF.5 - ADC5
#define SPADC_6         6   //!< PF.6 - ADC6
#define SPADC_7         7   //!< PF.7 - ADC7

// for JTAG interface
//                               PF.4 - Input : JTAG TCK serial clock
//                               PF.5 - Input : JTAG TMS strobe enable
//                               PF.6 - Output: JTAG TDO serial data output
//                               PF.7 - Input : JTAG TDI serial data input

// PortA, PortC, PortG 
//                               PA and PC - Multiplexed address/data
//                               PG.0 - Output: Write enable: WR_N
//                               PG.1 - Output: Read enable: RD_N
//                               PG.2 - Output: Address Latch Enable: ALE

// SPI�ʐM����
#define SPI_ENABLE()                (PORTB &= ~BM(CSN))                      //!< SPI�ʐM����
#define SPI_DISABLE()               (PORTB |= BM(CSN))                       //!< SPI�ʐM���֎~

// CC2420�R���t�B�O

// �e�s���̏��
#define FIFO_IS_1                   (!!(PIND & BM(FIFO)))                    //!< FIFO�s����High���
#define CCA_IS_1                    (!!(PIND & BM(CCA)))                     //!< CCA�s����High���
#define RESET_IS_1                  (!!(PINB & BM(RESET_N)))                 //!< RESET_N�s����High���
#define VREG_IS_1                   (!!(PINB & BM(VREG_EN)))                 //!< VREG�s����High���
#define FIFOP_IS_1                  (!!(PIND & BM(FIFOP)))                   //!< FIFOP�s����High���
#define SFD_IS_1                    (!!(PIND & BM(SFD)))                     //!< SFD�s����High���

// RESET_N�s���̑���
#define SET_RESET_ACTIVE()          PORTB &= ~BM(RESET_N)                    //!< RESET_N�s����High��Ԃɐݒ�
#define SET_RESET_INACTIVE()        PORTB |= BM(RESET_N)                     //!< RESET_N�s����High��Ԃɐݒ�

// VREG�s���̑���
#define SET_VREG_ACTIVE()           PORTB |= BM(VREG_EN)                     //!< VREG�s����High��Ԃɐݒ�
#define SET_VREG_INACTIVE()         PORTB &= ~BM(VREG_EN)                    //!< VREG�s����High��Ԃɐݒ�

// FIFOP���荞�݁i���G�b�W�g���K�j
#define FIFOP_INT_INIT()            { EICRA |= 0x03; CLEAR_FIFOP_INT(); }    //!< FIFOP���荞�ݏ�����
#define ENABLE_FIFOP_INT()          (EIMSK |= 0x01)                          //!< FIFOP���荞�݋���
#define DISABLE_FIFOP_INT()         (EIMSK &= ~0x01)                         //!< FIFOP���荞�݋֎~
#define CLEAR_FIFOP_INT()           (EIFR = 0x01)                            //!< FIFOP���荞�݃t���O�̃N���A

// SFD���荞�݁i�^�C�}1�𗘗p�j
#define ENABLE_SFD_CAPTURE_INT()    (TIMSK |= BM(TICIE1))                    //!< SFD���荞�݋���
#define DISABLE_SFD_CAPTURE_INT()   (TIMSK &= ~BM(TICIE1))                   //!< SFD���荞�݋֎~
#define CLEAR_SFD_CAPTURE_INT()     (TIFR = BM(ICF1))                        //!< SFD���荞�݃t���O�̃N���A



#endif // MOXA_BOARD_TYPE

#endif // BOARD_H
