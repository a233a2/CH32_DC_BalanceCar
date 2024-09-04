/*
 * buletooth.h
 *
 *  Created on: 2024年5月23日
 *      Author: SJY
 */

#ifndef BULETOOTH_H_
#define BULETOOTH_H_

extern int16 M0_Angle;//编码器 左电机
extern int16 M1_Angle;//编码器 右电机

extern uint8_t Control_receivedChar;    //接收遥控数据

void BuleTooth_Test();
void Community_Init(void);


void VOFA_Test(void);
void Control_Read(void);
void UART_Control_Read(void);
void Control_Community_Init(void);
#endif /* BULETOOTH_H_ */
