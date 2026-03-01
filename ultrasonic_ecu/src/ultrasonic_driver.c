// Function to generate millisecond delay using Timer0
void delay_millisec(unsigned int ms)
{
    T0PR  = 60000 - 1;   // Prescaler for 1 ms tick (assuming 60 MHz clock)
    T0TCR = 0x01;        // Enable Timer0
    while(T0TC < ms);    // Wait until Timer0 reaches desired count
    T0TCR = 0x03;        // Stop and reset Timer0
    T0TCR = 0x00;        // Clear Timer0
}
