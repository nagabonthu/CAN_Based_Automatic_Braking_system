

/*** main unit****/
void uart0_init(unsigned int baud);
void uart0_tx(unsigned char data);
unsigned char uart0_rx(void);
void uart0_tx_hex(int num);


void uart0_init(unsigned int baud){

	PINSEL0|=0x5;

	U0LCR=0x83;

	switch(baud){	

		case 115200:U0DLL=32;	break;//PCLK=60MHz

		case 921600:U0DLL=4;	break;
		case 9600:U0DLL=97;    break;

		default:	U0DLL=32	;	

	}

	U0LCR=0x03;

}


void uart0_tx(unsigned char data){

	U0THR=data;

	while((U0LSR&(1<<5))==0);

}


unsigned char uart0_rx(void){

	while((U0LSR&0x1)==0);

	return U0RBR;

}




void uart0_tx_string(char *ptr){

	while(*ptr!=0){

		U0THR=*ptr;

		while((U0LSR&(1<<5))==0);

		ptr++;

	}

}

void uart0_tx_hex(int num){

	char buf[10];

	sprintf(buf,"%X",num);

	uart0_tx_string(buf);

}
