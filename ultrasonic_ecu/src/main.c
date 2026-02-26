/** Ultrasonic sensor distance calculation transmit */
#include <lpc21xx.h>
#include <stdio.h>

#include "cantransmit.h"
#include "uartbaud.c"

unsigned int ultrasonic_distance(void);

#define trig (1<<10) 
#define echo (1<<11)

								  
int main()
{

unsigned int dist;
char arr[20];
 CAN2_MSG m1;
 can2_init();
 uart0_init(11520);
 
 uart0_tx_string("vishwa\r\n");


 while(1)
 { 

   dist=ultrasonic_distance();
   can_delay(1000);
    //sprintf((char*)arr, "distance=%02d", dist);   // avoid \r\n on LCD
    //uart0_tx_string((char*)arr);
    //uart0_tx_string("\r\n");
 
   m1.id=0x01;
   m1.dlc=4;
   m1.rtr=0;
   m1.byteA=dist;
   m1.byteB=0;
   can2_tx(m1);


   



 } 
}

unsigned int ultrasonic_distance(void)
{

 unsigned int count=0;
unsigned int distance=0;

IODIR0 |= trig;   //making trigger output
IODIR0 &= ~(echo);  //making echo pin input

IOCLR0=trig;
delay_us(10);
IOSET0=trig;	//sending 10 microseconds high pluse through trans pin
delay_us(10);
IOCLR0=trig;

count=0;

while (!(IOPIN0&echo));

   T1PR=60-1;
   T1TCR=0x01;
while((IOPIN0&echo));
count=T1TC;
T1TCR=0x03;
T1TCR=0x00;

distance=count/58;  //formula for convert into distance
return distance;
}
