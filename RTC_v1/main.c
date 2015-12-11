#include "MKL46Z4.h"                    // Device header
#include "RTC.h"
#include "sw.h"
#include "Led.h"
#include "SLCD.h"
#include "mode.h"
#include "Systick.h"
uint8_t SW1_INDEX=0; //Mode to go next

uint32_t alarm_seconds_count=0,hha=0,mma=0; //alarm time
uint32_t rtc_seconds_count =0,hh=0, mm=0,ss =0;//time
uint8_t SUBMODE=0,main_flow=1,alarm_state =0; //control flow variables



int main(){
	init_SysTick_interrupt();
	initSW_i();//initialize SW with interrupt enable
	initLED();
	//initRTC();
	
	initSLCD();
	SegLCD_DisplayDecimal(10);
	
	initRTC();
	while(1){
		chooseMode(&SW1_INDEX); //include if mode =5 save then mode = 1
	}

}

void PORTC_PORTD_IRQHandler(void){
		if(PORTC->ISFR &(1<<3)) {		//if SW1 is pressed, goto next mode
			if (main_flow==1){
					SW1_INDEX ++;
					
			}else{
					SUBMODE++;
			}
			PORTC->PCR[3] |= PORT_PCR_ISF_MASK;	//clear interrupt
		}
		if(PORTC->ISFR &(1<<12)) {
			if(main_flow==1){
				if (SW1_INDEX ==1){
					//hh-mode
					hh++;
					hh%=24;
				}
				if (SW1_INDEX ==2){
					//mm-mode
					mm++;
					mm%=60;
				}
				if (SW1_INDEX ==3){
					//alarm enable mode
					if(alarm_state==0){
						alarm_state =1;
						onLED1();
						NVIC_EnableIRQ(RTC_IRQn);
					}else{
						alarm_state =0;
						offLED1();
						NVIC_DisableIRQ(RTC_IRQn);
					}
				}
			}else{
				if(SUBMODE==0){
					hha++;
					hha%=24;
				}
				if (SUBMODE==1){
					mma++;
					mma%=60;
				}
			}
			PORTC->PCR[12] |= PORT_PCR_ISF_MASK;
		}
}