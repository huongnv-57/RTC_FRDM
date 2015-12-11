#ifndef mode
#define mode

#include "MKL46Z4.h"                    // Device header

void defaultMode(void);		//defaulf mode: display HH:MM
void settingHH(void);			//Blink HH, press SW2 to increase HH
void settingMM(void);			//Blink MM, press SW2 to increase MM
void settingAlarm(void);  //GreenLED on if enable and vice verse
void configAlarm(void);		//setting HHMM for alarm
void savingChanges(void);	//display saving and leave displayMode

void settingHHa(void);
void settingMMa(void);
void chooseSUBMODE(uint8_t *submode);

void chooseMode(uint8_t *sw1);


#endif	//mode
