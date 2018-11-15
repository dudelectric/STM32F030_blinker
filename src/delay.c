#include "stm32f0xx.h"
#include "stdint.h"
#include "delay.h"

#define MillisecondsIT 1e3
volatile uint32_t Milliseconds = 0, Seconds = 0;

void SysTick_Handler(void) {
	Milliseconds++; //Increment millisecond variable
	if (Milliseconds % 1000 == 999) { //If 1000 milliseconds have passed, increment seconds
		Seconds++;
	}
}

void delay_ms(uint32_t nTime) {
	volatile uint32_t MSStart = Milliseconds;
	while ((Milliseconds - MSStart) < nTime)
		asm volatile("nop");
}

void delay_s(uint32_t nTime) {
	volatile uint32_t Ss = Seconds;
	while ((Seconds - Ss) < nTime)
		asm volatile("nop");
}
void delay_init(void) {
	SystemInit(); //Ensure CPU is running at correctly set clock speed
	SystemCoreClockUpdate(); //Update SystemCoreClock variable to current clock speed
	SysTick_Config(SystemCoreClock / MillisecondsIT); //Set up a systick interrupt every millisecond
}

//static __IO uint32_t  	TimingDelay;
//static volatile uint64_t  	_micros;
//
////72 MHz/1000000 = 72,  Every 1 Usec the timer triggers a call to the SysTick_Handler
//void delay_init(void) {
//	SysTick_Config(72);
//	_micros = 0;
//}
//
//void SysTick_Handler() {
//	if (TimingDelay != 0) TimingDelay--;
//	_micros++;
//}
//
//void delay_us(uint32_t nTime) {
//	TimingDelay = nTime;
//	while (TimingDelay != 0);
//}
//
//void delay_ms(uint32_t nTime) {
//	TimingDelay = nTime*1000;
//	while (TimingDelay != 0);
//}
//
//uint32_t millis(void){
//	return _micros/1000;
//}
