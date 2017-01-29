// file: main.c
// author: Scott Christensen
//
// version history
// 1/28/2017 - set up basic LED blinking file

#include <msp430.h>				

volatile int milleseconds;

int main(void) {
	// Set watchdog to timer mode with 8ms/1_MHz_DCO period interrupts
	WDTCTL = WDT_MDLY_8;
	// enable the watchdog interrupt timer
	IE1 = WDTIE;

	//set the half millisecond counter to zero
	milleseconds = 0;

	//Change DCO frequency to 16 MHz
	BCSCTL1 = CALBC1_16MHZ;
	DCOCTL  = CALDCO_16MHZ;

	//set both masterclock AND sub master clock sources to DCO
	//make the masterclock oscilate at a period of DCO/1 and the SMCLK at DCO/2
	BCSCTL2 = DIVS_1;

	// I/0 functionality on all pins
	P1SEL  = 0x00;					// Set P1.0-P1.7 to I/O functionality
	P1SEL2 = 0x00;
	P2SEL  = 0x00;					// Set P1.0-P1.7 to I/O functionality
	P2SEL2 = 0x00;

	// set all pins to the output direction by default (less power consumption so long as they aren't connected to anything)
	P1DIR = 0xff;					// Set P1.0-P1.7 to output direction
	P2DIR = 0xff;					// Set P2.0-P2.7 to output direction

	P1OUT = 0x00;

	//enable interrupts (they won't run unless you do this)
	_EINT();

	for(;;) {
		//infinite loop
	}
	
	return 0;
}

#pragma vector=WDT_VECTOR
__interrupt void WatchDog_Timer(void)
{
	// real time is about 1.0252777777777777777777777777778 times faster than my time
	// the data sheet documents the lack of precision on the internal oscillator so no surprises here, 2.5% is pretty good

	//another half millisecond has passed
	milleseconds++;

	//just blink
	if(milleseconds == 950)
		P1OUT ^= BIT6;
	if(milleseconds == 1000)
		P1OUT ^= BIT6;

	//a full second has passed
	if(milleseconds == 1000)
	{
		P1OUT ^= BIT0;
		milleseconds = 0;
	}

	//clear the interrupt flag on the way out
	IFG1 &= ~WDTIFG;
}
