#include "MKL46Z4.h"                    // Device header
#include "sw.h"

void initSW(){
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
	PORTC->PCR[3] = PORT_PCR_MUX(1u) | PORT_PCR_PE_MASK|PORT_PCR_PS_MASK;
	PORTC->PCR[12] |= PORT_PCR_MUX(1u)| PORT_PCR_PE_MASK|PORT_PCR_PS_MASK;
	
	PTC->PDDR &= ~((uint32_t)(1u<<3));					//input PIN
	PTC->PDDR &= ~((uint32_t)(1u<<12));
}
void initSW_i(void){
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
	PORTC->PCR[3] = PORT_PCR_MUX(1u)| PORT_PCR_PE_MASK| PORT_PCR_PS_MASK|PORT_PCR_IRQC(0xA);//RISING EDGES
	PORTC->PCR[12] = PORT_PCR_MUX(1u)| PORT_PCR_PE_MASK| PORT_PCR_PS_MASK|PORT_PCR_IRQC(0xA);//RISING EDGES
	
	PTC->PDDR &= ~((uint32_t)(1u<<3));					//input PIN
	PTC->PDDR &= ~((uint32_t)(1u<<12));
	NVIC_ClearPendingIRQ(31);
	NVIC_EnableIRQ(31);
}


int isPress_SW1(){
	if (PTC->PDIR & (1u << 3)){ 	//1 and 1 = 1; 1 and 0 = 0   
		return 0;										//if sw =1 -> not press
	}else{
		return 1;
	}
}
int isPress_SW3(){
	if (PTC->PDIR & (1u << 12)){ 	//1 and 1 = 1; 1 and 0 = 0   
		return 0;										//if sw =1 -> not press
	}else{
		return 1;
	}
}
