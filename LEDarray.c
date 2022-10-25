#include <xc.h>
#include "LEDarray.h"

#define BM9 256
#define BM8 128
#define BM7 64
#define BM6 32
#define BM5 16
#define BM4 8
#define BM3 4
#define BM2 2
#define BM1 1




/************************************
/ LEDarray_init
/ Function used to initialise pins to drive the LEDarray
************************************/
void LEDarray_init(void)
{
    TRISGbits.TRISG0 = 0; 	//set up TRIS registers for pins connected to LED array
    TRISGbits.TRISG1 = 0;
    TRISAbits.TRISA2 = 0;
    TRISAbits.TRISA4 = 0;
    TRISAbits.TRISA5 = 0;
    TRISFbits.TRISF0 = 0;
    TRISFbits.TRISF6 = 0;
    TRISBbits.TRISB0 = 0;
    TRISBbits.TRISB1 = 0;
	
    LATGbits.LATG0 = 0; //set initial output LAT values (they may have random values when powered on) 	
    LATGbits.LATG1 = 0;
    LATAbits.LATA2 = 0;
    LATAbits.LATA4 = 0;
    LATAbits.LATA5 = 0;
    LATFbits.LATF0 = 0;
    LATFbits.LATF6 = 0;
    LATBbits.LATB0 = 0;
    LATBbits.LATB1 = 0;

    __delay_ms(1000);
    ANSELGbits.ANSELG0 = 0; //TURN OFF ANALOGUE SHIT
    ANSELGbits.ANSELG1 = 0;
    ANSELAbits.ANSELA2 = 0;
    ANSELAbits.ANSELA4 = 0;
    ANSELFbits.ANSELF0 = 0;
    ANSELFbits.ANSELF6 = 0;
    ANSELBbits.ANSELB0 = 0;
    ANSELBbits.ANSELB1 = 0;
}

/************************************
/ LEDarray_disp_bin
/ Function used to display a number on the LED array in binary
************************************/
void LEDarray_disp_bin(unsigned int number)
{   
  //We want to check to see if every individual bit is present in the number input (only need to do powers of 2)  
    if (number&1) {LATGbits.LATG0 = 1;} //Checks to see if there's an overlap between the binary for number and binary for 1
    else {LATGbits.LATG0 = 0;}
    
    if (number&2) {LATGbits.LATG1 = 1;}
    else {LATGbits.LATG1 = 0;}
    
    if (number&4) {LATAbits.LATA2 = 1;}
    else {LATAbits.LATA2 = 0;}
    
    if (number&8) {LATFbits.LATF6 = 1;}
    else {LATFbits.LATF6 = 0;}
    
    if (number&16) {LATAbits.LATA4 = 1;}
    else {LATAbits.LATA4 = 0;}
    
    if (number&32) {LATAbits.LATA5 = 1;}
    else {LATAbits.LATA5 = 0;}
    
    if (number&64) {LATFbits.LATF0 = 1;}
    else {LATFbits.LATF0 = 0;}
    
    if (number&128) {LATBbits.LATB0 = 1;}
    else {LATBbits.LATB0 = 0;}
    
    if (number&256) {LATBbits.LATB1 = 1;}
    else {LATBbits.LATB1 = 0;}
    

	//some code to turn on/off the pins connected to the LED array
	//if statements and bit masks can be used to determine if a particular pin should be on/off
	//see Readme.md for examples
}

/************************************
/ Function LEDarray_disp_dec
/ Used to display a number on the LEDs
/ where each LED is a value of 10
************************************/
void LEDarray_disp_dec(unsigned int number)
{  
	//some code to manipulate the variable number into the correct
	//format and store in disp_val for display on the LED array
    unsigned int disp_val=1;
 
    number = (number-number%10)/10;      //Floors number and then div to find number of 10s
    disp_val<<=number;              // Moves MSB to the left to be one higher than the required LED
    disp_val-=1;                    //Changes disp_val to have all LEDS on, e.g. 00010000 becomes 00001111
    
    LEDarray_disp_bin(disp_val);    //display value on LED array  
}




/************************************
/ LEDarray_disp_PPM
/ Function used to display a level on the LED array with peak hold
/ cur_val is the current level from the most recent sample, and max is the peak value for the last second
/ these input values need to calculated else where in your code
************************************/
void LEDarray_disp_PPM(unsigned int cur_val, unsigned int max_val)
{
    unsigned int disp_val = 0;        
    max_val=(max_val-max_val%10)/10; //Find number of 10s in max_val
    cur_val=(cur_val-cur_val%10)/10; //Find number of 10s in cur_val
    
    
    //max_val and cur_val bit manipulation
    //cur_val done as above
    //max_val needs MSB == highest LED, therefore subtract one before bit shift
    
    disp_val=(1<<(max_val-1))|((1<<cur_val)-1); //processed values combined using OR function
  	LEDarray_disp_bin(disp_val);	//display value on LED array  
    
    
    
    
    
    
    
    
    
    
    
    
    
    
//    int pow = 1; //Must start with pow>0 or binary shift won't work
//    for (int i = 1; i <= 9; i++) {
//        if (i!= 1) {
//            pow <<= 1;
//        }
//        if (max_val >= i * 10) {
//            biggest_bit = pow;
//        }
//    }
//            
//    cur_val |= biggest_bit;
	// some code to format the variable cur_val and max, store in disp_val for display on the LED array
	// hint: one method is to manipulate the variables separately and then combine them using the bitwise OR operator
    //disp_val=(cur_val|max)

}
//
//// L1 L2 L3 L4 L5 L6 L7 L8 L9
////  1  1  1  1  1  0  0  0  0
////  1  1  1  1  1  1  1  1  0