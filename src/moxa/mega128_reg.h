/*!
  @file
  @brief ATMEGA128�̃��W�X�^����`
  @author Shinji Yamachika, Vistarica Designs Co.Ltd.
  @date   2005/11/17
  @version 0.1
*/

#ifndef __MEGA128_REG_H__
#define __MEGA128_REG_H__

// TWI�r�b�g���[�g���W�X�^�[ (TWI Bit Rate Register) TWBR
#define TWBR7  7      //!< TWI�r�b�g���[�g�I�� bit7
#define TWBR6  6      //!< TWI�r�b�g���[�g�I�� bit6
#define TWBR5  5      //!< TWI�r�b�g���[�g�I�� bit5
#define TWBR4  4      //!< TWI�r�b�g���[�g�I�� bit4
#define TWBR3  3      //!< TWI�r�b�g���[�g�I�� bit3
#define TWBR2  2      //!< TWI�r�b�g���[�g�I�� bit2
#define TWBR1  1      //!< TWI�r�b�g���[�g�I�� bit1
#define TWBR0  0      //!< TWI�r�b�g���[�g�I�� bit0


// TWI���䃌�W�X�^ (TWI Control Register) TWCR
#define TWINT  7      //!< TWI���荞�ݗv���t���O
#define TWEA   6      //!< �m�F����(ACK)����
#define TWSTA  5      //!< �J�n(START)������������
#define TWSTO  4      //!< ��~(STOP)������������
#define TWWC   3      //!< TWI�㏑���G���[�t���O
#define TWEN   2      //!< TWI���싖��
                      //   1bit�ڂ͗\�񂳂�Ă��܂�
#define TWIE   0      //!< TWI���荞�݋���


// TWI�X�e�[�^�X���W�X�^ (TWI Status Register) TWSR
#define TWS7   7      //!< TWI�X�e�[�^�X bit7
#define TWS6   6      //!< TWI�X�e�[�^�X bit6
#define TWS5   5      //!< TWI�X�e�[�^�X bit5
#define TWS4   4      //!< TWI�X�e�[�^�X bit4
#define TWS3   3      //!< TWI�X�e�[�^�X bit3
                      //   2bit�ڂ͗\�񂳂�Ă��܂�
#define TWPS1  1      //!< TWI �O�u�����I��
#define TWPS0  0      //!< TWI �O�u�����I��


// TWI�f�[�^���W�X�^ (TWI Data Register) TWDR
#define TWD7   7      //!< TWI�f�[�^ bit7
#define TWD6   6      //!< TWI�f�[�^ bit6
#define TWD5   5      //!< TWI�f�[�^ bit5
#define TWD4   4      //!< TWI�f�[�^ bit4
#define TWD3   3      //!< TWI�f�[�^ bit3
#define TWD2   2      //!< TWI�f�[�^ bit2
#define TWD1   1      //!< TWI�f�[�^ bit1
#define TWD0   0      //!< TWI�f�[�^ bit0


// TWI�X���[�u�A�h���X���W�X�^ (TWI Slave Address Register) TWAR
#define TWA6   7      //!< TWI�X���[�u�A�h���X bit6
#define TWA5   6      //!< TWI�X���[�u�A�h���X bit5
#define TWA4   5      //!< TWI�X���[�u�A�h���X bit4
#define TWA3   4      //!< TWI�X���[�u�A�h���X bit3
#define TWA2   3      //!< TWI�X���[�u�A�h���X bit2
#define TWA1   2      //!< TWI�X���[�u�A�h���X bit1
#define TWA0   1      //!< TWI�X���[�u�A�h���X bit0
#define TWGCE  0      //!< ��ČĂяo�����o����


// MCU���䃌�W�X�^ (MCU Control Register) MCUCR
#define SRE    7      //!< �O������������
#define SRW    6      //!< �E�F�C�g�I���r�b�g
#define SRW10  6      //!< ��ʗ̈�E�F�C�g�I���r�b�g0
#define SE     5      //!< �X���[�v����
#define SM1    4      //!< �X���[�v��ʑI�� bit1
#define SM0    3      //!< �X���[�v��ʑI�� bit0
#define SM2    2      //!< �X���[�v��ʑI�� bit2
#define IVSEL  1      //!< ���荞�݃x�N�^�I��
#define IVCE   0      //!< ���荞�݃x�N�^�ύX����


// �O�����������䃌�W�X�^A (External Memory Control Register A) XMCRA
                      //   7bit�ڂ͗\�񂳂�Ă��܂�
#define SRL2   6      //!< �O��SRAM�͈͑I�� bit2
#define SRL1   5      //!< �O��SRAM�͈͑I�� bit1
#define SRL0   4      //!< �O��SRAM�͈͑I�� bit0
#define SRW01  3      //!< ���ʗ̈泪�đI�� bit1
#define SRW00  2      //!< ���ʗ̈泪�đI�� bit0
#define SRW11  1      //!< ��ʗ̈泪�đI�� bit1


// �O�����������䃌�W�X�^B (External Memory Control Register B) XMCRB
#define XMBK   7      //!< �o�X�ێ�����
#define XMM2   2      //!< ��ʃA�h���X�}�X�N bit2
#define XMM1   1      //!< ��ʃA�h���X�}�X�N bit1
#define XMM0   0      //!< ��ʃA�h���X�}�X�N bit0


// �N���b�N�������䃌�W�X�^ (XTAL Divide Control Register) XDIV
#define XDIVEN 7      //!< �N���b�N��������
#define XDIV6  6      //!< �N���b�N�����l�I�� bit6
#define XDIV5  5      //!< �N���b�N�����l�I�� bit5
#define XDIV4  4      //!< �N���b�N�����l�I�� bit4
#define XDIV3  3      //!< �N���b�N�����l�I�� bit3
#define XDIV2  2      //!< �N���b�N�����l�I�� bit2
#define XDIV1  1      //!< �N���b�N�����l�I�� bit1
#define XDIV0  0      //!< �N���b�N�����l�I�� bit0


// RAM�y�[�W�I�����W�X�^ (RAM Page Z Select Register) RAMPZ
#define RAMPZ0 0      //!< �g��RAM�y�[�W Z�|�C���^


// �O�����荞�ݐ��䃌�W�X�^A (External Interrupt Control Register A) EICRA
#define ISC31  7      //!< �O�����荞��3��������
#define ISC30  6      //!< �O�����荞��3��������
#define ISC21  5      //!< �O�����荞��2��������
#define ISC20  4      //!< �O�����荞��2��������
#define ISC11  3      //!< �O�����荞��1��������
#define ISC10  2      //!< �O�����荞��1��������
#define ISC01  1      //!< �O�����荞��0��������
#define ISC00  0      //!< �O�����荞��0��������


// �O�����荞�ݐ��䃌�W�X�^B (External Interrupt Control Register B) EICRB
#define ISC71  7      //!< �O�����荞��7��������
#define ISC70  6      //!< �O�����荞��7��������
#define ISC61  5      //!< �O�����荞��6��������
#define ISC60  4      //!< �O�����荞��6��������
#define ISC51  3      //!< �O�����荞��5��������
#define ISC50  2      //!< �O�����荞��5��������
#define ISC41  1      //!< �O�����荞��4��������
#define ISC40  0      //!< �O�����荞��4��������


// �O�����荞�݃}�X�N���W�X�^ (External Interrupt Mask Register) EIMSK
#define INT7   7      //!< �O�����荞��7 ����
#define INT6   6      //!< �O�����荞��6 ����
#define INT5   5      //!< �O�����荞��5 ����
#define INT4   4      //!< �O�����荞��4 ����
#define INT3   3      //!< �O�����荞��3 ����
#define INT2   2      //!< �O�����荞��2 ����
#define INT1   1      //!< �O�����荞��1 ����
#define INT0   0      //!< �O�����荞��0 ����


// �O�����荞�ݗv���t���O���W�X�^ (External Interrupt Flag Register) EIFR
#define INTF7  7      //!< �O�����荞��7�v���t���O
#define INTF6  6      //!< �O�����荞��6�v���t���O
#define INTF5  5      //!< �O�����荞��5�v���t���O
#define INTF4  4      //!< �O�����荞��4�v���t���O
#define INTF3  3      //!< �O�����荞��3�v���t���O
#define INTF2  2      //!< �O�����荞��2�v���t���O
#define INTF1  1      //!< �O�����荞��1�v���t���O
#define INTF0  0      //!< �O�����荞��0�v���t���O


// SPM���ߐ���/�X�e�[�^�X���W�X�^ (Store Program Memory Controll and Status Register) SPMCRS
#define SPMIE  7      //!< SPM������荞�݋���
#define RWWSB  6      //!< RWW�̈���W�[
#define RWWSRE 4      //!< RWW�̈�ǂݏo������
#define BLBSET 3      //!< �u�[�g���b�N�r�b�g�ݒ�
#define PGWRT  2      //!< �y�[�W��������
#define PGERS  1      //!< �y�[�W����
#define SPMEN  0      //!< SPM���싖��


// �^�C�}/�J�E���^0 ���䃌�W�X�^ (Timer/Counter0 Control Register) TCCR0
#define FOC0   7      //!< OC0�����ύX
#define WGM00  6      //!< �g�`�������
#define COM01  5      //!< ��r0�o�͑I��
#define COM00  4      //!< ��r0�o�͑I��
#define WGM01  3      //!< �g�`�������
#define CS02   2      //!< �N���b�N�I��2
#define CS01   1      //!< �N���b�N�I��1
#define CS00   0      //!< �N���b�N�I��0


// �^�C�}/�J�E���^���荞�݃}�X�N ���W�X�^ (Timer/Counter Interrupt Mask Register) TIMSK
#define OCIE2  7      //!< �^�C�}/�J�E���^2 ��r���荞�݋���
#define TOIE2  6      //!< �^�C�}/�J�E���^2 �I�[�o�[�t���[���荞�݋���
#define TICIE1 5      //!< �^�C�}/�J�E���^1 �ߊl(�L���v�`��)���荞�݋���
#define OCIE1A 4      //!< �^�C�}/�J�E���^1 ��rA���荞�݋���
#define OCIE1B 3      //!< �^�C�}/�J�E���^1 ��rB���荞�݋���
#define TOIE1  2      //!< �^�C�}/�J�E���^1 �I�[�o�[�t���[���荞�݋���
#define OCIE0  1      //!< �^�C�}/�J�E���^0 ��r���荞�݋���
#define TOIE0  0      //!< �^�C�}/�J�E���^0 �I�[�o�[�t���[���荞�݋���


// �^�C�}/�J�E���^���荞�ݗv���t���O���W�X�^ (Timer/Counter Interrupt Flag Register) TIFR
#define OCF2   7      //!< �^�C�}/�J�E���^2 ��r���荞�ݗv���t���O
#define TOV2   6      //!< �^�C�}/�J�E���^2 �I�[�o�[�t���[���荞�ݗv���t���O
#define ICF1   5      //!< �L���v�`�������ݗv���t���O
#define OCF1A  4      //!< ��r�v�������݃t���O1A
#define OCF1B  3      //!< ��r�v�������݃t���O1B
#define TOV1   2      //!< �^�C�}/�J�E���^ �I�[�o�[�t���[�t���O
#define OCF0   1      //!< �^�C�}/�J�E���^0 ��r���荞�ݗv���t���O
#define TOV0   0      //!< �^�C�}/�J�E���^0 �I�[�o�[�t���[���荞�ݗv���t���O


// �^�C�}/�J�E���^0�񓯊��X�e�[�^�X���W�X�^ (Timer/Counter0 Asynchronous Status Register) ASSR
#define AS0    3      //!< �^�C�}/�J�E���^0�񓯊����싖��
#define TCN0UB 2      //!< �^�C�}/�J�E���^0�X�V���t���O
#define OCR0UB 1      //!< ��r0���W�X�^�X�V���t���O
#define TCR0UB 0      //!< �^�C�}/�J�E���^0���䃌�W�X�^�X�V���t���O


// ����I/O�@�\���W�X�^ (Special Function I/O Register) SFIOR
#define TSM    7      //!< �^�C�}/�J�E���^�������샂�[�h
#define ADHSM  4      //!< ���̋@�\�͍폜����܂����A����4bit�ڂ͗\�񂳂�Ă��܂�
#define ACME   3      //!< �A�i���O��r��}���`�v���N�T����
#define PUD    2      //!< �v���A�b�v�֎~�r�b�g
#define PSR0   1      //!< �^�C�}/�J�E���^0 �O�u�����탊�Z�b�g
#define PSR321 0      //!< �^�C�}/�J�E���^3,2,1 �O�u�����탊�Z�b�g


// �^�C�}/�J�E���^1���䃌�W�X�^A (Timer/Counter1 Control Register A) TCCR1A
#define COM1A1 7      //!< ��r1A�o�͑I�� bit1
#define COM1A0 6      //!< ��r1A�o�͑I�� bit0
#define COM1B1 5      //!< ��r1B�o�͑I�� bit1
#define COM1B0 4      //!< ��r1B�o�͑I�� bit0
#define COM1C1 3      //!< ��r1C�o�͑I�� bit1
#define COM1C0 2      //!< ��r1C�o�͑I�� bit0
#define WGM11  1      //!< �g�`������� bit1
#define WGM10  0      //!< �g�`������� bit0


// �^�C�}/�J�E���^3���䃌�W�X�^A (Timer/Counter3 Control Register A) TCCR3A
#define COM3A1 7      //!< ��r3A�o�͑I�� bit1
#define COM3A0 6      //!< ��r3A�o�͑I�� bit0
#define COM3B1 5      //!< ��r3B�o�͑I�� bit1
#define COM3B0 4      //!< ��r3B�o�͑I�� bit0
#define COM3C1 3      //!< ��r3C�o�͑I�� bit1
#define COM3C0 2      //!< ��r3C�o�͑I�� bit0
#define WGM31  1      //!< �g�`������� bit1
#define WGM30  0      //!< �g�`������� bit0


// �^�C�}/�J�E���^1���䃌�W�X�^B (Timer/Counter1 Control Register B) TCCR1B
#define ICNC1  7      //!< �L���v�`���N������1 �m�C�Y��������
#define ICES1  6      //!< �L���v�`���N������1 �G�b�W�I��
                      //   5bit�ڂ͗\�񂳂�Ă��܂�
#define WGM13  4      //!< �g�`�������[�h�̎w��
#define WGM12  3      //!< �g�`�������[�h�̎w��
#define CS12   2      //!< �N���b�N�I��2
#define CS11   1      //!< �N���b�N�I��1
#define CS10   0      //!< �N���b�N�I��0


// �^�C�}/�J�E���^3���䃌�W�X�^B (Timer/Counter3 Control Register B) TCCR3B
#define ICNC3  7      //!< �L���v�`���N������3 �m�C�Y��������
#define ICES3  6      //!< �L���v�`���N������3 �G�b�W�I��
                      //   5bit�ڂ͗\�񂳂�Ă��܂�
#define WGM33  4      //!< �g�`�������[�h�̎w��
#define WGM32  3      //!< �g�`�������[�h�̎w��
#define CS32   2      //!< �N���b�N�I��2
#define CS31   1      //!< �N���b�N�I��1
#define CS30   0      //!< �N���b�N�I��0


// �^�C�}/�J�E���^1���䃌�W�X�^C (Timer/Counter1 Control Register C) TCCR1C
#define FOC1A  7      //!< OC1A�����ύX
#define FOC1B  6      //!< OC1B�����ύX
#define FOC1C  5      //!< OC1B�����ύX


// �^�C�}/�J�E���^3���䃌�W�X�^C (Timer/Counter3 Control Register C) TCCR1C
#define FOC3A  7      //!< OC3A�����ύX
#define FOC3B  6      //!< OC3B�����ύX
#define FOC3C  5      //!< OC3C�����ύX


// �g���^�C�}/�J�E���^���荞�݃}�X�N���W�X�^
// (Extended Timer/Counter Interrupt Mask Register) ETIMSK
                      //   7,6bit�ڂ͗\�񂳂�Ă��܂�
#define TICIE3 5      //!< �^�C�}/�J�E���^3 �L���v�`�����荞�݋���
#define OCIE3A 4      //!< �^�C�}/�J�E���^3 ��rA���荞�݋���
#define OCIE3B 3      //!< �^�C�}/�J�E���^3 ��rB���荞�݋���
#define TOIE3  2      //!< �^�C�}/�J�E���^3 �I�[�o�[�t���[���荞�݋���
#define OCIE3C 1      //!< �^�C�}/�J�E���^3 ��rC���荞�݋���
#define OCIE1C 0      //!< �^�C�}/�J�E���^1 ��rC���荞�݋���


// �g���^�C�}/�J�E���^���荞�ݗv���t���O���W�X�^
// (Extended Timer/Counter Interrupt Flag Register) ETIFR
                      //   7,6bit�ڂ͗\�񂳂�Ă��܂�
#define ICF3   5      //!< �^�C�}/�J�E���^3 �L���v�`�����荞�ݗv���t���O
#define OCF3A  4      //!< �^�C�}/�J�E���^3 ��rA���荞�ݗv���t���O
#define OCF3B  3      //!< �^�C�}/�J�E���^3 ��rB���荞�ݗv���t���O
#define TOV3   2      //!< �^�C�}/�J�E���^3 �I�[�o�[�t���[���荞�ݗv���t���O
#define OCF3C  1      //!< �^�C�}/�J�E���^3 ��rC���荞�ݗv���t���O
#define OCF1C  0      //!< �^�C�}/�J�E���^1 ��rC���荞�ݗv���t���O


// 8bit �^�C�}/�J�E���^2���䃌�W�X�^ (Timer/Counter2 Control Register) TCCR2
#define FOC2   7      //!< OC2�����ύX
#define WGM20  6      //!< �g�`�������[�h�̎w�� bit0
#define COM21  5      //!< ��r2�o�͑I�����[�h�̎w�� bit1
#define COM20  4      //!< ��r2�o�͑I�����[�h�̎w�� bit0
#define WGM21  3      //!< �g�`�������[�h�̎w�� bit1
#define CS22   2      //!< �N���b�N�I��2 bit2
#define CS21   1      //!< �N���b�N�I��2 bit1
#define CS20   0      //!< �N���b�N�I��2 bit0


// SPI���䃌�W�X�^ (SPI Control Register) SPCR
#define SPIE   7      //!< SPI���荞�݋���
#define SPE    6      //!< SPI����
#define DORD   5      //!< �f�[�^���I��
#define MSTR   4      //!< �}�X�^/�X���[�u�I��
#define CPOL   3      //!< SCK�ɐ��I��
#define CPHA   2      //!< SCK�ʑ��I��
#define SPR1   1      //!< SPI�N���b�N�I�� bit1
#define SPR0   0      //!< SPI�N���b�N�I�� bit0


// �^�C�}/�J�E���^ ���䃌�W�X�^
#define FOC    7      //!< OC0�����ύX
#define WGM0   6      //!< �g�`�������
#define COM1   5      //!< ��r0�o�͑I��
#define COM0   4      //!< ��r0�o�͑I��
#define WGM1   3      //!< �g�`�������
#define CS2    2      //!< �N���b�N�I��2
#define CS1    1      //!< �N���b�N�I��1
#define CS0    0      //!< �N���b�N�I��0


// �^�C�}/�J�E���^ ���䃌�W�X�^A
#define COMA1  7
#define COMA0  6
#define COMB1  5
#define COMB0  4
#define COMC1  3
#define COMC0  2
#define WGMA1  1
#define WGMA0  0


// �^�C�}/�J�E���^ ����/�X�e�[�^�X���W�X�^B
#define ICNC   7
#define ICES   6
#define WGMB3  4
#define WGMB2  3
#define CSB2   2
#define CSB1   1
#define CSB0   0


// �^�C�}/�J�E���^ ���䃌�W�X�^C
#define FOCA   7
#define FOCB   6
#define FOCC   5


// �����f�o�b�O���W�X�^ (On-chip Debug Register) OCDR
#define IDRD   7
#define OCDR7  7
#define OCDR6  6
#define OCDR5  5
#define OCDR4  4
#define OCDR3  3
#define OCDR2  2
#define OCDR1  1
#define OCDR0  0


// �E�H�b�`�h�b�O�^�C�}���䃌�W�X�^ (Watchdog Timer Control Register) WDTCR
                      //   7,6,5bit�ڂ͗\�񂳂�Ă��܂�
#define WDCE   4      //!< �E�H�b�`�h�b�O�ύX����
#define WDE    3      //!< �E�H�b�`�h�b�O����
#define WDP2   2      //!< �E�H�b�`�h�b�O�^�C�}�O�u�����I�� bit2
#define WDP1   1      //!< �E�H�b�`�h�b�O�^�C�}�O�u�����I�� bit1
#define WDP0   0      //!< �E�H�b�`�h�b�O�^�C�}�O�u�����I�� bit0


// SPI�X�e�[�^�X���W�X�^ (SPI Status Register) SPSR
#define SPIF   7      //!< SPI���荞�ݗv���t���O
#define WCOL   6      //!< �㏑���G���[�t���O
                      //   5,4,3,2,1bit�ڂ͗\�񂳂�Ă��܂�
#define SPI2X  0      //!< SPI�{������


// �ėpUSART���䃌�W�X�^A (USART Control Register A)
#define RXC    7      //!< USART��M�����t���O
#define TXC    6      //!< USART0���M�����t���O
#define UDRE   5      //!< USART0���M�f�[�^���W�X�^�󂫃t���O
#define FE     4      //!< �t���[�~���O�G���[�t���O
#define DOR    3      //!< �f�[�^�I�[�o�[�����G���[�t���O
#define UPE    2      //!< �p���e�B�G���[�t���O
#define U2X    1      //!< �{������
#define MPCM   0      //!< �}���`�v���Z�b�T�ʐM���[�h


// USART0����/�X�e�[�^�X���W�X�^A (USART0 Control and Status Register A) UCSR0A
#define RXC0   7      //!< USART0��M�����t���O
#define TXC0   6      //!< USART0���M�����t���O
#define UDRE0  5      //!< USART0���M�f�[�^���W�X�^�󂫃t���O
#define FE0    4      //!< �t���[�~���O�G���[�t���O
#define DOR0   3      //!< �f�[�^�I�[�o�[�����G���[�t���O
#define UPE0   2      //!< �p���e�B�G���[�t���O
#define U2X0   1      //!< �{������
#define MPCM0  0      //!< �}���`�v���Z�b�T�ʐM���[�h


// USART1����/�X�e�[�^�X���W�X�^A (USART1 Control and Status Register A) UCSR1A
#define RXC1   7      //!< USART1��M�����t���O
#define TXC1   6      //!< USART1���M�����t���O
#define UDRE1  5      //!< USART1���M�f�[�^���W�X�^�󂫃t���O
#define FE1    4      //!< �t���[�~���O�G���[�t���O
#define DOR1   3      //!< �f�[�^�I�[�o�[�����G���[�t���O
#define UPE1   2      //!< �p���e�B�G���[�t���O
#define U2X1   1      //!< �{������
#define MPCM1  0      //!< �}���`�v���Z�b�T�ʐM���[�h


// �ėpUSART���䃌�W�X�^B (USART Control Register B)
#define RXCIE  7      //!< ��M�������荞�݋���
#define TXCIE  6      //!< ���M�������荞�݋���
#define UDRIE  5      //!< ���M�f�[�^���W�X�^�󂫊��荞�݋���
#define RXEN   4      //!< ��M����
#define TXEN   3      //!< ���M����
#define UCSZ   2      //!< �f�[�^�r�b�g���I��
#define UCSZ2  2      //!< �f�[�^�r�b�g���I��2
#define RXB8   1      //!< ��M�f�[�^�r�b�g
#define TXB8   0      //!< ���M�f�[�^�r�b�g


// USART0����/�X�e�[�^�X���W�X�^B (USART0 Control and Status Register B) UCSR0B
#define RXCIE0 7      //!< ��M�������荞�݋���
#define TXCIE0 6      //!< ���M�������荞�݋���
#define UDRIE0 5      //!< ���M�f�[�^���W�X�^�󂫊��荞�݋���
#define RXEN0  4      //!< ��M����
#define TXEN0  3      //!< ���M����
#define UCSZ02 2      //!< �f�[�^�r�b�g���I��2
#define RXB80  1      //!< ��M�f�[�^�r�b�g
#define TXB80  0      //!< ���M�f�[�^�r�b�g


// USART1����/�X�e�[�^�X���W�X�^B (USART1 Control and Status Register B) UCSR1B
#define RXCIE1 7      //!< ��M�������荞�݋���
#define TXCIE1 6      //!< ���M�������荞�݋���
#define UDRIE1 5      //!< ���M�f�[�^���W�X�^�󂫊��荞�݋���
#define RXEN1  4      //!< ��M����
#define TXEN1  3      //!< ���M����
#define UCSZ12 2      //!< �f�[�^�r�b�g���I��2
#define RXB81  1      //!< ��M�f�[�^�r�b�g
#define TXB81  0      //!< ���M�f�[�^�r�b�g


// �ėpUSART���W�X�^C (USART Register C)
                      //   7bit�ڂ͗\�񂳂�Ă��܂�
#define UMSEL  6      //!< USART0����I��
#define UPM1   5      //!< �p���e�B�I�� 1bit
#define UPM0   4      //!< �p���e�B�I�� 0bit
#define USBS   3      //!< �X�g�b�v�r�b�g�I��
#define UCSZ1  2      //!< �f�[�^�r�b�g���I�� 1bit
#define UCSZ0  1      //!< �f�[�^�r�b�g���I�� 0bit
#define UCPOL  0      //!< �N���b�N�ɐ��I��


// USART0����/�X�e�[�^�X���W�X�^C (USART0 Control and Status Register C) UCSR0C
                      //   7bit�ڂ͗\�񂳂�Ă��܂�
#define UMSEL0 6      //!< USART0����I��
#define UPM01  5      //!< �p���e�B�I�� 1bit
#define UPM00  4      //!< �p���e�B�I�� 0bit
#define USBS0  3      //!< �X�g�b�v�r�b�g�I��
#define UCSZ01 2      //!< �f�[�^�r�b�g���I�� 1bit
#define UCSZ00 1      //!< �f�[�^�r�b�g���I�� 0bit
#define UCPOL0 0      //!< �N���b�N�ɐ��I��


// USART1����/�X�e�[�^�X���W�X�^C (USART1 Control and Status Register C) UCSR1C
                      //   7bit�ڂ͗\�񂳂�Ă��܂�
#define UMSEL1 6      //!< USART1����I��
#define UPM11  5      //!< �p���e�B�I�� 1bit
#define UPM10  4      //!< �p���e�B�I�� 0bit
#define USBS1  3      //!< �X�g�b�v�r�b�g�I��
#define UCSZ11 2      //!< �f�[�^�r�b�g���I�� 1bit
#define UCSZ10 1      //!< �f�[�^�r�b�g���I�� 0bit
#define UCPOL1 0      //!< �N���b�N�ɐ��I��


// A/D�ϊ��`�����l���I�����W�X�^ (ADC Multiplexer Select Register) ADMUX
#define REFS1  7      //!< ��d���I�� bit1
#define REFS0  6      //!< ��d���I�� bit0
#define ADLAR  5      //!< �������I��
#define MUX4   4      //!< A/D�`�����l���I��bit4
#define MUX3   3      //!< A/D�`�����l���I��bit3
#define MUX2   2      //!< A/D�`�����l���I��bit2
#define MUX1   1      //!< A/D�`�����l���I��bit1
#define MUX0   0      //!< A/D�`�����l���I��bit0


// A/D�ϊ� ����/�X�e�[�^�X���W�X�^A (ADC Control and Status Register A) ADCSRA
#define ADEN   7      //!< A/D����
#define ADSC   6      //!< A/D�ϊ��J�n
#define ADFR   5      //!< �A��/�P�ƕϊ�����I��
#define ADIF   4      //!< A/D�ϊ��������荞�ݗv���t���O
#define ADIE   3      //!< A/D�ϊ��������荞�݋���
#define ADPS2  2      //!< A/D�ϊ��N���b�N�I�� bit2
#define ADPS1  1      //!< A/D�ϊ��N���b�N�I�� bit1
#define ADPS0  0      //!< A/D�ϊ��N���b�N�I�� bit0


// �A�i���O��r�� ����/�X�e�[�^�X���W�X�^ (Analog Comparator Control and Status Register) ACSR
#define ACD    7      //!< �A�i���O��r��֎~
#define ACBG   6      //!< ��d���I��
#define ACO    5      //!< �A�i���O��r��o��
#define ACI    4      //!< �A�i���O��r�튄�荞�ݗv���t���O
#define ACIE   3      //!< �A�i���O��r�튄�荞�݋���
#define ACIC   2      //!< �A�i���O��r��L���v�`���N������
#define ACIS1  1      //!< �A�i���O��r�튄�荞�ݏ��� bit1
#define ACIS0  0      //!< �A�i���O��r�튄�荞�ݏ��� bit0


// MCU����/�X�e�[�^�X���W�X�^ (MCU Control and Status Register) MCUCSR
#define JTD    7      //!< JTAG�C���^�[�t�F�C�X�֎~
                      //   5,6bit�ڂ͗\�񂳂�Ă��܂�
#define JTRF   4      //!< JTAG���Z�b�g�t���O
#define WDRF   3      //!< �E�H�b�`�h�b�O���Z�b�g�t���O
#define BORF   2      //!< ��d�����Z�b�g�t���O
#define EXTRF  1      //!< �O�����Z�b�g�t���O
#define PORF   0      //!< �d��ON���Z�b�g�t���O


// �|�[�gA �o�̓��W�X�^ (Port A Data Register) PORTA
#define PA7    7
#define PA6    6
#define PA5    5
#define PA4    4
#define PA3    3
#define PA2    2
#define PA1    1
#define PA0    0


// �|�[�gA �f�[�^�������W�X�^ (Port A Data Direction Register) DDRA
#define DDA7   7
#define DDA6   6
#define DDA5   5
#define DDA4   4
#define DDA3   3
#define DDA2   2
#define DDA1   1
#define DDA0   0


// �|�[�gA ���̓��W�X�^ (Port A Input Address) PINA
#define PINA7  7
#define PINA6  6
#define PINA5  5
#define PINA4  4
#define PINA3  3
#define PINA2  2 
#define PINA1  1
#define PINA0  0


// �|�[�gB �o�̓��W�X�^ (Port B Data Register) PORTB
#define PB7    7
#define PB6    6
#define PB5    5
#define PB4    4
#define PB3    3
#define PB2    2
#define PB1    1
#define PB0    0


// �|�[�gB �f�[�^�������W�X�^ (Port B Data Direction Register) DDRB
#define DDB7   7
#define DDB6   6
#define DDB5   5
#define DDB4   4
#define DDB3   3
#define DDB2   2
#define DDB1   1
#define DDB0   0


// �|�[�gB ���̓��W�X�^ (Port B Input Address) PINB
#define PINB7  7
#define PINB6  6
#define PINB5  5
#define PINB4  4
#define PINB3  3
#define PINB2  2 
#define PINB1  1
#define PINB0  0


// �|�[�gC �o�̓��W�X�^ (Port C Data Register) PORTC
#define PC7    7
#define PC6    6
#define PC5    5
#define PC4    4
#define PC3    3
#define PC2    2
#define PC1    1
#define PC0    0


// �|�[�gC �f�[�^�������W�X�^ (Port C Data Direction Register) DDRC
#define DDC7   7
#define DDC6   6
#define DDC5   5
#define DDC4   4
#define DDC3   3
#define DDC2   2
#define DDC1   1
#define DDC0   0


// �|�[�gC ���̓��W�X�^ (Port C Input Address) PINC
#define PINC7  7
#define PINC6  6
#define PINC5  5
#define PINC4  4
#define PINC3  3
#define PINC2  2 
#define PINC1  1
#define PINC0  0


// �|�[�gD �o�̓��W�X�^ (Port D Data Register) PORTD
#define PD7    7
#define PD6    6
#define PD5    5
#define PD4    4
#define PD3    3
#define PD2    2
#define PD1    1
#define PD0    0


// �|�[�gD �f�[�^�������W�X�^ (Port D Data Direction Register) DDRD
#define DDD7   7
#define DDD6   6
#define DDD5   5
#define DDD4   4
#define DDD3   3
#define DDD2   2
#define DDD1   1
#define DDD0   0


// �|�[�gD ���̓��W�X�^ (Port D Input Address) PIND
#define PIND7  7
#define PIND6  6
#define PIND5  5
#define PIND4  4
#define PIND3  3
#define PIND2  2 
#define PIND1  1
#define PIND0  0


// �|�[�gE �o�̓��W�X�^ (Port E Data Register) PORTE
#define PE7    7
#define PE6    6
#define PE5    5
#define PE4    4
#define PE3    3
#define PE2    2
#define PE1    1
#define PE0    0


// �|�[�gE �f�[�^�������W�X�^ (Port E Data Direction Register) DDRE
#define DDE7   7
#define DDE6   6
#define DDE5   5
#define DDE4   4
#define DDE3   3
#define DDE2   2
#define DDE1   1
#define DDE0   0


// �|�[�gE ���̓��W�X�^ (Port E Input Address) PINE
#define PINE7  7
#define PINE6  6
#define PINE5  5
#define PINE4  4
#define PINE3  3
#define PINE2  2 
#define PINE1  1
#define PINE0  0


// �|�[�gF �o�̓��W�X�^ (Port F Data Register) PORTF
#define PF7    7
#define PF6    6
#define PF5    5
#define PF4    4
#define PF3    3
#define PF2    2
#define PF1    1
#define PF0    0


// �|�[�gF �f�[�^�������W�X�^ (Port F Data Direction Register) DDRF
#define DDF7   7
#define DDF6   6
#define DDF5   5
#define DDF4   4
#define DDF3   3
#define DDF2   2
#define DDF1   1
#define DDF0   0


// �|�[�gF ���̓��W�X�^ (Port F Input Address) PINF
#define PINF7  7
#define PINF6  6
#define PINF5  5
#define PINF4  4
#define PINF3  3
#define PINF2  2 
#define PINF1  1
#define PINF0  0


// �|�[�gG �o�̓��W�X�^ (Port G Data Register) PORTG
#define PG4    4
#define PG3    3
#define PG2    2
#define PG1    1
#define PG0    0


// �|�[�gG �f�[�^�������W�X�^ (Port G Data Direction Register) DDRG
#define DDG4   4
#define DDG3   3
#define DDG2   2
#define DDG1   1
#define DDG0   0


// �|�[�gG ���̓��W�X�^ (Port G Input Address) PING
#define PING4  4
#define PING3  3
#define PING2  2 
#define PING1  1
#define PING0  0

/* Constants */
#define SPM_PAGESIZE  256
#define RAMEND        0x10FF     //!< ����SRAM�̏I�[��\���܂�
#define XRAMEND       0xFFFF     //!< RAM��������Ԃ̏I�[��\���܂�
#define E2END         0x0FFF
#define FLASHEND      0x1FFFF

#endif /* __MEGA128_REG_H__ */
