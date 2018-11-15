#include "stm32f0xx_conf.h"

#define MillisecondsIT 1e3
volatile uint32_t Milliseconds = 0, Seconds = 0;


void SysTick_Handler(void) {
	Milliseconds++; //Increment millisecond variable
	if (Milliseconds % 1000 == 999) { //If 1000 milliseconds have passed, increment seconds
		Seconds++;
	}
}

void DelayMil(uint32_t MilS) {
	volatile uint32_t MSStart = Milliseconds;
	while ((Milliseconds - MSStart) < MilS)
		asm volatile("nop");
}

void DelaySec(uint32_t S){
	volatile uint32_t Ss = Seconds;
	while((Seconds - Ss)<S) asm volatile("nop");
}

int main(void) {
	SystemInit(); //Ensure CPU is running at correctly set clock speed
	SystemCoreClockUpdate(); //Update SystemCoreClock variable to current clock speed
	SysTick_Config(SystemCoreClock / MillisecondsIT); //Set up a systick interrupt every millisecond

	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_WriteBit(GPIOA, GPIO_Pin_0, SET);

	while (1) {
		GPIO_WriteBit(GPIOA, GPIO_Pin_0, RESET);
		DelayMil(1000);
		GPIO_WriteBit(GPIOA, GPIO_Pin_0, SET);
		DelayMil(1000);
	}

}
