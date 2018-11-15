#include "stm32f0xx_conf.h"
#include "delay.h"

int main(void) {
	delay_init();

	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_WriteBit(GPIOA, GPIO_Pin_0, SET);

	while (1) {
		GPIO_WriteBit(GPIOA, GPIO_Pin_0, RESET);
		delay_ms(100);
		GPIO_WriteBit(GPIOA, GPIO_Pin_0, SET);
		delay_ms(100);
	}

}
