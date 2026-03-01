/** Ultrasonic sensor distance calculation and CAN transmit to dashboard ECU */
#include <lpc21xx.h>
#include <stdio.h>
#include "cantransmit.h" // CAN transmit header
#include "ultrasonic_driver.c"

unsigned int ultrasonic_reading(void);//function declartion

//trigger and echo pins
#define trig (1<<10) 
#define echo (1<<11)
								  
int main()
{
unsigned int dist;
CAN2_MSG m1;      // CAN message structure
	
can2_init();     // Initializing CAN controller	
 while(1)
 { 
   distance=ultrasonic_reading();  // function call to read distance from ultrasonic sensor 
   delay_millisec(1000);               // Delay of 1000ms between transmissions
   m1.id=0x01;   //Messgae ID
   m1.dlc=4;     // data length code
   m1.rtr=0;     // data frame
   m1.byteA=dist;//measured distance storing in byteA
   m1.byteB=0;
   can2_tx(m1); // transmit CAN message

 } 
}

