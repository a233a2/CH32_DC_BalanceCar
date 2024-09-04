#include "zf_common_headfile.h"

int main(void)
{
    clock_init(SYSTEM_CLOCK_144M);      // ��ʼ��оƬʱ�� ����Ƶ��Ϊ 120MHz
    debug_init();                       // ��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���

    // �˴���д�û����� ���������ʼ�������
//    ips114_init();
    Beep_Init();
    Motor_Init();
    Encoder_TIM3_Init();
    Encoder_TIM4_Init();
    mpu6050_init();

    Community_Init();  //vofa��

    //Key_Init();

    Control_Community_Init();


    Y_angle_ZeroOFFset_get();

    ADC_Vol_get_Init();

    pit_ms_init(TIM1_PIT, 1);  //pidѭ���������
    pit_ms_init(TIM5_PIT, 20);  //�����Լ�����
    Beep_Ring_500MS();

//     ��ʼ��GPIO E2 E9Ϊ������� Ĭ������͵�ƽ
//    gpio_init(E2, GPO, 1, GPO_PUSH_PULL);
//    gpio_init(E3, GPO, 1, GPO_PUSH_PULL);


    // �˴���д�û����� ���������ʼ�������
//    ips114_show_string(0,0,"Angle_Y:");
//    ips114_show_string(0,30,"Gryo_Y:");
//    ips114_show_string(0,50,"Speed_M0:");
//    ips114_show_string(0,70,"Speed_M1:");
    while(1)
    {

    }
}
