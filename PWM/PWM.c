#include "stm32f10x.h"                  // Device header

void PWM_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//开启tim时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//开启gpio
	
	GPIO_InitTypeDef GPIO_InitStructure;//初始化GPIO
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	TIM_InternalClockConfig(TIM2);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;//定时器配置
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 20000 - 1;		//ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;		//PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	TIM_OCInitTypeDef TIM_OCInitStructure;//pwm配置
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//配置输出比较模式看下面
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//配置输出电平     #define TIM_OCPolarity_High                ((uint16_t)0x0000)高电平  #define TIM_OCPolarity_Low                 ((uint16_t)0x0002)低电平
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//开或关
	TIM_OCInitStructure.TIM_Pulse = 0;		//CCR
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);//配置CH值也就是选择引脚
	
	TIM_Cmd(TIM2, ENABLE);
}

void PWM_SetCompare2(uint16_t Compare)
{
	TIM_SetCompare2(TIM2, Compare);//用于修改ccr
}


/*输出比较模式看图P3
#define TIM_OCMode_Timing                  ((uint16_t)0x0000)冻结模式
#define TIM_OCMode_Active                  ((uint16_t)0x0010)相等时为有效电平
#define TIM_OCMode_Inactive                ((uint16_t)0x0020)相等时为无效电平
#define TIM_OCMode_Toggle                  ((uint16_t)0x0030)相等时电平翻转
#define TIM_OCMode_PWM1                    ((uint16_t)0x0060) pwm1
#define TIM_OCMode_PWM2                    ((uint16_t)0x0070) pwm2

*/