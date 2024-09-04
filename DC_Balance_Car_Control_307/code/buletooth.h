/*
 * buletooth.h
 *
 *  Created on: 2024��5��23��
 *      Author: SJY
 */

#ifndef BULETOOTH_H_
#define BULETOOTH_H_

extern int16 M0_Angle;//������ ����
extern int16 M1_Angle;//������ �ҵ��

extern uint8_t Control_receivedChar;    //����ң������

void BuleTooth_Test();
void Community_Init(void);


void VOFA_Test(void);
void Control_Read(void);
void UART_Control_Read(void);
void Control_Community_Init(void);
#endif /* BULETOOTH_H_ */
