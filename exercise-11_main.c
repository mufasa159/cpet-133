#include <msp430.h>
#include <stdint.h>
#include <stdbool.h>

int main(void)
{
    
    enum traffic_states {MHOLD, MGSR, MYSR, MRSR1, MRSG, MRSY, MRSR2} state, prevState;
    
	volatile uint32_t i;            // iteration counter for delay loop
    volatile bool isCar;            // boolean variable for checking if there is a car 
    volatile bool isNewState;       // boolean variable for checking if it's a new state     
    volatile uint8_t stateTimer;    // declaring state timer
    uint8_t statetimer = 0;         // initializing state timer
    
	WDTCTL = WDTPW | WDTHOLD;       // stop WDT
    PM5CTL0 &= ~LOCKLPM5;           // always included in program
    
    P1DIR |= 0b11111100;            // configuring output pins
    P2DIR &= 0b11111101;            // configuring input pins
    
    P1OUT = 0b00101000;             // turn on Main Green and Side Red
    
    state = MGSR;                   // start in hold state
    prevState = !MGSR;              // for checking if state has changed
    
    
    while(1) {
        
        isCar = ((P2IN & 0b00000010) == 0); // check if car is present
        isNewState = (state != prevState);  // check if its a new state
        prevState = state;                  // save the current state as prevState
        
        switch(state) {                     // switch on the current state
        
            case MGSR:
                P1OUT = 0b00101000;         // turn on Main Green and Side Red
                if (isCar) {                // change states if there is a car
                    state = MYSR;
                }
            break;
            
            case MYSR:
                if (isNewState) {           // if it's a new state
                    stateTimer = 0;         // then reset state timer
                }
                P1OUT = 0b00100100;         // turn on Main Yellow and Side Red
                stateTimer++;               // increment timer value
                if (stateTimer == 5) {      // if 5 seconds has passed
                    state = MRSR1;          // then change to next state
                }
            break;
            
            case MRSR1:
                if (isNewState) {           // if it's a new state
                    stateTimer = 0;         // then reset state timer
                }
                P1OUT = 0b10100000;         // turn on Main Red and Side Red
                stateTimer++;               // increment timer value
                if (stateTimer == 5) {      // if 5 seconds has passed
                    state = MRSG;           // then change to next state
                }
            break; 
            
            case MRSG:
                if (isNewState) {           // if it's a new state
                    stateTimer = 0;         // then reset state timer
                }
                P1OUT = 0b10010000;         // turn on Main Red and Side Green
                stateTimer++;               // increment timer value
                if (stateTimer == 40) {     // if 40 seconds has passed
                    state = MRSY;           // then change to next state
                }
            break;
            
            case MRSY:
                if (isNewState) {           // if it's a new state
                    stateTimer = 0;         // then reset state timer
                }
                P1OUT = 0b11000000;         // turn on Main Red and Side Yellow
                stateTimer++;               // increment timer value
                if (stateTimer == 5) {      // if 5 seconds has passed
                    state = MRSR2;          // then change to next state
                }
            break;
            
            case MRSR2:
                if (isNewState) {           // if it's a new state
                    stateTimer = 0;         // then reset state timer
                }
                P1OUT = 0b10100000;         // turn on Main Red and Side Red
                stateTimer++;               // increment timer value
                if (stateTimer == 5) {      // if 5 seconds has passed
                    state = MHOLD;          // then change to next state
                }
            break;
            
            case MHOLD:
                if (isNewState) {           // if it's a new state
                    stateTimer = 0;         // then reset state timer
                }
                P1OUT = 0b00101000;         // turn on Main Green and Side Red
                stateTimer++;               // increment timer value
                if (stateTimer == 40) {     // if 40 seconds has passed
                    state = MGSR;           // then change to next state
                }
            break;
        }
        
        for (i = 47500; i > 0; i--);        // one second delay
    }
	
}

