#include "stm32f10x.h"                  // Device header

void Timer_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	TIM_InternalClockConfig(TIM2);//选择内部定时器
	//初始化TIM
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//分频#define TIM_CKD_DIV1                       ((uint16_t)0x0000) 1分频#define TIM_CKD_DIV2            2分频           ((uint16_t)0x0100)#define TIM_CKD_DIV4  4分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//                      #define TIM_CounterMode_Up               ((uint16_t)0x0000) 向上计数    #define TIM_CounterMode_Down               ((uint16_t)0x0010) 向下计数   #define TIM_CounterMode_CenterAligned1     ((uint16_t)0x0020)#define TIM_CounterMode_CenterAligned2     ((uint16_t)0x0040)#define TIM_CounterMode_CenterAligned3     ((uint16_t)0x0060)（中央对齐计数有需要看图P1）
	TIM_TimeBaseInitStructure.TIM_Period = 10000 - 1;//arr
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7200 - 1;//psc
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;//重复计数
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);//手动更新定时中断位
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);//开启中断 第一个选择时钟，第二个更新中断，第三个开启
	//配置nvic具体看中断
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;//映射到nvic
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM2, ENABLE);
}

/*
void TIM2_IRQHandler(void)//中断函数
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
*/
