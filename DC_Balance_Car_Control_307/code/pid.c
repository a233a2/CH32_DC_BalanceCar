/*
 * pid.c
 *
 *  Created on: 2024��5��11��
 *      Author: SJY
 */
#include "zf_common_headfile.h"
#define ZHONGZHI 0          //��е��ֵ

int Med_Angle=0; //��е��ֵ��---�������޸���Ļ�е��ֵ���ɡ�
int16 Target_Speed=0; //�����ٶȣ���������---���ο����ӿڣ����ڿ���С��ǰ�����˼����ٶȡ�
int Turn_Speed=0;     //�����ٶȣ�ƫ����

uint8 Flag_Qian,Flag_Hou,Flag_Left,Flag_Right,Flag_sudu=2; //����ң����صı���
uint8 Flag_Stop=0,Flag_Show=1;

float Vertical_Kp=315;//315;      //ֱ����Kp315
float Vertical_Kd=-5;      //ֱ����Kd0

float Velocity_Kp=-75.0;//-26.3;     //�ٶȻ�Kp-23.5
float Velocity_Ki=-0.35;//-0.11;     //�ٶȻ�Ki-0.1


float Turn_Kp=0;          //ת��Kp
float Turn_Kd=0;          //ת��Kd

int16 Balance_Pwm=0,Velocity_Pwm=0,Turn_Pwm=0;  //�������

int Vertical_out,Velocity_out,Turn_out,PWM_out;//ֱ����&�ٶȻ�&ת�� ���������
int16 MOTO1,MOTO2;                                //���װ�ر���

void Main_PID_Progrem(void)
{
    angle_fliter_get();
    M0_Angle=-Read_Speed(4);
    M1_Angle=Read_Speed(3);

    Velocity_out=Velocity(Target_Speed,M0_Angle,M1_Angle); //�ٶȻ�

    Vertical_out=Vertical(Med_Angle,Angle_Y,Gyro_Y);//ֱ����

    //Turn_out=Turn(Gyro_Y,Turn_Speed);//ת��

    PWM_out=Vertical_out-Velocity_out;//�������

    MOTO1=PWM_out+Turn_out;//����
    MOTO2=PWM_out-Turn_out;//�ҵ��
    /*ƽ�⳵ˤ������*/
//    if(Gyro_Y > 35 || Gyro_Y < -35)
//        Load(0,0),Flag_Stop=1;
 //   else
    if(Angle_Y > 30 || Angle_Y < -30)
    {
        MOTO1=MOTO2=0;
    }
        Load(MOTO1,MOTO2);
}
void Control_BuleTooth(void)
{
    if (Flag_Stop==1) {Target_Speed=0;}
    if (Flag_Qian==1) {Target_Speed=20;}
    if (Flag_Hou==1) {Target_Speed=-20;}
}


/*********************
ֱ����PD��������Kp*Ek+Kd*Ek_D

��ڣ������Ƕȡ���ʵ�Ƕȡ���ʵ���ٶ�
���ڣ�ֱ�������
*********************/
int Vertical(float Med,float Angle,float gyro_Y)
{
    int PWM_out;
    float Bias;
    Bias = Angle - Med;

    PWM_out=Vertical_Kp*Bias+Vertical_Kd*(gyro_Y-0);//��1��

    return PWM_out;
}


/*********************
�ٶȻ�PI��Kp*Ek+Ki*Ek_S
*********************/
int Velocity(int Target,int encoder_left,int encoder_right)
{
    static int EnC_Err_Lowout_last,Encoder_Err,EnC_Err_Lowout;
    static int Encoder_S;  //����
    static int PWM_out;
    //1.�����ٶ�ƫ��
    Encoder_Err=((encoder_left+encoder_right)-Target);//��ȥ���--�ҵ���⣺�ܹ����ٶ�Ϊ"0"�ĽǶȣ����ǻ�е��ֵ��
    //2.���ٶ�ƫ����е�ͨ�˲�

    EnC_Err_Lowout=0.3*Encoder_Err+0.7*EnC_Err_Lowout_last;//ʹ�ò��θ���ƽ�����˳���Ƶ���ţ���ֹ�ٶ�ͻ�䡣
    EnC_Err_Lowout_last=EnC_Err_Lowout;//��ֹ�ٶȹ����Ӱ��ֱ����������������
    //3.���ٶ�ƫ����֣����ֳ�λ��
    Encoder_S+=EnC_Err_Lowout;
    //4.�����޷�
    if(Encoder_S<-10000) Encoder_S=-10000;
    if(Encoder_S>10000) Encoder_S=10000;

    //if(stop==1)Encoder_S=0,stop=0;//���������

    //5.�ٶȻ������������
    PWM_out = Velocity_Kp*EnC_Err_Lowout + Velocity_Ki*Encoder_S;
    if(Angle_Y<-40||Angle_Y>40) Encoder_S=0;
    return PWM_out;
}

//*********************
//ת�򻷣�ϵ��*Z����ٶ�+ϵ��*ң������
//*********************/
int Turn(int gyro_Z,int RC)
{
    int PWM_out;
    //�ⲻ��һ���ϸ��PD��������Kd��Ե���ת���Լ������Kp��Ե���ң�ص�ת��
    PWM_out=Turn_Kd*gyro_Z + Turn_Kp*RC;
    return PWM_out;
}


//�������ܣ�����ֵ����
//��ڲ�����int
//����  ֵ��unsigned int
int myabs(int a)
{
    int temp;
    if(a<0)  temp=-a;
    else temp=a;
    return temp;
}



