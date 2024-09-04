/*
 * pid_1.c
 *
 *  Created on: 2024年8月25日
 *      Author: SJY
 */
#include "zf_common_headfile.h"

float sudu_kp=-0.27;    //速度环
float sudu_ki=-0.0010;
float Target_Angle_1=0;  //达到目标速度的直立环目标角度-速度环的输出

float zhili_kp=300;    //直立环
float zhili_kd=-5 ;
int zhili_OUT;   //直立环输出
float zhili_Bias;


float zhuanxiang_kp=0.8;    //转向环
float zhuangxiang_kd=0;
int zhuanxiang_OUT;   //转向环输出
int zhuanxiang_IN;   //转向环输入-遥控决定  1000/-1000

float Target_Speed_1=0;  //目标前进速度-遥控决定
int NOW_SPEED;   //现在速度
int MOTOR1,MOTOR2;                                //电机装载变量

int Velocity_PWM_out;
float Velocity_Kp_1=-70;
float Velocity_Ki_1=-0.15;


//参数动态调整，有遥控信号时，PID柔和，直立时，PID硬。
void Canshu_Adj(void)
{
    if(Control_receivedChar=='E') //直立参数
    {
        if(zhili_Bias<=10&&zhili_Bias>=-10)
        {
            sudu_kp=-0.3;    //速度环
            sudu_ki=0;

            zhili_kp=300;    //直立环
            zhili_kd=-1;

            zhuanxiang_kp=0;    //转向环
            zhuangxiang_kd=0;
        }
        if(zhili_Bias>10&&zhili_Bias<-10)
        {
            sudu_kp=-0.3;    //速度环
            sudu_ki=0;

            zhili_kp=300;    //直立环
            zhili_kd=-1;

            zhuanxiang_kp=0;    //转向环
            zhuangxiang_kd=0;
        }

    }
    else//动态参数
    {
        sudu_kp=-0.27;    //速度环
        sudu_ki=-0.0010;

        zhili_kp=300;    //直立环
        zhili_kd=-5;

        zhuanxiang_kp=0.5;    //转向环
        zhuangxiang_kd=0;
    }
}




void Main_PID_Progrem_1(void)
{
    angle_fliter_get();    //速度以及角度获取
    M0_Angle=-Read_Speed(4);
    M1_Angle=Read_Speed(3);
    NOW_SPEED=(M0_Angle+M1_Angle)/2;

    sudu_PID();
    zhili_PID();
    Velocity_1(Target_Speed_1,M0_Angle,M1_Angle);
    zhuanxiang_PID();

    MOTOR1=zhili_OUT-Velocity_PWM_out+zhuanxiang_OUT;//左电机
    MOTOR2=zhili_OUT-Velocity_PWM_out+zhuanxiang_OUT;
    if(Angle_Y > 30 || Angle_Y < -30)
    {
        MOTOR1=MOTOR2=0;
    }
    Load(MOTOR1,MOTOR2);
}


//外环速度pid
void sudu_PID(void)
{
    static int EnC_Err_Lowout_last,Encoder_Err,EnC_Err_Lowout;
    static int Encoder_S;  //积分

    //1.计算速度偏差
    Encoder_Err=NOW_SPEED-Target_Speed_1;

    //2.对速度偏差进行低通滤波
    EnC_Err_Lowout=0.2*Encoder_Err+0.8*EnC_Err_Lowout_last;//使得波形更加平滑，滤除高频干扰，防止速度突变。
    EnC_Err_Lowout_last=EnC_Err_Lowout;//防止速度过大的影响直立环的正常工作。
    //3.对速度偏差积分，积分出位移
    Encoder_S+=EnC_Err_Lowout;
    //4.积分限幅
    if(Encoder_S<-10000) Encoder_S=-10000;
    if(Encoder_S>10000) Encoder_S=10000;

    if(Target_Speed_1==0)Encoder_S=0;//清零积分量

    //5.速度环控制输出计算
    Target_Angle_1 = sudu_kp*EnC_Err_Lowout + sudu_ki*Encoder_S;
}

/*********************
速度环PI：Kp*Ek+Ki*Ek_S
*********************/
int Velocity_1(int Target,int encoder_left,int encoder_right)
{
    static int EnC_Err_Lowout_last,Encoder_Err,EnC_Err_Lowout;
    static int Encoder_S;  //积分
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
    Velocity_PWM_out = Velocity_Kp_1*EnC_Err_Lowout + Velocity_Ki_1*Encoder_S;
    if(Angle_Y<-40||Angle_Y>40) Encoder_S=0;
    return Velocity_PWM_out;
}

//内环角度（直立pid）

void zhili_PID(void)
{
    zhili_Bias = Angle_Y - Target_Angle_1;

    zhili_OUT=zhili_kp*zhili_Bias+zhili_kd*(Gyro_Y-0);
}

//内环角度（直立pid）
void zhuanxiang_PID(void)
{
    zhuanxiang_OUT=zhuanxiang_kp*zhuanxiang_IN+zhuangxiang_kd*0;
}

void yaokong(void)
{

}
