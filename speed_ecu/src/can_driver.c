/** cn transmit****/
/*can2_driver.c*/
typedef unsigned int u32;
void can2_init(void);
void delay_millisec(unsigned int);
typedef struct CAN2
  {
	u32 id;
	u32 rtr;
	u32 dlc;
	u32 byteA;
	u32 byteB;
 }CAN2_MSG;
void can2_tx(CAN2_MSG m1);
void can2_rx(CAN2_MSG*);
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
void can2_rx(CAN2_MSG* m1)
  {
    while((C2GSR&0x1)==0);//waiting untill message received
    m1->id=C2RID;
	m1->dlc=(C2RFS>>16)&0xF;
	m1->rtr=(C2RFS>>30)&0x1;
	if(m1->rtr==0){ //if data frame
		m1->byteA=C2RDA;
		m1->byteB=C2RDB;
	}
   C2CMR=(1<<2);//free receiver buffer(imp)
   }

   void delay_millisec(unsigned int ms)
{
    T0PR=60000-1;//microsecs
	T0TCR=0x01;
	while(T0TC<ms);
	T0TCR=0x03;
	T0TCR=0x00;
}

   	/*if(m1.id==0x02)
			{ 
				uart0_tx_string("speed check\r\n");
			speed=m1.byteA;
		sprintf((char*)arr, "speed=%02d", speed);   // avoid \r\n on LCD
        uart0_tx_string((char*)arr);
        uart0_tx_string("\r\n");
		//delay_millisec(3000);
		//uart0_tx_string("speed check\r\n");
		   
			}*/
