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

extern uint8 Init_Flag; //��ʼ����־λ
extern char Input_data[50];  //���������ַ���


void BuleTooth_Test();
void Community_Init(void);


void VOFA_Test(void);



#endif /* BULETOOTH_H_ */
