#include"Pit.h"
void PIT_enable(uint32_t ldval){
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK; /* SIM_SCGC6: PIT=1 : Enable PIT Clock gatecontrol*/
	PIT->MCR = 0x00U; 								//PIT_MCR: MDIS=0,FRZ=0 : Enable device clock
	
	PIT->CHANNEL[1].TCTRL = 0x00U; /* PIT_TCTRL0: CHN=0,TIE=0,TEN=0 : Clear controlregister */
	PIT->CHANNEL[1].TFLG = PIT_TFLG_TIF_MASK; /* PIT_TFLG0: TIF=1: Clear timer flag register*/
	PIT->CHANNEL[1].LDVAL = PIT_LDVAL_TSV(ldval-1); /* PIT_LDVAL0: TSV=0xD1B6: Set upload register */
	NVIC_SetPriority(22, 2); /* Set priority for PIT IRQ22 */
	NVIC_EnableIRQ(22); /* Enable IRQ for PIT IRQ22 */
	/* PIT_TCTRL0: CHN=0,TIE=1,TEN=1 */
	PIT->CHANNEL[1].TCTRL = (PIT_TCTRL_TIE_MASK | PIT_TCTRL_TEN_MASK|PIT_TCTRL_CHN_MASK); /* Set up controlregister */
	
	
	
	PIT->CHANNEL[0].TCTRL = 0x00U; /* PIT_TCTRL0: CHN=0,TIE=0,TEN=0 : Clear controlregister */
	PIT->CHANNEL[0].TFLG = PIT_TFLG_TIF_MASK; /* PIT_TFLG0: TIF=1: Clear timer flag register*/
	PIT->CHANNEL[0].LDVAL = PIT_LDVAL_TSV(13980000-1); /* PIT_LDVAL0: TSV=0xD1B6: Set upload register */
	
	/* PIT_TCTRL0: CHN=0,TIE=1,TEN=1 */
	PIT->CHANNEL[0].TCTRL = (PIT_TCTRL_TEN_MASK); /* Set up controlregister */
	
	//TIMER2
	
	
}
