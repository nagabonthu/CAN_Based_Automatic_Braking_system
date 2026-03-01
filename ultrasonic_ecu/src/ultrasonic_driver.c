
unsigned int ultrasonic_reading(void);
void delay_millisec(unsigned int ms);
void delay_us(unsigned int us);

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

// Function to generate millisecond delay using Timer0
void delay_millisec(unsigned int ms)
{
    T0PR  = 60000 - 1;   // Prescaler for 1 ms tick (assuming 60 MHz clock)
    T0TCR = 0x01;        // Enable Timer0
    while(T0TC < ms);    // Wait until Timer0 reaches desired count
    T0TCR = 0x03;        // Stop and reset Timer0
    T0TCR = 0x00;        // Clear Timer0
}

// Function to generate microsecs delay using Timer0
void delay_us(unsigned int us)
{
    T0PR  = 60 - 1;   // Prescaler for 1 us(assuming 60 MHz clock)
    T0TCR = 0x01;        // Enable Timer0
    while(T0TC < us);    // Wait until Timer0 reaches desired count
    T0TCR = 0x03;        // Stop and reset Timer0
    T0TCR = 0x00;        // Clear Timer0
}
