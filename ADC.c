// ADC.c
// Runs on LM4F120/TM4C123
// Provide functions that initialize ADC0
// Last Modified: 3/6/2015 
// Student names: Dhruv and Arman
// Last modification date: change this to the last modification date or look very silly

#include <stdint.h>
#include "tm4c123gh6pm.h"

// ADC initialization function 
// Input: none
// Output: none
void ADC_Init(void){ 
	SYSCTL_RCGCGPIO_R |= 0x10;      // 1) activate clock for Port E 
  while((SYSCTL_PRGPIO_R&0x10) == 0){}; 
		GPIO_PORTE_DIR_R &= ~0xC;      // 2) make PE2 input
		GPIO_PORTE_AFSEL_R |= 0xC;     // 3) enable alternate fun on PE2
  GPIO_PORTE_DEN_R &= ~0xC;      // 4) disable digital I/O on PE2 
		GPIO_PORTE_AMSEL_R |= 0xC;     // 5) enable analog fun on PE2
		SYSCTL_RCGCADC_R |= 0x03;       // 6) activate ADC0  
 uint32_t		delay = SYSCTL_RCGCADC_R;       // extra time to stabilize
		delay = SYSCTL_RCGCADC_R;       // extra time to stabilize
  delay = SYSCTL_RCGCADC_R;       // extra time to stabilize  
		delay = SYSCTL_RCGCADC_R;  
		ADC0_PC_R = 0x01;               // 7) configure for 125K  
		ADC0_SSPRI_R = 0x0123;          // 8) Seq 3 is highest priority 
		ADC0_ACTSS_R &= ~0x0008;        // 9) disable sample sequencer 3
  ADC0_EMUX_R &= ~0xF000;         // 10) seq3 is software trigger  
		ADC0_SSMUX3_R = (ADC0_SSMUX3_R&0xFFFFFFF0)+1;  // 11) Ain1 (PE2)
		ADC0_SSCTL3_R = 0x0006;         // 12) no TS0 D0, yes IE0 END0 
		ADC0_IM_R &= ~0x0008;           // 13) disable SS3 interrupts  
		ADC0_SAC_R = 0X06;              // FOR AVERAGING REMOVE IF IT BREAKS
		ADC0_ACTSS_R |= 0x0008;         // 14) enable sample sequencer 3
		
		ADC1_PC_R = 0x01;               // 7) configure for 125K  
		ADC1_SSPRI_R = 0x0123;          // 8) Seq 3 is highest priority 
		ADC1_ACTSS_R &= ~0x0008;        // 9) disable sample sequencer 3
  ADC1_EMUX_R &= ~0xF000;         // 10) seq3 is software trigger  
		ADC1_SSMUX3_R = (ADC1_SSMUX3_R&0xFFFFFFF0)+0;  // 11) Ain0 (PE3)
		ADC1_SSCTL3_R = 0x0006;         // 12) no TS0 D0, yes IE0 END0 
		ADC1_IM_R &= ~0x0008;           // 13) disable SS3 interrupts  
		ADC1_SAC_R = 0X06;              // FOR AVERAGING REMOVE IF IT BREAKS
		ADC1_ACTSS_R |= 0x0008;         // 14) enable sample sequencer 3


}

//------------ADC_In------------
// Busy-wait Analog to digital conversion
// Input: none
// Output: 12-bit result of ADC conversion
uint32_t ADC_InX(void){  
	uint32_t data;  
	ADC0_PSSI_R = 0x0008;     
  while((ADC0_RIS_R&0x08)==0){};      
	data = ADC0_SSFIFO3_R&0xFFF;
  ADC0_ISC_R = 0x0008;  
	return data;
  
}
uint32_t ADC_InY(void){  
	uint32_t data;  
	ADC1_PSSI_R = 0x0008;     
  while((ADC1_RIS_R&0x08)==0){};      
	data = ADC1_SSFIFO3_R&0xFFF;
  ADC1_ISC_R = 0x0008;  
	return data;
  
}


