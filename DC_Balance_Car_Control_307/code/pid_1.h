/*
 * pid_1.h
 *
 *  Created on: 2024年8月25日
 *      Author: SJY
 */

#ifndef PID_1_H_
#define PID_1_H_

extern float Target_Angle_1;  //达到目标速度的直立环目标角度-速度环的输出
extern float Target_Speed_1;  //目标前进速度-遥控决定
extern int zhuanxiang_IN;   //转向环输入-遥控决定
extern int MOTOR1;
extern int MOTOR2;

void Main_PID_Progrem_1(void);
void sudu_PID(void);
void zhili_PID(void);
void zhuanxiang_PID(void);
void yaokong(void);

int Velocity_1(int Target,int encoder_left,int encoder_right);

void Canshu_Adj(void);
#endif /* PID_1_H_ */
