/*can2_Transmit driver.c*/
#include <lpc21xx.h>
#define Mode_3     0x18  // CPOL 1 CPHA 1

#define MSTR_BIT   5     // SPI0 as Master 
#define SPIF_BIT   7 

typedef unsigned int u32;
void can2_init(void);
void Init_SPI0(void);
 unsigned int Read_ADC_MCP3204(unsigned char);
unsigned char SPI0(unsigned char);

typedef struct CAN2
  {
  	u32 id;
	u32 rtr;
	u32 dlc;
	u32 byteA;
	u32 byteB;
  }CAN2_MSG;

void can2_tx(CAN2_MSG);

void can2_init(void)
 {
	PINSEL1|=0x00014000;//P0.23-->RD2 & P0.24-->TD2
	VPBDIV=1; //PCLK=60MHz
    C2MOD=0x1; //CAN2 into Reset  Mode 
	C2BTR=0x001C001D; //B125Kbps @ PLCK=60MHz	
	AFMR=0x2;//Enable Acceptance Filter
    C2MOD=0x0; //CAN2 into Normal Mode
 }
void can2_tx(CAN2_MSG m1)
{
  C2TID1=m1.id;
  C2TFI1=(m1.dlc<<16);	
	if(m1.rtr==0) //if data frame
	{
	C2TFI1&=~(1<<30);//RTR=0
	C2TDA1=m1.byteA; //lower 4bytes of data
	C2TDB1=m1.byteB; //upper 4bytes of data
	}
	else
	{
	C2TFI1|=(1<<30); //RTR=1
	}
	C2CMR=(1<<0)|(1<<5);//Start Xmission & select Tx Buf1
	while((C2GSR&(1<<3))==0);//wait for data Xmission.
}

void Init_SPI0(void)					
{	
PINSEL0 |=0X00001500;
S0SPCCR  = 150;
S0SPCR  = (1<<MSTR_BIT|Mode_3); //spi module in master mode,//CPOL =1,CCPHA = 1. MSB firs              
IODIR0 |= (1<<7);//direction
}
unsigned int Read_ADC_MCP3204(unsigned char channelNo)
{
  unsigned char hByte,lByte;
  unsigned int adcVal=0;  
  IOCLR0|=(1<<7);	
  SPI0(0x06);
  hByte = SPI0(channelNo<<6);
  lByte = SPI0(0x00);	
  IOSET0|=(1<<7);
  adcVal=((hByte&0x0f)<<8)|lByte;
 return adcVal;
}

unsigned char SPI0(unsigned char data)
{
   unsigned char stat;
   stat = S0SPSR;    //clear SPIF 
   S0SPDR = data;   // load spi tx reg
   while(((S0SPSR>>SPIF_BIT)&1)==0); // wait for transmission to complete
   return S0SPDR;    // read data from SPI data reg, place into buffer
} 	
