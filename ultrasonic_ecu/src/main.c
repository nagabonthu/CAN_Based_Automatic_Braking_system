/** Ultrasonic sensor distance calculation and CAN transmit to dashboard ECU */
#include <lpc21xx.h>
#include <stdio.h>
#include "cantransmit.h" // CAN transmit header

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
   delay_can(1000);               // Delay of 1000ms between transmissions
   m1.id=0x01;   //Messgae ID
   m1.dlc=4;     // data length code
   m1.rtr=0;     // data frame
   m1.byteA=dist;//measured distance storing in byteA
   m1.byteB=0;
   can2_tx(m1); // transmit CAN message

 } 
}
/** Function to measure distance using ultrasonic sensor **/
unsigned int ultrasonic_reading(void)
{
 unsigned int count=0;  
 unsigned int dist=0;   

 IODIR0 |= trig;    // trigger pin as output
 IODIR0 &= ~(echo); // echo pin as input

 IOCLR0=trig;  // Clear trigger pin 
 delay_us(10); 
 IOSET0=trig;// Set trigger pin high
 delay_us(10); // Keep high for 10 microseconds
 IOCLR0=trig; // Clear trigger pin
 
 while (!(IOPIN0&echo)); // Wait until echo pin goes high
   T1PR=60-1;   // Prescaler for 1µs (PCLK=60MHz)
   T1TCR=0x01; // Enable Timer1
 while((IOPIN0&echo)); // Wait until echo pin goes low
	
 count=T1TC; // Capturing the timer count
 T1TCR=0x03; // Stop and resetting Timer1
 T1TCR=0x00;// Clear Timer1
 dist=count/58;  //formula: distance(cm)= time/58;
 return dist; // Returning measured distance
}
