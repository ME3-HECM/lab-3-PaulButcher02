#include <xc.h>
#include "timers.h"

/************************************
 * Function to set up timer 0
************************************/
void Timer0_init(void)
{
    T0CON1bits.T0CS=0b010; // Fosc/4
    T0CON1bits.T0ASYNC=1; // see datasheet errata - needed to ensure correct operation when Fosc/4 used as clock source
    T0CON1bits.T0CKPS=0b1000; // 1:256 Prescale 
    T0CON0bits.T016BIT=1;	//8bit/16bit mode	
	
    // it's a good idea to initialise the timer registers so we know we are at 0
    //In 8 bit TMR0H is end value; TMR0L is start
    
    TMR0H=0;            //write High reg first, update happens when low reg is written to
    TMR0L=0;
    T0CON0bits.T0EN=1;	//start the timer
    
    
}

/************************************
 * Function to return the full 16bit timer value
 * Note TMR0L and TMR0H must be read in the correct order, or TMR0H will not contain the correct value
************************************/
unsigned int get16bitTMR0val(void)
{
    unsigned int disp_val=TMR0L; //First reading TMR0L to ensure TMR0H will read correctly
    disp_val|=(TMR0H<<8); //Bit shifting TMR0H to become a 16 bit number with 8 empty LSB, and then combine with TMR0LS

    return disp_val;
	//add your code to get the full 16 bit timer value here
}
