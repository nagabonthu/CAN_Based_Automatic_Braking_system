 
/**  Sends speed to Dashboard ECU over CAN **/ 

#include <lpc21xx.h>

#include "can_driver.c"      
#include "spi_driver.c"         

int main()
{
    int adc, speed;

    CAN2_MSG m1;

    /* Init peripherals */
    Init_SPI0();     // SPI0 for MCP3204
    can2_init();     // CAN2 init (125 kbps)


    while (1)
    {
        
        adc = Read_ADC_MCP3204(1);//Read raw ADC (0–4095) 
 
        speed = (adc*100) / 4095;// Convert ADC to speed range 0–100 

        /* Send speed via CAN */
        m1.id = 0x02;       // Speed message ID
        m1.rtr = 0;          // Data frame
        m1.dlc = 1;          // 1 byte data
        m1.byteA = (unsigned char)speed;  // speed in byte0
        m1.byteB = 0;        
        can2_tx(m1);

        delay_millisec(200);  // small  delay
    }
}
																																													   /**/
