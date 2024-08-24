/*
 * motor.h
 *
 *  Created on: 2024年8月10日
 *      Author: SJY
 */

#ifndef MOTOR_H_
#define MOTOR_H_




void Motor_Init(void);
void Load(int16_t moto1,int16_t moto2);/*赋值函数*/
void Limit(int16 motoA,int16 motoB);/*限幅函数*/
void Motor_SetSpeed(int16_t Speed);


#endif /* MOTOR_H_ */
