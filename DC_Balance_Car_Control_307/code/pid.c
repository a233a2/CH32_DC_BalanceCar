/*
 * pid.c
 *
 *  Created on: 2024年5月11日
 *      Author: SJY
 */
#include "zf_common_headfile.h"
#define ZHONGZHI 0          //机械中值

int Med_Angle=0; //机械中值。---在这里修改你的机械中值即可。
int16 Target_Speed=0; //期望速度（俯仰）。---二次开发接口，用于控制小车前进后退及其速度。
int Turn_Speed=0;     //期望速度（偏航）

uint8 Flag_Qian,Flag_Hou,Flag_Left,Flag_Right,Flag_sudu=2; //蓝牙遥控相关的变量
uint8 Flag_Stop=0,Flag_Show=1;

float Vertical_Kp=315;//315;      //直立环Kp315
float Vertical_Kd=-5;      //直立环Kd0

float Velocity_Kp=-75.0;//-26.3;     //速度环Kp-23.5
float Velocity_Ki=-0.35;//-0.11;     //速度环Ki-0.1


float Turn_Kp=0;          //转向环Kp
float Turn_Kd=0;          //转向环Kd

int16 Balance_Pwm=0,Velocity_Pwm=0,Turn_Pwm=0;  //三环输出

int Vertical_out,Velocity_out,Turn_out,PWM_out;//直立环&速度环&转向环 的输出变量
int16 MOTO1,MOTO2;                                //电机装载变量

void Main_PID_Progrem(void)
{
    angle_fliter_get();
    M0_Angle=-Read_Speed(4);
    M1_Angle=Read_Speed(3);

    Velocity_out=Velocity(Target_Speed,M0_Angle,M1_Angle); //速度环

    Vertical_out=Vertical(Med_Angle,Angle_Y,Gyro_Y);//直立环

    //Turn_out=Turn(Gyro_Y,Turn_Speed);//转向环

    PWM_out=Vertical_out-Velocity_out;//最终输出

    MOTO1=PWM_out+Turn_out;//左电机
    MOTO2=PWM_out-Turn_out;//右电机
    /*平衡车摔倒保护*/
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
直立环PD控制器：Kp*Ek+Kd*Ek_D

入口：期望角度、真实角度、真实角速度
出口：直立环输出
*********************/
int Vertical(float Med,float Angle,float gyro_Y)
{
    int PWM_out;
    float Bias;
    Bias = Angle - Med;

    PWM_out=Vertical_Kp*Bias+Vertical_Kd*(gyro_Y-0);//【1】

    return PWM_out;
}


/*********************
速度环PI：Kp*Ek+Ki*Ek_S
*********************/
int Velocity(int Target,int encoder_left,int encoder_right)
{
    static int EnC_Err_Lowout_last,Encoder_Err,EnC_Err_Lowout;
    static int Encoder_S;  //积分
    static int PWM_out;
    //1.计算速度偏差
    Encoder_Err=((encoder_left+encoder_right)-Target);//舍去误差--我的理解：能够让速度为"0"的角度，就是机械中值。
    //2.对速度偏差进行低通滤波

    EnC_Err_Lowout=0.3*Encoder_Err+0.7*EnC_Err_Lowout_last;//使得波形更加平滑，滤除高频干扰，防止速度突变。
    EnC_Err_Lowout_last=EnC_Err_Lowout;//防止速度过大的影响直立环的正常工作。
    //3.对速度偏差积分，积分出位移
    Encoder_S+=EnC_Err_Lowout;
    //4.积分限幅
    if(Encoder_S<-10000) Encoder_S=-10000;
    if(Encoder_S>10000) Encoder_S=10000;

    //if(stop==1)Encoder_S=0,stop=0;//清零积分量

    //5.速度环控制输出计算
    PWM_out = Velocity_Kp*EnC_Err_Lowout + Velocity_Ki*Encoder_S;
    if(Angle_Y<-40||Angle_Y>40) Encoder_S=0;
    return PWM_out;
}

//*********************
//转向环：系数*Z轴角速度+系数*遥控数据
//*********************/
int Turn(int gyro_Z,int RC)
{
    int PWM_out;
    //这不是一个严格的PD控制器，Kd针对的是转向的约束，但Kp针对的是遥控的转向。
    PWM_out=Turn_Kd*gyro_Z + Turn_Kp*RC;
    return PWM_out;
}


//函数功能：绝对值函数
//入口参数：int
//返回  值：unsigned int
int myabs(int a)
{
    int temp;
    if(a<0)  temp=-a;
    else temp=a;
    return temp;
}



