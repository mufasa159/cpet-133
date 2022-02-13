#include <msp430.h>

int main(void) {
    volatile unsigned int i;
    
    WDTCTL = WDTPW+WDTHOLD;     // Stop WDT
    PM5CTL0 &= ~LOCKLPM5;       // Always include these two lines
    
    P1DIR = 0b00000010;         // P1.0 (port 1, bit 0) set as output
    P1OUT = 0b00000010;         // P1.0 (port 1, bit 0) set to 1
    
    while(1) {                  // continuous loop
        P1OUT ^= 0b00000010;    // XOR P1.0 with 1 to invert it
        for(i=5;i>0;i--);   // Delay (do nothing for 50000 clock cycles)
    }
}
 

