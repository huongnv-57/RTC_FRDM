#include "mode.h"
#include "MKL46Z4.h"                    // Device header
#include "SLCD.h"
#include "RTC.h"
#include "Systick.h"
#include "LED.h"

extern uint8_t SW1_INDEX, SUBMODE,main_flow,alarm_state;
extern uint32_t hh, mm, ss;
extern uint32_t rtc_seconds_count,alarm_seconds_count;
extern uint32_t hha,mma;

void defaultMode(void){//display mode
	rtc_seconds_count= RTC->TSR;
	alarm_seconds_count= RTC->TAR;
	hha= alarm_seconds_count/3600;
	hha%=24;
	mma=alarm_seconds_count/60;
	mma%=60;
	
	ss=rtc_seconds_count%60;			//ss = 0->59
	mm=rtc_seconds_count/60;			//mm = 0->59
	hh=rtc_seconds_count/3600;
	mm%=60;
	hh = hh%24;										//hh = 0->24
	SegLCD_DisplayTime(hh,mm);		
	
	//SegLCD_Set(uint8_t Value,uint8_t Digit);
	/* Blink 2 dots in middle */
	SegLCD_Col_On();
	delay_mss(500);
	SegLCD_Col_Off();	
	delay_mss(500);
}
void settingHH(void){
	SegLCD_DisplayTime(hh,mm);		
	//SegLCD_Col_On();	
	delay_mss(200);
	//Disable LCD
	LCD->WF8B[LCD_FRONTPLANE0] = (LCD_CLEAR);
	LCD->WF8B[LCD_FRONTPLANE1] = (LCD_CLEAR);
	LCD->WF8B[LCD_FRONTPLANE2] = (LCD_CLEAR);
	LCD->WF8B[LCD_FRONTPLANE3] = (LCD_CLEAR);
	//SegLCD_Col_Off();	
	delay_mss(200);
}
void settingMM(void){
	SegLCD_DisplayTime(hh,mm);
	SegLCD_Col_On();
	delay_mss(200);
	LCD->WF8B[LCD_FRONTPLANE4] = (LCD_CLEAR);
	LCD->WF8B[LCD_FRONTPLANE5] = (LCD_CLEAR);
	LCD->WF8B[LCD_FRONTPLANE6] = (LCD_CLEAR);
	LCD->WF8B[LCD_FRONTPLANE7] = (LCD_CLEAR);
	SegLCD_Col_Off();	
	delay_mss(200);
}
void settingHHa(void){
	SegLCD_DisplayTime(hha,mma);		
	//SegLCD_Col_On();	
	delay_mss(200);
	//Disable LCD
	LCD->WF8B[LCD_FRONTPLANE0] = (LCD_CLEAR);
	LCD->WF8B[LCD_FRONTPLANE1] = (LCD_CLEAR);
	LCD->WF8B[LCD_FRONTPLANE2] = (LCD_CLEAR);
	LCD->WF8B[LCD_FRONTPLANE3] = (LCD_CLEAR);
	//SegLCD_Col_Off();	
	delay_mss(200);
}
void settingMMa(void){
	SegLCD_DisplayTime(hha,mma);
	SegLCD_Col_On();
	delay_mss(200);
	LCD->WF8B[LCD_FRONTPLANE4] = (LCD_CLEAR);
	LCD->WF8B[LCD_FRONTPLANE5] = (LCD_CLEAR);
	LCD->WF8B[LCD_FRONTPLANE6] = (LCD_CLEAR);
	LCD->WF8B[LCD_FRONTPLANE7] = (LCD_CLEAR);
	SegLCD_Col_Off();	
	delay_mss(200);
}
void settingAlarm(void){
	//hha: mma
	SegLCD_DisplayDecimal(alarm_state);

}
void configAlarm(void){
	if (alarm_state ==1){
		main_flow =0;
		chooseSUBMODE(&SUBMODE);
	}else{
		SW1_INDEX=5;
	}
}
void savingChanges(void){
	//Disable RTC
	RTC->SR &= ~ RTC_SR_TCE_MASK;
	
	//Resetting seconds in RTC
	rtc_seconds_count=hh*3600 + mm * 60 +ss;
	alarm_seconds_count=hha*3600+mma*60;
	
	RTC->TSR =rtc_seconds_count;					//TSR++ when TSR>=32767
	RTC->TPR = ss;	
	RTC->TAR=alarm_seconds_count;
	//enable RTC
	RTC->SR |= RTC_SR_TCE_MASK;
}

void chooseMode (uint8_t *sw1){
	if (*sw1==0){
		defaultMode();
	}else if(*sw1==1){
		settingHH();
	}else if(*sw1==2){
		settingMM();
	}else if(*sw1==3){
		settingAlarm();
	}else if(*sw1==4){
		configAlarm();
	}else if(*sw1==5){
		savingChanges();
		*sw1=0;
	}
}
void chooseSUBMODE(uint8_t *submode){
	if (*submode==0){
		settingHHa();
	}else if(*submode==1){
		settingMMa();
	}else if(*submode==2){
		*submode=0;
		SW1_INDEX=5;//MODE5 saving and exit
		main_flow=1;
		
	}
	
}