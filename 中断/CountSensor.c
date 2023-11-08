#include "stm32f10x.h"                  // Device header

uint16_t CountSensor_Count;

void CountSensor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;//初始化gpio
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);//配置afio的数据选择GPIO作为中断源
	//配置exti
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line14;//配置中断线EXTI_LineX  x=0 — 15
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;//是否开启
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//EXTI_Mode_Interrupt = 0x00中断模式, EXTI_Mode_Event = 0x04事件模式
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//  EXTI_Trigger_Rising = 0x08 上升沿触发, EXTI_Trigger_Falling = 0x0C下降沿触发,  EXTI_Trigger_Rising_Falling = 0x10边沿触发
	EXTI_Init(&EXTI_InitStructure);
	//配置nvic
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//nvic分组 具体查看nvic.txt
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//查看irqh.txt 选择EXTI通道
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//是否开启
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//响应优先级
	NVIC_Init(&NVIC_InitStructure);
}

uint16_t CountSensor_Get(void)
{
	return CountSensor_Count;//中断函数里面的CountSensor_Count ++来计数
}

void EXTI15_10_IRQHandler(void)//中断函数是固定的，请参考中断向量表.txt选择中断函数
{
	if (EXTI_GetITStatus(EXTI_Line14) == SET)//判断是不是exti14进来的
	{
		/*如果出现数据乱跳的现象，可再次判断引脚电平，以避免抖动*/
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 0)
		{
			CountSensor_Count ++;
		}
		EXTI_ClearITPendingBit(EXTI_Line14);//清除中断标志位
	}
}
