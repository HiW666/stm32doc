#ifndef __MOTOR_H
#define __MOTOR_H

void Motor_Init(void);//初始化直流电机
void Motor_SetSpeed(int8_t Speed);//电机转数（15到115可以用负数来表示反转）

#endif
