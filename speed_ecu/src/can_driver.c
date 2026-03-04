/* can2_driver.c
   Simple CAN2 driver (init, transmit, receive) + Timer0 delay */

#include <lpc21xx.h>

typedef unsigned int u32;

/* CAN message structure */
typedef struct
{
    u32 id;      // CAN Identifier
    u32 rtr;     // 0 = Data frame, 1 = Remote frame
    u32 dlc;     // Data length (0 to 8)
    u32 byteA;   // Data bytes 0-3
    u32 byteB;   // Data bytes 4-7
} CAN2_MSG;

/* Function prototypes */
void can2_init(void);
void can2_tx(CAN2_MSG m1);
void can2_rx(CAN2_MSG *m1);
void delay_millisec(unsigned int ms);

/* Initialize CAN2 (125 kbps @ PCLK = 60 MHz) */
void can2_init(void)
{
    PINSEL1 |= 0x00014000;   // P0.23 = RD2, P0.24 = TD2 (CAN2 pins)
    VPBDIV   = 1;            // PCLK = CCLK (assumed 60 MHz)

    C2MOD = 0x01;            // Reset mode 
    C2BTR = 0x001C001D;      // Bit timing for 125 kbps @ 60 MHz PCLK
    AFMR  = 0x02;            // Acceptance filter bypass (accept all)
    C2MOD = 0x00;            // Normal mode (start CAN)
}

/* Transmit one CAN frame using TX Buffer 1 */
void can2_tx(CAN2_MSG m1)
{
    C2TID1 = m1.id;          // Load CAN ID
    C2TFI1 = (m1.dlc << 16); // Set DLC in frame info

    if (m1.rtr == 0)         // Data frame
    {
        C2TFI1 &= ~(1 << 30); // RTR = 0
        C2TDA1  = m1.byteA;   // Data bytes 0-3
        C2TDB1  = m1.byteB;   // Data bytes 4-7
    }
    else                     // Remote frame
    {
        C2TFI1 |= (1 << 30);  // RTR = 1
    }

    C2CMR = (1 << 0) | (1 << 5);     // Start TX + select TX buffer 1
    while ((C2GSR & (1 << 3)) == 0); // Wait until transmission completes
}

/* Receive one CAN frame (polling) */
void can2_rx(CAN2_MSG *m1)
{
    while ((C2GSR & 0x01) == 0);     // Wait until receive buffer has data

    m1->id  = C2RID;                 // Read received ID
    m1->dlc = (C2RFS >> 16) & 0x0F;  // Extract DLC
    m1->rtr = (C2RFS >> 30) & 0x01;  // Extract RTR

    if (m1->rtr == 0)                // If data frame, read payload
    {
        m1->byteA = C2RDA;           // Data bytes 0..3
        m1->byteB = C2RDB;           // Data bytes 4..7
    }

    C2CMR = (1 << 2);                // Release receive buffer (important)
}

/*  millisecond delay using Timer0 */
void delay_millisec(unsigned int ms)
{
    T0PR  = 60000 - 1;   // Prescaler 
    T0TCR = 0x01;        // Start timer
    while (T0TC < ms);   // Wait
    T0TCR = 0x03;        // Reset timer
    T0TCR = 0x00;        // Stop timer
}


