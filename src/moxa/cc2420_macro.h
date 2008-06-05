/*!
  @file
  @brief �����ʐM�`�b�vCC2420�̐���}�N����`
  @author Takaaki Ishizawa, Vistarica Designs Co.Ltd.
  @date   2006/02/20
  @version 0.1
 */

#ifndef CC2420_MACRO_H
#define CC2420_MACRO_H

/*****************************************************************************
 �჌�x��SPI�ʐM�}�N��
 ****************************************************************************/

// SPI�ʐM�@�\�̏�����
// SPI���A�}�X�^�ݒ�A�{������
#define SPI_INIT()  \
    {  \
        SPCR = BM(SPE) | BM(MSTR);  \
        SPSR = BM(SPI2X);  \
    }

// SPI�ʐM�҂�
#define FASTSPI_WAIT()  \
    {  \
        while (!(SPSR & BM(SPIF)));  \
    }

// SPI���M
#define FASTSPI_TX(x)  \
    {  \
        SPDR = x;  \
        FASTSPI_WAIT();  \
    }

// SPI��M
#define FASTSPI_RX(x)  \
    {  \
        SPDR = 0;  \
        FASTSPI_WAIT();  \
        x = SPDR;  \
    }

// SPI��M�o�b�t�@�N���A
#define FASTSPI_RX_GARBAGE()  \
    {  \
        SPDR = 0;  \
        FASTSPI_WAIT();  \
    }

// SPI���[�h���M�i���g���G���f�B�A���j
#define FASTSPI_TX_WORD_LE(x)  \
    {  \
        FASTSPI_TX(x);  \
        FASTSPI_TX((x) >> 8);  \
    }
    
// SPI���[�h���M
#define FASTSPI_TX_WORD(x)  \
    {  \
        FASTSPI_TX(((WORD)(x)) >> 8);  \
        FASTSPI_TX((BYTE)(x));  \
    }
    
// SPI�o���N���M
#define FASTSPI_TX_MANY(p,c)  \
    {  \
        UINT8 spiCnt;  \
        for (spiCnt = 0; spiCnt < (c); spiCnt++) {  \
            FASTSPI_TX(((BYTE*)(p))[spiCnt]);  \
        }  \
    }
        
// SPI���[�h��M�i���g���G���f�B�A���j
#define FASTSPI_RX_WORD_LE(x)  \
    {  \
        SPDR = 0;  \
        FASTSPI_WAIT();  \
        x = SPDR;  \
        SPDR = 0;  \
        FASTSPI_WAIT();  \
        x |= SPDR << 8;  \
    }

// SPI���[�h��M
#define FASTSPI_RX_WORD(x)  \
    {  \
        SPDR = 0;  \
        FASTSPI_WAIT();  \
        x = SPDR << 8;  \
        SPDR = 0;  \
        FASTSPI_WAIT();  \
        x |= SPDR;  \
    }

// SPI�o���N��M    
#define FASTSPI_RX_MANY(p,c)  \
    {  \
        UINT8 spiCnt;  \
        for (spiCnt = 0; spiCnt < (c); spiCnt++) {  \
            FASTSPI_RX((p)[spiCnt]);  \
        }  \
    }
        
// SPI���W�X�^�������݃A�h���X�w��
#define FASTSPI_TX_ADDR(a)  \
    {  \
        SPDR = a;  \
        FASTSPI_WAIT();  \
    }

// SPI���W�X�^�ǂݏo���A�h���X�w��
#define FASTSPI_RX_ADDR(a)  \
    {  \
        SPDR = (a) | 0x40;  \
        FASTSPI_WAIT();  \
    }

/*****************************************************************************
 ���W�X�^�A�N�Z�X
 ****************************************************************************/

// SPI���W�X�^�X�g���[�u
#define FASTSPI_STROBE(s)  \
    {  \
        SPI_ENABLE();  \
        FASTSPI_TX_ADDR(s);  \
        SPI_DISABLE();  \
    }

// SPI���W�X�^��������
#define FASTSPI_SETREG(a,v)  \
    {  \
        SPI_ENABLE();  \
        FASTSPI_TX_ADDR(a);  \
        FASTSPI_TX((BYTE) ((v) >> 8));  \
        FASTSPI_TX((BYTE) (v));  \
        SPI_DISABLE();  \
    }

// SPI���W�X�^�ǂݏo��
#define FASTSPI_GETREG(a,v)  \
    {  \
        SPI_ENABLE();  \
        FASTSPI_RX_ADDR(a);  \
        FASTSPI_RX_WORD(v);  \
        SPI_DISABLE();  \
    }

// �X�e�[�^�X�o�C�g�̃A�b�v�f�[�g
#define FASTSPI_UPD_STATUS(s)  \
    {  \
        SPI_ENABLE();  \
        FASTSPI_TX_ADDR(CC2420_SNOP);  \
        s = SPDR;  \
        SPI_DISABLE();  \
    }

/*****************************************************************************
 FIFO�A�N�Z�X
 ****************************************************************************/

// FIFO�o���N��������
#define FASTSPI_WRITE_FIFO(p,c)  \
    {  \
        UINT8 spiCnt;  \
        SPI_ENABLE();  \
        FASTSPI_TX_ADDR(CC2420_TXFIFO);  \
        for (spiCnt = 0; spiCnt < (c); spiCnt++) {  \
            FASTSPI_TX(((BYTE*)(p))[spiCnt]);  \
        }  \
        SPI_DISABLE();  \
    }

// FIFO�o���N�ǂݏo��
#define FASTSPI_READ_FIFO(p,c)  \
    {  \
        UINT8 spiCnt;  \
        SPI_ENABLE();  \
        FASTSPI_RX_ADDR(CC2420_RXFIFO);  \
        for (spiCnt = 0; spiCnt < (c); spiCnt++) {  \
            while (!FIFO_IS_1);  \
            FASTSPI_RX(((BYTE*)(p))[spiCnt]);  \
        }  \
        SPI_DISABLE();  \
    }

// FIFO�ǂݏo��
#define FASTSPI_READ_FIFO_BYTE(b)  \
    {  \
        SPI_ENABLE();  \
        FASTSPI_RX_ADDR(CC2420_RXFIFO);  \
        FASTSPI_RX(b);  \
        SPI_DISABLE();  \
    }


// �u���b�N������FIFO�o���N�ǂݏo��
#define FASTSPI_READ_FIFO_NO_WAIT(p,c)  \
    {  \
        UINT8 spiCnt;  \
        SPI_ENABLE();  \
        FASTSPI_RX_ADDR(CC2420_RXFIFO);  \
        for (spiCnt = 0; spiCnt < (c); spiCnt++) {  \
            FASTSPI_RX(((BYTE*)(p))[spiCnt]);  \
        }  \
        SPI_DISABLE();  \
    }

// ��M�o�b�t�@���N���A
#define FASTSPI_READ_FIFO_GARBAGE(c)  \
    {  \
        UINT8 spiCnt;  \
        SPI_ENABLE();  \
        FASTSPI_RX_ADDR(CC2420_RXFIFO);  \
        for (spiCnt = 0; ((spiCnt < (c)) && (FIFO_IS_1)); spiCnt++) {  \
            FASTSPI_RX_GARBAGE();  \
        }  \
        SPI_DISABLE();  \
    }


/*****************************************************************************
 RAM�A�N�Z�X
 ****************************************************************************/

// RAM�������݁i���g���G���f�B�A���j
#define FASTSPI_WRITE_RAM_LE(p,a,c,n)  \
    {  \
        SPI_ENABLE();  \
        FASTSPI_TX(0x80 | (a & 0x7F));  \
        FASTSPI_TX((a >> 1) & 0xC0);  \
        for (n = 0; n < (c); n++) {  \
            FASTSPI_TX(((BYTE*)(p))[n]);  \
        }  \
        SPI_DISABLE();  \
    }

// RAM�ǂݏo���i���g���G���f�B�A���j
#define FASTSPI_READ_RAM_LE(p,a,c,n)  \
    {  \
        SPI_ENABLE();  \
        FASTSPI_TX(0x80 | (a & 0x7F));  \
        FASTSPI_TX(((a >> 1) & 0xC0) | 0x20);  \
        for (n = 0; n < (c); n++) {  \
            FASTSPI_RX(((BYTE*)(p))[n]);  \
        }  \
        SPI_DISABLE();  \
    }

// RAM�o���N��������    
#define FASTSPI_WRITE_RAM(p,a,c,n)  \
    {  \
        SPI_ENABLE();  \
        FASTSPI_TX(0x80 | (a & 0x7F));  \
        FASTSPI_TX((a >> 1) & 0xC0);  \
        n = c;  \
        do {  \
            FASTSPI_TX(((BYTE*)(p))[--n]);  \
        } while (n);  \
        SPI_DISABLE();  \
    }

// RAM�o���N�ǂݏo��
#define FASTSPI_READ_RAM(p,a,c,n)  \
    {  \
        SPI_ENABLE();  \
        FASTSPI_TX(0x80 | (a & 0x7F));  \
        FASTSPI_TX(((a >> 1) & 0xC0) | 0x20);  \
        n = c;  \
        do {  \
            FASTSPI_RX(((BYTE*)(p))[--n]);  \
        } while (n);  \
        SPI_DISABLE();  \
    }

/*****************************************************************************
 ���̑�
 ****************************************************************************/

// SPI�ʐM�̃��Z�b�g
#define FASTSPI_RESET_CC2420()  \
    {  \
        FASTSPI_SETREG(CC2420_MAIN, 0x0000);  \
        FASTSPI_SETREG(CC2420_MAIN, 0xF800);  \
    }

#endif
