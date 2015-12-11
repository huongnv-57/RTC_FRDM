#include "Led.h"
#include "MKL46Z4.h"                    // Device header

void initLED(void){
	SIM->SCGC5|=SIM_SCGC5_PORTD_MASK; //enable the clock for PORTD
	SIM->SCGC5|=SIM_SCGC5_PORTE_MASK; //enable the clock for PORTE
	
	PORTD->PCR[5]|=PORT_PCR_MUX(1u); 	// PIN5 PORTD as GPIO
	PORTE->PCR[29]|=PORT_PCR_MUX(1u);	// PIN29 PORTE as GPIO
	PTD->PDDR|=(1u<<5); 							// config PIN5 PORTD as output pin
	PTE->PDDR|=(1u<<29);							// config PIN5 PORTD as output pin
	offLED1();
	offLED2();
}

void blinkLED(int time){
		uint32_t count;
		onLED1();
		onLED2();
		
		//Delay
		for (count =0;count <time;count ++){};
		
		offLED1();
		offLED2();
		
			//Delay
		for (count =0;count <time;count ++){};
}	
void onLED1(){
	PTD->PCOR|=(1u<<5);							//Clear bit -> LED1 ON
}
void offLED1(){
	PTD->PSOR|=(1u<<5);							//Set bit LED OFF
}
void onLED2(){
	PTE->PCOR|=(1u<<29);						//On
}
void offLED2(){
	PTE->PSOR|=(1u<<29);						//off
}
void toggleLED1(void){
	PTD->PTOR |= (1u<<5);
}

void toggleLED2(void){
	PTE->PTOR |= (1u<<29);
}

