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

extern uint8 Init_Flag; //初始化标志位
extern char Input_data[50];  //接收数据字符串


void BuleTooth_Test();
void Community_Init(void);


void VOFA_Test(void);



#endif /* BULETOOTH_H_ */
