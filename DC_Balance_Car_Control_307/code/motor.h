/*
 * motor.h
 *
 *  Created on: 2024��8��10��
 *      Author: SJY
 */

#ifndef MOTOR_H_
#define MOTOR_H_




void Motor_Init(void);
void Load(int16_t moto1,int16_t moto2);/*��ֵ����*/
void Limit(int16 motoA,int16 motoB);/*�޷�����*/
void Motor_SetSpeed(int16_t Speed);


#endif /* MOTOR_H_ */
