/*!
  @file
  @brief �����ʐM�`�b�vCC2420�̃��W�X�^����`
  @author Takaaki Ishizawa, Vistarica Designs Co.Ltd.
  @date   2006/02/20
  @version 0.1
 */

#ifndef CC2420_REG_H
#define CC2420_REG_H

// �R���t�B�O���[�V�������W�X�^�A�h���X
#define CC2420_SNOP             0x00 //!< NOP
#define CC2420_SXOSCON          0x01 //!< �N���X�^�����U�J�n
#define CC2420_STXCAL           0x02 //!< ���M�p���g��������𓮍싖����
#define CC2420_SRXON            0x03 //!< ��M����
#define CC2420_STXON            0x04 //!< ���M����
#define CC2420_STXONCCA         0x05 //!< �`�����l�����󂢂Ă����瑗�M����
#define CC2420_SRFOFF           0x06 //!< �S�Ă̑���M�Ɣ��U�𓮍�֎~
#define CC2420_SXOSCOFF         0x07 //!< �������M��Ɩ����@�\�̓d����؂�
#define CC2420_SFLUSHRX         0x08 //!< ��M�o�b�t�@�̃N���A
#define CC2420_SFLUSHTX         0x09 //!< ���M�o�b�t�@�̃N���A
#define CC2420_SACK             0x0A //!< pending field���N���A����ACK�t���[���̑��M
#define CC2420_SACKPEND         0x0B //!< pending field���Z�b�g����ACK�t���[���̑��M
#define CC2420_SRXDEC           0x0C //!< ��M�������̊J�n
#define CC2420_STXENC           0x0D //!< ���M�Í����̊J�n
#define CC2420_SAES             0x0E //!< AES�X�g���[�u
// not in use                   0x0F
#define CC2420_MAIN             0x10 //!< ���C���R���g���[�����W�X�^
#define CC2420_MDMCTRL0         0x11 //!< ���f���R���g���[�����W�X�^0
#define CC2420_MDMCTRL1         0x12 //!< ���f���R���g���[�����W�X�^1
#define CC2420_RSSI             0x13 //!< RSSI��CCA
#define CC2420_SYNCWORD         0x14 //!< Synchronisation word�R���g���[�����W�X�^
#define CC2420_TXCTRL           0x15 //!< ���M�R���g���[�����W�X�^
#define CC2420_RXCTRL0          0x16 //!< ��M�R���g���[�����W�X�^0
#define CC2420_RXCTRL1          0x17 //!< ��M�R���g���[�����W�X�^1
#define CC2420_FSCTRL           0x18 //!< ���g��������R���g���[�����W�X�^
#define CC2420_SECCTRL0         0x19 //!< �Z�L�����e�B�R���g���[�����W�X�^0
#define CC2420_SECCTRL1         0x1A //!< �Z�L�����e�B�R���g���[�����W�X�^1
#define CC2420_BATTMON          0x1B //!< �o�b�e���[���j�^�R���g���[��/�X�e�[�^�X���W�X�^
#define CC2420_IOCFG0           0x1C //!< I/O�R���g���[�����W�X�^0
#define CC2420_IOCFG1           0x1D //!< I/O�R���g���[�����W�X�^1
#define CC2420_MANFIDL          0x1E //!< Manufacturer ID Low word
#define CC2420_MANFIDH          0x1F //!< Manufacturer ID High word
#define CC2420_FSMTC            0x20 //!< �L���X�e�[�g�}�V�����Ԓ萔
#define CC2420_MANAND           0x21 //!< AND�}�X�N�蓮�ݒ�
#define CC2420_MANOR            0x22 //!< OR�}�X�N�蓮�ݒ�
#define CC2420_AGCCTRL          0x23 //!< AGC�R���g���[�����W�X�^
#define CC2420_AGCTST0          0x24 //!< AGC�e�X�g���W�X�^0
#define CC2420_AGCTST1          0x25 //!< AGC�e�X�g���W�X�^1
#define CC2420_AGCTST2          0x26 //!< AGC�e�X�g���W�X�^2
#define CC2420_FSTST0           0x27 //!< ���g��������e�X�g���W�X�^0
#define CC2420_FSTST1           0x28 //!< ���g��������e�X�g���W�X�^1
#define CC2420_FSTST2           0x29 //!< ���g��������e�X�g���W�X�^2
#define CC2420_FSTST3           0x2A //!< ���g��������e�X�g���W�X�^3
#define CC2420_RXBPFTST         0x2B //!< ��M�o���h�p�X�t�B���^�e�X�g���W�X�^
#define CC2420_FSMSTATE         0x2C //!< �L���X�e�[�g�}�V���X�e�[�^�X���W�X�^
#define CC2420_ADCTST           0x2D //!< ADC�e�X�g���W�X�^
#define CC2420_DACTST           0x2E //!< DAC�e�X�g���W�X�^
#define CC2420_TOPTST           0x2F //!< �g�b�v���x���e�X�g���W�X�^
#define CC2420_RESERVED         0x30 //!< �\��
// not in use             from  0x31
//                        to    0x3D
#define CC2420_TXFIFO           0x3E //!< ���MFIFO�o�b�t�@
#define CC2420_RXFIFO           0x3F //!< ��MFIFO�o�b�t�@

// �������T�C�Y��`
#define CC2420_RAM_SIZE         368 //!< RAM�T�C�Y
#define CC2420_FIFO_SIZE        128 //!< FIFO�T�C�Y

// RAM��������ԓ��A�h���X
#define CC2420RAM_TXFIFO        0x000
#define CC2420RAM_RXFIFO        0x080
#define CC2420RAM_KEY0          0x100
#define CC2420RAM_RXNONCE       0x110
#define CC2420RAM_SABUF         0x120
#define CC2420RAM_KEY1          0x130
#define CC2420RAM_TXNONCE       0x140
#define CC2420RAM_CBCSTATE      0x150
#define CC2420RAM_IEEEADDR      0x160
#define CC2420RAM_PANID         0x168
#define CC2420RAM_SHORTADDR     0x16A

// �X�e�[�^�X�o�C�g�r�b�g�}�X�N
// reserved                     7
#define CC2420_XOSC16M_STABLE   6
#define CC2420_TX_UNDERFLOW     5
#define CC2420_ENC_BUSY         4
#define CC2420_TX_ACTIVE        3
#define CC2420_LOCK             2
#define CC2420_RSSI_VALID       1
// reserved                     0

#endif
