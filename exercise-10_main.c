// Title: Lab 10 - Multifunction Flashlight
// Developer: Muhfasul Alam
// Date: November 18, 2021
// Description: A multifunction flashlight that works as listed below:
//      1st button push: the LEDs turn yellow
//      2nd button push: the LEDs turn red
//      3rd button push: the LEDs flash on and off (red)
//      4th button push: the LEDs turn off

#include <msp430.h> 
#include <stdint.h>
#include <stdbool.h>

int main(void)
{
	uint8_t ButtonCount = 0;  // for tracking button push
	volatile uint16_t i;      // to be used with loop for counting iteration
	bool ButtonPressed;       // for checking if the button was pressed
	
	WDTCTL = WDTPW+WDTHOLD;   // Stop WDT
    PM5CTL0 &= ~LOCKLPM5;     // Always included in program
    
    P1DIR = 0b11111100;       // Configuring output pins
    P2DIR = 0b11111110;       // Configuring input pins
    
    P1OUT = 0b00000000;       // Turning off all the LEDs
    
    while (1){                // Endless loop
    
        ButtonPressed = ((P2IN & 0b00000001) == 0); // Button has not been pressed
        
        if (ButtonPressed) {                        // Check if button is pressed
            ButtonCount += 1;                       // If so, increase ButtonCount
            
            if (ButtonCount == 4) {                 // If the button is pressed 4 times
                P1OUT = 0b00000000;                 // Turn off all the LEDs
                ButtonCount = 0;                    // Set ButtonCount to 0
            }
            while (((P2IN & 0b00000001) == 0));     // Wait until button is released
        }
        
        if (ButtonCount == 1) {             // When Button is pressed once
            P1OUT = 0b01000100;             // Turn on yellow LEDs
            
        } else if (ButtonCount == 2) {      // When button is pressed twice
            P1OUT = 0b10100000;             // Turn on red LEDs
            
        } else if (ButtonCount == 3) {      // When button is pressed thrice
            P1OUT ^= 0b10100000;            // Toggle red LEDs
            for (i = 5000; i > 0; i--);     // Empty loop for delay
        }
    }
    
    return;
}

