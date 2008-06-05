/*!
  @file
  @brief 無線通信チップCC2420の制御マクロ定義
  @author Takaaki Ishizawa, Vistarica Designs Co.Ltd.
  @date   2006/02/20
  @version 0.1
 */

#ifndef CC2420_MACRO_H
#define CC2420_MACRO_H

/*****************************************************************************
 低レベルSPI通信マクロ
 ****************************************************************************/

// SPI通信機能の初期化
// SPI許可、マスタ設定、倍速許可
#define SPI_INIT()  \
    {  \
        SPCR = BM(SPE) | BM(MSTR);  \
        SPSR = BM(SPI2X);  \
    }

// SPI通信待ち
#define FASTSPI_WAIT()  \
    {  \
        while (!(SPSR & BM(SPIF)));  \
    }

// SPI送信
#define FASTSPI_TX(x)  \
    {  \
        SPDR = x;  \
        FASTSPI_WAIT();  \
    }

// SPI受信
#define FASTSPI_RX(x)  \
    {  \
        SPDR = 0;  \
        FASTSPI_WAIT();  \
        x = SPDR;  \
    }

// SPI受信バッファクリア
#define FASTSPI_RX_GARBAGE()  \
    {  \
        SPDR = 0;  \
        FASTSPI_WAIT();  \
    }

// SPIワード送信（リトルエンディアン）
#define FASTSPI_TX_WORD_LE(x)  \
    {  \
        FASTSPI_TX(x);  \
        FASTSPI_TX((x) >> 8);  \
    }
    
// SPIワード送信
#define FASTSPI_TX_WORD(x)  \
    {  \
        FASTSPI_TX(((WORD)(x)) >> 8);  \
        FASTSPI_TX((BYTE)(x));  \
    }
    
// SPIバルク送信
#define FASTSPI_TX_MANY(p,c)  \
    {  \
        UINT8 spiCnt;  \
        for (spiCnt = 0; spiCnt < (c); spiCnt++) {  \
            FASTSPI_TX(((BYTE*)(p))[spiCnt]);  \
        }  \
    }
        
// SPIワード受信（リトルエンディアン）
#define FASTSPI_RX_WORD_LE(x)  \
    {  \
        SPDR = 0;  \
        FASTSPI_WAIT();  \
        x = SPDR;  \
        SPDR = 0;  \
        FASTSPI_WAIT();  \
        x |= SPDR << 8;  \
    }

// SPIワード受信
#define FASTSPI_RX_WORD(x)  \
    {  \
        SPDR = 0;  \
        FASTSPI_WAIT();  \
        x = SPDR << 8;  \
        SPDR = 0;  \
        FASTSPI_WAIT();  \
        x |= SPDR;  \
    }

// SPIバルク受信    
#define FASTSPI_RX_MANY(p,c)  \
    {  \
        UINT8 spiCnt;  \
        for (spiCnt = 0; spiCnt < (c); spiCnt++) {  \
            FASTSPI_RX((p)[spiCnt]);  \
        }  \
    }
        
// SPIレジスタ書き込みアドレス指定
#define FASTSPI_TX_ADDR(a)  \
    {  \
        SPDR = a;  \
        FASTSPI_WAIT();  \
    }

// SPIレジスタ読み出しアドレス指定
#define FASTSPI_RX_ADDR(a)  \
    {  \
        SPDR = (a) | 0x40;  \
        FASTSPI_WAIT();  \
    }

/*****************************************************************************
 レジスタアクセス
 ****************************************************************************/

// SPIレジスタストローブ
#define FASTSPI_STROBE(s)  \
    {  \
        SPI_ENABLE();  \
        FASTSPI_TX_ADDR(s);  \
        SPI_DISABLE();  \
    }

// SPIレジスタ書き込み
#define FASTSPI_SETREG(a,v)  \
    {  \
        SPI_ENABLE();  \
        FASTSPI_TX_ADDR(a);  \
        FASTSPI_TX((BYTE) ((v) >> 8));  \
        FASTSPI_TX((BYTE) (v));  \
        SPI_DISABLE();  \
    }

// SPIレジスタ読み出し
#define FASTSPI_GETREG(a,v)  \
    {  \
        SPI_ENABLE();  \
        FASTSPI_RX_ADDR(a);  \
        FASTSPI_RX_WORD(v);  \
        SPI_DISABLE();  \
    }

// ステータスバイトのアップデート
#define FASTSPI_UPD_STATUS(s)  \
    {  \
        SPI_ENABLE();  \
        FASTSPI_TX_ADDR(CC2420_SNOP);  \
        s = SPDR;  \
        SPI_DISABLE();  \
    }

/*****************************************************************************
 FIFOアクセス
 ****************************************************************************/

// FIFOバルク書き込み
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

// FIFOバルク読み出し
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

// FIFO読み出し
#define FASTSPI_READ_FIFO_BYTE(b)  \
    {  \
        SPI_ENABLE();  \
        FASTSPI_RX_ADDR(CC2420_RXFIFO);  \
        FASTSPI_RX(b);  \
        SPI_DISABLE();  \
    }


// ブロック無しのFIFOバルク読み出し
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

// 受信バッファをクリア
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
 RAMアクセス
 ****************************************************************************/

// RAM書き込み（リトルエンディアン）
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

// RAM読み出し（リトルエンディアン）
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

// RAMバルク書き込み    
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

// RAMバルク読み出し
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
 その他
 ****************************************************************************/

// SPI通信のリセット
#define FASTSPI_RESET_CC2420()  \
    {  \
        FASTSPI_SETREG(CC2420_MAIN, 0x0000);  \
        FASTSPI_SETREG(CC2420_MAIN, 0xF800);  \
    }

#endif
