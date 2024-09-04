#include "zf_common_headfile.h"

int main(void)
{
    clock_init(SYSTEM_CLOCK_144M);      // 初始化芯片时钟 工作频率为 120MHz
    debug_init();                       // 务必保留，本函数用于初始化MPU 时钟 调试串口

    // 此处编写用户代码 例如外设初始化代码等
//    ips114_init();
    Beep_Init();
    Motor_Init();
    Encoder_TIM3_Init();
    Encoder_TIM4_Init();
    mpu6050_init();

    Community_Init();  //vofa用

    //Key_Init();

    Control_Community_Init();


    Y_angle_ZeroOFFset_get();

    ADC_Vol_get_Init();

    pit_ms_init(TIM1_PIT, 1);  //pid循环运算程序
    pit_ms_init(TIM5_PIT, 20);  //调试以及控制
    Beep_Ring_500MS();

//     初始化GPIO E2 E9为推挽输出 默认输出低电平
//    gpio_init(E2, GPO, 1, GPO_PUSH_PULL);
//    gpio_init(E3, GPO, 1, GPO_PUSH_PULL);


    // 此处编写用户代码 例如外设初始化代码等
//    ips114_show_string(0,0,"Angle_Y:");
//    ips114_show_string(0,30,"Gryo_Y:");
//    ips114_show_string(0,50,"Speed_M0:");
//    ips114_show_string(0,70,"Speed_M1:");
    while(1)
    {

    }
}
