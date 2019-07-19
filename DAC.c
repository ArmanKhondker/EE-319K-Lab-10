// dac.c
// This software configures DAC output
// Runs on LM4F120 or TM4C123
// Program written by: Dhruv and Arman
// Date Created: 3/6/17 
// Last Modified: 3/6/17 
// Lab number: 6
// Hardware connections
// TO STUDENTS "REMOVE THIS LINE AND SPECIFY YOUR HARDWARE********

#include <stdint.h>
#include "tm4c123gh6pm.h"
// Code files contain the actual implemenation for public functions
// this file also contains an private functions and private data

// **************DAC_Init*********************
// Initialize 4-bit DAC, called once 
// Input: PE 0-2
// Output: PB 0-5
void DAC_Init(void){
		volatile unsigned long delay;
	SYSCTL_RCGC2_R |= 0x2;              //enable Port B
	delay = SYSCTL_RCGC2_R;             //wait
	GPIO_PORTB_AMSEL_R &= ~0x3F;        //disable analog function on PB5-0
  GPIO_PORTB_PCTL_R &= ~0x00FFFFFF;   //enable regular GPIO
  GPIO_PORTB_DIR_R |= 0x3F;           //output PB5-0
  GPIO_PORTB_AFSEL_R &= ~0x3F;        //regular function PB5-0
  GPIO_PORTB_DEN_R |= 0x3F;           //enable PB5-0
}

// **************DAC_Out*********************
// output to DAC
// Input: 6-bit data, 0 to 63 
// Output: none
void DAC_Out(uint32_t data){
		GPIO_PORTB_DATA_R = data;
}
