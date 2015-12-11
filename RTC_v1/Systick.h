#ifndef Systick
#define Systick
#include "MKL46Z4.h"
void init_SysTick_interrupt(void);
void SysTick_Handler(void);
void delay_mss(uint32_t TICK);
#endif
