
#include <lpc21xx.h>
#include <stdio.h>

#include "cantransmit.h"
#include "lcd.h"
//#include "uartbaud.c"

void float_display(float f);

 int main()
{
    //CAN2_MSG m1;
    unsigned char arr[20];
    int f;
	int speed,adc;
  //uart0_init(115200);
   Init_SPI0();
   //can2_init();
   lcd_init();
  // uart0_init(115200);
    


	IOPIN0|= (1<<7);
    
   //IOCLR0= (1<<7);
    //IOSET0= (1 << 7);    // CS high (inactive)
  

    //uart0_tx_string("nodeB TESTING CAN\r\n");
          
//lcd_cmd(0x80);          
//lcd_string("Speed:");


lcd_cmd(0x01);   // clear once

while(1)
{
    adc = Read_ADC_MCP3204(1);      // raw 0–4095
    speed = (adc * 100) / 4095;     // convert to 0–100

    lcd_cmd(0x80);                  // first line

    sprintf((char*)arr, "Speed:%3d Kmph ", speed);
    lcd_string((char*)arr);

    delay_ms(200);
}             // small refresh delay
}

/*		//lcd_cmd(0x88);
		//lcd_string("Kmph");


        /*m1.id   = 0x02;
        m1.dlc  = 1;
        m1.rtr  = 0;
        m1.byteA = (unsigned char)f;  */

       //can2_tx(m1);
       
																																													   /**/
