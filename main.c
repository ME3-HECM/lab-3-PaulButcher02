// CONFIG1L
#pragma config FEXTOSC = HS     // External Oscillator mode Selection bits (HS (crystal oscillator) above 8 MHz; PFM set to high power)
#pragma config RSTOSC = EXTOSC_4PLL// Power-up default value for COSC bits (EXTOSC with 4x PLL, with EXTOSC operating per FEXTOSC bits)

// CONFIG3L
#pragma config WDTE = OFF        // WDT operating mode (WDT enabled regardless of sleep)

#include <xc.h>
#include "LEDarray.h"
#include "interrupts.h"
#include "comparator.h"

#define _XTAL_FREQ 64000000 //note intrinsic _delay function is 62.5ns at 64,000,000Hz  


void main(void) {
	//call your initialisation functions to set up the hardware modules
    DAC_init();
    Comp1_init();
    Interrupts_init();
        
    while (1) {
		
        if (triggered==1){ //if interrupt occurred, other LED turns on (experimenting with global variables)
            __delay_ms(50);
            LATDbits.LATD7=1;
            triggered=0;
        }
        Sleep(); 
        LATDbits.LATD7=0; //This code proves that the processor has gone to sleep since the LED doesn't turn off
        __delay_ms(100)
    }
}