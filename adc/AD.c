#include "stm32f10x.h"                  // Device header

void AD_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);//开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);//配置adcclk   选择分频
// 	    @arg RCC_PCLK2_Div2: ADC clock = PCLK2/2
//   *     @arg RCC_PCLK2_Div4: ADC clock = PCLK2/4
//   *     @arg RCC_PCLK2_Div6: ADC clock = PCLK2/6
//   *     @arg RCC_PCLK2_Div8: ADC clock = PCLK2/8

//初始化GPIo
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
//	第一个ADCX，第二个指定通道ADC_Channel_X（x为0到17），第三个规则组1到16，第四个是采样时间看下面注释
	
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//adc工作模式   下面注释
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//ADC_DataAlign_Right        右对齐              ADC_DataAlign_Left  左对齐
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//触发源看下面
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//连续转换模式  ENABLE连续模式 DISABLE单次模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;//扫描转换模式 ENABLE扫描模式 DISABLE非扫描模式
	ADC_InitStructure.ADC_NbrOfChannel = 1;//通道数目1到16
	ADC_Init(ADC1, &ADC_InitStructure);
	
	ADC_Cmd(ADC1, ENABLE);//开启adc电源
	//adc校准
	ADC_ResetCalibration(ADC1);//复位校准
	while (ADC_GetResetCalibrationStatus(ADC1) == SET);//等待校准
	ADC_StartCalibration(ADC1);//开始校准
	while (ADC_GetCalibrationStatus(ADC1) == SET);//等待开始校准
}

uint16_t AD_GetValue(void)
{
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);//软件触发转换
	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);//等待转换
	return ADC_GetConversionValue(ADC1);//adc获取转换值
}



// 采样时间

// #define ADC_SampleTime_1Cycles5                    ((uint8_t)0x00)
// #define ADC_SampleTime_7Cycles5                    ((uint8_t)0x01)
// #define ADC_SampleTime_13Cycles5                   ((uint8_t)0x02)
// #define ADC_SampleTime_28Cycles5                   ((uint8_t)0x03)
// #define ADC_SampleTime_41Cycles5                   ((uint8_t)0x04)
// #define ADC_SampleTime_55Cycles5                   ((uint8_t)0x05)
// #define ADC_SampleTime_71Cycles5                   ((uint8_t)0x06)
// #define ADC_SampleTime_239Cycles5   


// adc工作模式

// #define ADC_Mode_Independent                       ((uint32_t)0x00000000)adc独立模式
// 下面全部是双adc模式
// #define ADC_Mode_RegInjecSimult                    ((uint32_t)0x00010000)
// #define ADC_Mode_RegSimult_AlterTrig               ((uint32_t)0x00020000)
// #define ADC_Mode_InjecSimult_FastInterl            ((uint32_t)0x00030000)
// #define ADC_Mode_InjecSimult_SlowInterl            ((uint32_t)0x00040000)
// #define ADC_Mode_InjecSimult                       ((uint32_t)0x00050000)
// #define ADC_Mode_RegSimult                         ((uint32_t)0x00060000)
// #define ADC_Mode_FastInterl                        ((uint32_t)0x00070000)
// #define ADC_Mode_SlowInterl                        ((uint32_t)0x00080000)
// #define ADC_Mode_AlterTrig      

// 触发源选择
// #define ADC_ExternalTrigConv_T1_CC1                ((uint32_t)0x00000000) /*!< For ADC1 and ADC2 */
// #define ADC_ExternalTrigConv_T1_CC2                ((uint32_t)0x00020000) /*!< For ADC1 and ADC2 */
// #define ADC_ExternalTrigConv_T2_CC2                ((uint32_t)0x00060000) /*!< For ADC1 and ADC2 */
// #define ADC_ExternalTrigConv_T3_TRGO               ((uint32_t)0x00080000) /*!< For ADC1 and ADC2 */
// #define ADC_ExternalTrigConv_T4_CC4                ((uint32_t)0x000A0000) /*!< For ADC1 and ADC2 */
// #define ADC_ExternalTrigConv_Ext_IT11_TIM8_TRGO    ((uint32_t)0x000C0000) /*!< For ADC1 and ADC2 */

// #define ADC_ExternalTrigConv_T1_CC3                ((uint32_t)0x00040000) /*!< For ADC1, ADC2 and ADC3 */
// #define ADC_ExternalTrigConv_None                  ((uint32_t)0x000E0000) /*!< For ADC1, ADC2 and ADC3 */不使用外部触发使用软件触发

// #define ADC_ExternalTrigConv_T3_CC1                ((uint32_t)0x00000000) /*!< For ADC3 only */
// #define ADC_ExternalTrigConv_T2_CC3                ((uint32_t)0x00020000) /*!< For ADC3 only */
// #define ADC_ExternalTrigConv_T8_CC1                ((uint32_t)0x00060000) /*!< For ADC3 only */
// #define ADC_ExternalTrigConv_T8_TRGO               ((uint32_t)0x00080000) /*!< For ADC3 only */
// #define ADC_ExternalTrigConv_T5_CC1                ((uint32_t)0x000A0000) /*!< For ADC3 only */
// #define ADC_ExternalTrigConv_T5_CC3     