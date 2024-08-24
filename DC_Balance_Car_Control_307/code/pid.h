/*
 * pid.h
 *
 *  Created on: 2024年5月11日
 *      Author: SJY
 */

#ifndef PID_H_
#define PID_H_


extern uint8 Flag_Qian;
extern uint8 Flag_Hou;
extern uint8 Flag_Left;
extern uint8 Flag_Right;
extern uint8 Flag_sudu; //蓝牙遥控相关的变量
extern uint8 Flag_Stop;
extern uint8 Flag_Show;


extern int16 Target_Speed;


void Main_PID_Progrem(void);
/*函数声明*/
int Vertical(float Med,float Angle,float gyro_Y);
int Velocity(int Target,int encoder_left,int encoder_right);
int Turn(int gyro_Z,int RC);


#endif /* PID_H_ */
