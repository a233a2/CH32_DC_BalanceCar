#include "zf_common_headfile.h"

float Angle_Y=0;  //主要！前后角度
float Angle_Y_zero=0;//零飘

float Gyro_Y=0;  //主要！前后角度
float Gyro_Y_zero=0;//零飘

float Angle_Z=0;  //左右角度
//float Angle_Z_zero=0;//零飘

void angle_fliter_get(void)
{
    Angle_Y=0;
    for (int i = 0; i < 10; i++)
    {
        mpu6050_get_acc();//角度
        mpu6050_get_gyro();//加速度
        Angle_Y += mpu6050_acc_x;
        Gyro_Y += mpu6050_gyro_y;
    }
    Angle_Y=Angle_Y/1000.0-Angle_Y_zero;
    Gyro_Y=Gyro_Y/100-Gyro_Y_zero;
}
//获取零飘值
void Y_angle_ZeroOFFset_get(void)
{

    for (int i = 0; i < 10; i++)
    {
        mpu6050_get_acc();//角度
        mpu6050_get_gyro();//加速度
        Angle_Y_zero+=mpu6050_acc_x;
        Gyro_Y_zero+=mpu6050_gyro_y;

        //systick_delay(2*1000);//2ms
    }
    Angle_Y_zero=Angle_Y_zero/1000.0;
    Gyro_Y_zero=Gyro_Y_zero/100.0;
}
