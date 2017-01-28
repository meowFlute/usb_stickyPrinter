// file: main.c
// author: Scott Christensen
//
// version history
// 1/28/2017 - set up basic LED blinking file

#include <msp430.h>				

int main(void) {
	WDTCTL = WDTPW | WDTHOLD;		// Stop watchdog timer

	// I/0 functionality on all pins
	P1SEL  = 0x00;					// Set P1.0-P1.7 to I/O functionality
	P1SEL2 = 0x00;
	P2SEL  = 0x00;					// Set P1.0-P1.7 to I/O functionality
	P2SEL2 = 0x00;

	// set all pins to the output direction by default (less power consumption so long as they aren't connected to anything)
	P1DIR = 0xff;					// Set P1.0-P1.7 to output direction
	P2DIR = 0xff;					// Set P2.0-P2.7 to output direction

	P1OUT = BIT6; 					// Turn on only the green LED on P1.6

	for(;;) {
		volatile unsigned int i;	// volatile to prevent optimization
		volatile unsigned int j;	// volatile to prevent optimization

		P1OUT ^= BIT0;				// Toggle P1.0 using exclusive-OR


		i = 5;						// SW Delay

		do
		{
			P1OUT ^= BIT6;			// Toggle P1.6 using exclusive-OR
			i--;
			j = 20000;				// Scale the delay
			do
			{
				j--;
			}
			while (j != 0);
		}
		while(i != 0);
	}
	
	return 0;
}
