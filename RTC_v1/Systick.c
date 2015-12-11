#include "Systick.h"
#include "MKL46Z4.h"                    // Device header
//extern uint8_t mm;
int32_t volatile msTicks = 0; // Interval counter in ms
void init_SysTick_interrupt(void){
	SysTick->LOAD = SystemCoreClock / 1000; //configured the SysTick to count in 1ms
	/* Select Core Clock & Enable SysTick & Enable Interrupt */
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk |SysTick_CTRL_TICKINT_Msk|SysTick_CTRL_ENABLE_Msk;
}
void SysTick_Handler(void) { // SysTick interrupt Handler
	msTicks++; // Increment counter
}
void delay_mss(uint32_t TICK) {
	while (msTicks < TICK); // Wait 500ms
	msTicks = 0; // Reset counter
}