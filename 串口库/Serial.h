#ifndef __SERIAL_H
#define __SERIAL_H

#include <stdio.h>

void Serial_Init(void);//串口初始化
void Serial_SendByte(uint8_t Byte);
void Serial_SendArray(uint8_t *Array, uint16_t Length);
void Serial_SendString(char *String);
void Serial_SendNumber(uint32_t Number, uint8_t Length);//输出数字
void Serial_Printf(char *format, ...);//输出文字

uint8_t Serial_GetRxFlag(void);
uint8_t Serial_GetRxData(void);//读取串口参数

#endif
