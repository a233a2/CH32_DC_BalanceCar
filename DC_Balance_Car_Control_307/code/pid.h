/*
 * pid.h
 *
 *  Created on: 2024��5��11��
 *      Author: SJY
 */

#ifndef PID_H_
#define PID_H_


extern uint8 Flag_Qian;
extern uint8 Flag_Hou;
extern uint8 Flag_Left;
extern uint8 Flag_Right;
extern uint8 Flag_sudu; //����ң����صı���
extern uint8 Flag_Stop;
extern uint8 Flag_Show;


extern int16 Target_Speed;


void Main_PID_Progrem(void);
/*��������*/
int Vertical(float Med,float Angle,float gyro_Y);
int Velocity(int Target,int encoder_left,int encoder_right);
int Turn(int gyro_Z,int RC);


#endif /* PID_H_ */
