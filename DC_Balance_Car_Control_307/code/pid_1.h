/*
 * pid_1.h
 *
 *  Created on: 2024��8��25��
 *      Author: SJY
 */

#ifndef PID_1_H_
#define PID_1_H_

extern float Target_Angle_1;  //�ﵽĿ���ٶȵ�ֱ����Ŀ��Ƕ�-�ٶȻ������
extern float Target_Speed_1;  //Ŀ��ǰ���ٶ�-ң�ؾ���
extern int zhuanxiang_IN;   //ת������-ң�ؾ���
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
