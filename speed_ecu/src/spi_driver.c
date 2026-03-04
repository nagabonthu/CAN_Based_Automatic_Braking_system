/***SPI communication with the MCP3204
ADC using the LPC2129 ARM7 microcontroller ***/
#include <lpc21xx.h>

#define Mode_3     0x18   // SPI mode 3 (CPOL=1, CPHA=1)
#define MSTR_BIT   5      // SPI master mode bit
#define SPIF_BIT   7      // SPI transfer complete flag

/* Function prototypes */
void Init_SPI0(void);
unsigned int Read_ADC_MCP3204(unsigned char channelNo);
unsigned char SPI0(unsigned char data);


/* Initialize SPI0 as master */
void Init_SPI0(void)
{
    PINSEL0 |= 0x00001500;     // Select SPI0 pins (P0.4, P0.5, P0.6)
    S0SPCCR  = 150;            // SPI clock 
    S0SPCR   = (1<<MSTR_BIT) | Mode_3;   // Master mode, SPI mode 3
    IODIR0  |= (1<<7);         // P0.7 as chip select (CS)
}


/* Read analog value from MCP3204 ADC */
unsigned int Read_ADC_MCP3204(unsigned char channelNo)
{
    unsigned char hByte, lByte;
    unsigned int adcVal = 0;

    IOCLR0 |= (1<<7);          // CS low (start communication)

    SPI0(0x06);                // Start bit + single-ended mode
    hByte = SPI0(channelNo<<6);// Send channel number
    lByte = SPI0(0x00);        // Read lower byte

    IOSET0 |= (1<<7);          // CS high (end communication)

    adcVal = ((hByte & 0x0F)<<8) | lByte;  // Combine to 12-bit value

    return adcVal;
}

/* Send and receive one byte through SPI */
unsigned char SPI0(unsigned char data)
{
    unsigned char stat;

    stat = S0SPSR;             // Clear previous SPI flag
    S0SPDR = data;             // Load data to transmit

    while(((S0SPSR>>SPIF_BIT)&1)==0);  // Wait for transfer complete

    return S0SPDR;             // Return received byte
}
