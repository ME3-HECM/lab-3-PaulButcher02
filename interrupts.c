#include <xc.h>
#include "interrupts.h"
/************************************
 * Function to turn on interrupts and set if priority is used
 * Note you also need to enable peripheral interrupts in the INTCON register to use CM1IE.
************************************/
void Interrupts_init(void){
    
    PIE0bits.TMR0IE =1; 	//enable interrupt source TMR0 (timer)
    INTCONbits.GIE=1; 	//turn on interrupts globally (when this is off, all interrupts are deactivated)
    INTCONbits.PEIE=1; //enable peripheral interupts
    
    LATHbits.LATH3=0; //set initial output state of LED
    TRISHbits.TRISH3=0; //set TRIS value for pin (output)
    
	// turn on global interrupts, peripheral interrupts and the interrupt source 
	// It's a good idea to turn on global interrupts last, once all other interrupt configuration is done.
}

/************************************
 * High priority interrupt service routine
 * Make sure all enabled interrupts are checked and flags cleared
************************************/

void __interrupt(high_priority) HighISR()
{
    if (PIR0bits.TMR0IF){ // check interrupt source
        LATHbits.LATH3=!LATHbits.LATH3; //toggle LED
        PIR0bits.TMR0IF=0; //clear interrupt flag
        TMR0L=3035 & 0x00FF ; //Assigns 8 LSB, AND removes 8 MSB
        TMR0H=(3035>>8); //Rest of the number
    }
    
							
	//add your ISR code here i.e. check the flag, do something (i.e. toggle an LED), clear the flag...
}

