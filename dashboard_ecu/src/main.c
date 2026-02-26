/** DashBoard ECu, Receive distance and speed- display it on LCD, 
calculated the collision RISk and apply the breaks in another ECU with the help of DC motor**/  
#include <lpc21xx.h>
#include<stdio.h>
#include "candriver.c"
#include "uartbaud.c"
#define led1 1<<4  //red zone 
#define led2 1<<7  //green zone

#define pin1  (1<<8)
#define pin2 (1<<9)
#define BRAKE_DIST  10

//#define warn     30   // warning when <= 30 cm
//#define break   10   // brake when <= 10 cm

//static void motor_run(void){ IOSET0 = MOTOR_PIN; }
//static void motor_stop(void){ IOCLR0 = MOTOR_PIN; }

// #include "lcd.h"
int main()
{  
   char arr[20];


   int distance=0;
   	CAN2_MSG m1;     // in cm ]

 IODIR0 |= (pin1)|(pin2);;
 IODIR0|=led1|led2;
 IOSET0|=led1|led2;
    //lcd_init();
	can2_init(); 
	uart0_init(115200);
//	uart0_tx_string("check\r\n");

IOSET0 = pin1;
IOCLR0=pin2;
	
	 while(1)
    {
        can2_rx(&m1);

        if(m1.rtr == 0 && m1.id == 0x01)
        {
            distance = m1.byteA;

            if(distance <= BRAKE_DIST)
            {

			    IOCLR0 = led1;//red zone
				IOSET0 = led2; 	 

                IOCLR0 = pin1;   // STOP motor


                sprintf(arr, "Distance=%d cm -> danger", distance);
				
            }

            else
            {
                //IOSET0 = MOTOR_PIN;   // RUN motor
				IOCLR0 = led2;	 //green safe 
				IOSET0=led1;


				IOSET0 = pin1;	 //green safe 
	
                sprintf(arr, "Distance=%d cm -> safe", distance);
            }
			
            uart0_tx_string(arr);
            uart0_tx_string("\r\n");
        }

    }
}
