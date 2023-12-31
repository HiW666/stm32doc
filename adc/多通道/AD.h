#ifndef __AD_H
#define __AD_H

void AD_Init(void);
uint16_t AD_GetValue(uint8_t ADC_Channel);//选择adc通道

#endif

// uint8_t ADC_Channel的值可以为
// #define ADC_Channel_0                               ((uint8_t)0x00)
// #define ADC_Channel_1                               ((uint8_t)0x01)
// #define ADC_Channel_2                               ((uint8_t)0x02)
// #define ADC_Channel_3                               ((uint8_t)0x03)
// #define ADC_Channel_4                               ((uint8_t)0x04)
// #define ADC_Channel_5                               ((uint8_t)0x05)
// #define ADC_Channel_6                               ((uint8_t)0x06)
// #define ADC_Channel_7                               ((uint8_t)0x07)
// #define ADC_Channel_8                               ((uint8_t)0x08)
// #define ADC_Channel_9                               ((uint8_t)0x09)
// #define ADC_Channel_10                              ((uint8_t)0x0A)
// #define ADC_Channel_11                              ((uint8_t)0x0B)
// #define ADC_Channel_12                              ((uint8_t)0x0C)
// #define ADC_Channel_13                              ((uint8_t)0x0D)
// #define ADC_Channel_14                              ((uint8_t)0x0E)
// #define ADC_Channel_15                              ((uint8_t)0x0F)
// #define ADC_Channel_16                              ((uint8_t)0x10)
// #define ADC_Channel_17                              ((uint8_t)0x11)