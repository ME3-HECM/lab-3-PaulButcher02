#include <xc.h>
#include "interrupts.h"
extern volatile unsigned int triggered = 0;
//extern volatile unsigned int triggered = 0;
/************************************
 * Function to turn on interrupts and set if priority is used
 * Note you also need to enable peripheral interrupts in the INTCON register to use CM1IE.
************************************/
void Interrupts_init(void){
    
    PIE2bits.C1IE =1; 	//enable interrupt source C1I
    INTCONbits.GIE=1; 	//turn on interrupts globally (when this is off, all interrupts are deactivated)
    INTCONbits.PEIE=1; //enable peripheral interupts
    LATHbits.LATH3=0; //set initial output state of LED
    TRISHbits.TRISH3=0; //set TRIS value for pin (output)
    
    LATDbits.LATD7=0; //set initial output state of LED
    TRISDbits.TRISD7=0; //set TRIS value for pin (output)
    
	// turn on global interrupts, peripheral interrupts and the interrupt source 
	// It's a good idea to turn on global interrupts last, once all other interrupt configuration is done.
}

/************************************
 * High priority interrupt service routine
 * Make sure all enabled interrupts are checked and flags cleared
************************************/

void __interrupt(high_priority) HighISR()
{
    if(PIR2bits.C1IF){ 					//check the interrupt source
        LATHbits.LATH3=1;
        PIR2bits.C1IF=0; 
        triggered=1;
    }
    
    //LATHbits.LATH3=!LATHbits.LATH3;
    
							//clear the interrupt flag!
	//add your ISR code here i.e. check the flag, do something (i.e. toggle an LED), clear the flag...
}

