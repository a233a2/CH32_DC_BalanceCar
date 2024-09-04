/*
 * pid_1.c
 *
 *  Created on: 2024��8��25��
 *      Author: SJY
 */
#include "zf_common_headfile.h"

float sudu_kp=-0.27;    //�ٶȻ�
float sudu_ki=-0.0010;
float Target_Angle_1=0;  //�ﵽĿ���ٶȵ�ֱ����Ŀ��Ƕ�-�ٶȻ������

float zhili_kp=300;    //ֱ����
float zhili_kd=-5 ;
int zhili_OUT;   //ֱ�������
float zhili_Bias;


float zhuanxiang_kp=0.8;    //ת��
float zhuangxiang_kd=0;
int zhuanxiang_OUT;   //ת�����
int zhuanxiang_IN;   //ת������-ң�ؾ���  1000/-1000

float Target_Speed_1=0;  //Ŀ��ǰ���ٶ�-ң�ؾ���
int NOW_SPEED;   //�����ٶ�
int MOTOR1,MOTOR2;                                //���װ�ر���

int Velocity_PWM_out;
float Velocity_Kp_1=-70;
float Velocity_Ki_1=-0.15;


//������̬��������ң���ź�ʱ��PID��ͣ�ֱ��ʱ��PIDӲ��
void Canshu_Adj(void)
{
    if(Control_receivedChar=='E') //ֱ������
    {
        if(zhili_Bias<=10&&zhili_Bias>=-10)
        {
            sudu_kp=-0.3;    //�ٶȻ�
            sudu_ki=0;

            zhili_kp=300;    //ֱ����
            zhili_kd=-1;

            zhuanxiang_kp=0;    //ת��
            zhuangxiang_kd=0;
        }
        if(zhili_Bias>10&&zhili_Bias<-10)
        {
            sudu_kp=-0.3;    //�ٶȻ�
            sudu_ki=0;

            zhili_kp=300;    //ֱ����
            zhili_kd=-1;

            zhuanxiang_kp=0;    //ת��
            zhuangxiang_kd=0;
        }

    }
    else//��̬����
    {
        sudu_kp=-0.27;    //�ٶȻ�
        sudu_ki=-0.0010;

        zhili_kp=300;    //ֱ����
        zhili_kd=-5;

        zhuanxiang_kp=0.5;    //ת��
        zhuangxiang_kd=0;
    }
}




void Main_PID_Progrem_1(void)
{
    angle_fliter_get();    //�ٶ��Լ��ǶȻ�ȡ
    M0_Angle=-Read_Speed(4);
    M1_Angle=Read_Speed(3);
    NOW_SPEED=(M0_Angle+M1_Angle)/2;

    sudu_PID();
    zhili_PID();
    Velocity_1(Target_Speed_1,M0_Angle,M1_Angle);
    zhuanxiang_PID();

    MOTOR1=zhili_OUT-Velocity_PWM_out+zhuanxiang_OUT;//����
    MOTOR2=zhili_OUT-Velocity_PWM_out+zhuanxiang_OUT;
    if(Angle_Y > 30 || Angle_Y < -30)
    {
        MOTOR1=MOTOR2=0;
    }
    Load(MOTOR1,MOTOR2);
}


//�⻷�ٶ�pid
void sudu_PID(void)
{
    static int EnC_Err_Lowout_last,Encoder_Err,EnC_Err_Lowout;
    static int Encoder_S;  //����

    //1.�����ٶ�ƫ��
    Encoder_Err=NOW_SPEED-Target_Speed_1;

    //2.���ٶ�ƫ����е�ͨ�˲�
    EnC_Err_Lowout=0.2*Encoder_Err+0.8*EnC_Err_Lowout_last;//ʹ�ò��θ���ƽ�����˳���Ƶ���ţ���ֹ�ٶ�ͻ�䡣
    EnC_Err_Lowout_last=EnC_Err_Lowout;//��ֹ�ٶȹ����Ӱ��ֱ����������������
    //3.���ٶ�ƫ����֣����ֳ�λ��
    Encoder_S+=EnC_Err_Lowout;
    //4.�����޷�
    if(Encoder_S<-10000) Encoder_S=-10000;
    if(Encoder_S>10000) Encoder_S=10000;

    if(Target_Speed_1==0)Encoder_S=0;//���������

    //5.�ٶȻ������������
    Target_Angle_1 = sudu_kp*EnC_Err_Lowout + sudu_ki*Encoder_S;
}

/*********************
�ٶȻ�PI��Kp*Ek+Ki*Ek_S
*********************/
int Velocity_1(int Target,int encoder_left,int encoder_right)
{
    static int EnC_Err_Lowout_last,Encoder_Err,EnC_Err_Lowout;
    static int Encoder_S;  //����
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
    Velocity_PWM_out = Velocity_Kp_1*EnC_Err_Lowout + Velocity_Ki_1*Encoder_S;
    if(Angle_Y<-40||Angle_Y>40) Encoder_S=0;
    return Velocity_PWM_out;
}

//�ڻ��Ƕȣ�ֱ��pid��

void zhili_PID(void)
{
    zhili_Bias = Angle_Y - Target_Angle_1;

    zhili_OUT=zhili_kp*zhili_Bias+zhili_kd*(Gyro_Y-0);
}

//�ڻ��Ƕȣ�ֱ��pid��
void zhuanxiang_PID(void)
{
    zhuanxiang_OUT=zhuanxiang_kp*zhuanxiang_IN+zhuangxiang_kd*0;
}

void yaokong(void)
{

}
