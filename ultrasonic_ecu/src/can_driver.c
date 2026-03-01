/** CAN2 Transmit Driver Implementation **/
/* can2_driver.c */

typedef unsigned int u32;   // typedef for 32-bit unsigned type 

// Function prototypes
void can2_init(void);
void delay_millisec(unsigned int);

// CAN2 message structure
typedef struct CAN2
{
    u32 id;      // Message ID
    u32 rtr;     // Remote Transmission Request (0 = data frame, 1 = remote frame)
    u32 dlc;     // Data Length Code (number of bytes in message)
    u32 byteA;   // First data word (lower 4 bytes)
    u32 byteB;   // Second data word (upper 4 bytes)
} CAN2_MSG;

// Function to initialize CAN2 controller
void can2_init(void)
{
    PINSEL1 |= 0x00014000;   // Configure P0.23 as RD2 (receive), P0.24 as TD2 (transmit)
    VPBDIV = 1;              // Set PCLK = 60 MHz
    C2MOD = 0x1;             // Reset Mode
    C2BTR = 0x001C001D;      // speed: 125 kbps @ 60 MHz PCLK
    AFMR  = 0x2;             // Enable Acceptance Filter 
    C2MOD = 0x0;             // CAN2 into Normal Mode (ready for communication)
}

// Function to transmit a CAN2 message
void can2_tx(CAN2_MSG m1)
{
    C2TID1 = m1.id;          // Load message ID to transmit buffer
    C2TFI1 = (m1.dlc << 16); // Set Data Length Code (DLC) in transmit frame info

    if(m1.rtr == 0)          // If it is  data frame
    {
        C2TFI1 &= ~(1 << 30); // Clear RTR bit (RTR = 0)
        C2TDA1  = m1.byteA;   // Load lower 4 bytes of data
        C2TDB1  = m1.byteB;   // Load upper 4 bytes of data
    }
    else                     // If it is  remote frame
    {
        C2TFI1 |= (1 << 30);  // Set RTR bit (RTR = 1)
    }

    C2CMR = (1 << 0) | (1 << 5); // start transmission using Tx Buffer1

    while((C2GSR & (1 << 3)) == 0); // Wait until transmission is complete
}

