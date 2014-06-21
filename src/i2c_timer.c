/*
 * i2c.c
 *
 *  Created on: Mar 24, 2014
 *      Author: Kevin
 */

#include "i2c_timer.h"

void i2cTimerInit()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);

	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;

	NVIC_Init(&NVIC_InitStructure);

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Prescaler=2;
	TIM_TimeBaseStructure.TIM_Period=24000;
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;

	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);

	TIM_Cmd(TIM4,ENABLE);
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);

}

void i2cTimeDeInit()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelCmd=DISABLE;

	NVIC_Init(&NVIC_InitStructure);

	TIM_ITConfig(TIM4,TIM_IT_Update,DISABLE);
	TIM_Cmd(TIM4,DISABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,DISABLE);

}


 void TIM4_IRQHandler()
{
	if(TIM_GetITStatus(TIM4,TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
		CPAL_I2C_TIMEOUT_Manager();
	}
}


