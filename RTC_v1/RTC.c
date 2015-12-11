#include "RTC.h"
#include "Led.h"
#include "Systick.h"
#define ALARM_TIME 5
#define RTC_SOURCE_CKL 1000u
extern uint32_t alarm_seconds_count;
extern uint32_t rtc_seconds_count;
extern uint8_t alarm_state;


void initRTC(void){
	unsigned int i;
	SIM->SCGC6 |= SIM_SCGC6_RTC_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
	PORTC->PCR[1] &= ~PORT_PCR_MUX_MASK;
	PORTC->PCR[1] = PORT_PCR_MUX(1);
	
	SIM->SOPT1 &= ~SIM_SOPT1_OSC32KSEL_MASK;
  SIM->SOPT1 |= SIM_SOPT1_OSC32KSEL(0x02u);//Slect RTC source clock as RTC_CLKIN
	
	RTC->IER |= RTC_IER_TSIE_MASK | RTC_IER_TAIE_MASK;//Enable Time seconds and alarm interrupt
	
	
	NVIC_EnableIRQ(RTC_Seconds_IRQn);		//RTC_seconds interrupt
	//NVIC_EnableIRQ(RTC_IRQn);						//Enable interrupt by NVIC
    if (RTC->SR & RTC_SR_TIF_MASK)
    {
        /* Reset RTC if time is invalid */
        RTC->CR |= RTC_CR_SWR_MASK;
        RTC->CR &= ~RTC_CR_SWR_MASK;
    }
		i = RTC->TSR;//read the previous value
		RTC->TSR = i;//write back 
    /* Enable RTC */
    RTC->SR |= RTC_SR_TCE_MASK;
}

void RTC_Seconds_IRQHandler(void){
  rtc_seconds_count++;
}
void RTC_IRQHandler (void){
	 if(RTC->SR & RTC_SR_TAF_MASK) // RTC timer alarm flag is set
    {
			toggleLED2();
      RTC->TAR = RTC->TAR;     // write new value to TAR to clear TAF
			alarm_state=0;
			offLED1(); //led status
    }
}