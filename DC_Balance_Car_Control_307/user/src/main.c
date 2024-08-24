/*********************************************************************************************************************
* CH32V307VCT6 Opensourec Library ����CH32V307VCT6 ��Դ�⣩��һ�����ڹٷ� SDK �ӿڵĵ�������Դ��
* Copyright (c) 2022 SEEKFREE ��ɿƼ�
*
* ���ļ���CH32V307VCT6 ��Դ���һ����
*
* CH32V307VCT6 ��Դ�� ��������
* �����Ը��������������ᷢ���� GPL��GNU General Public License���� GNUͨ�ù������֤��������
* �� GPL �ĵ�3�棨�� GPL3.0������ѡ��ģ��κκ����İ汾�����·�����/���޸���
*
* ����Դ��ķ�����ϣ�����ܷ������ã�����δ�������κεı�֤
* ����û�������������Ի��ʺ��ض���;�ı�֤
* ����ϸ����μ� GPL
*
* ��Ӧ�����յ�����Դ���ͬʱ�յ�һ�� GPL �ĸ���
* ���û�У������<https://www.gnu.org/licenses/>
*
* ����ע����
* ����Դ��ʹ�� GPL3.0 ��Դ���֤Э�� �����������Ϊ���İ汾
* �������Ӣ�İ��� libraries/doc �ļ����µ� GPL3_permission_statement.txt �ļ���
* ���֤������ libraries �ļ����� �����ļ����µ� LICENSE �ļ�
* ��ӭ��λʹ�ò����������� ���޸�����ʱ���뱣����ɿƼ��İ�Ȩ����������������
*
* �ļ�����          main
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          MounRiver Studio V1.8.1
* ����ƽ̨          CH32V307VCT6
* ��������          https://seekfree.taobao.com/
*
* �޸ļ�¼
* ����                                      ����                             ��ע
* 2022-09-15        ��W            first version
********************************************************************************************************************/
#include "zf_common_headfile.h"

// *************************** ���̲���˵�� ***************************
// 1.���İ���¼��ɱ����̣�����ϵ�
//
// 2.���Կ������İ�����ɫ LED ��˸
//
// 3.����ͨ�����ߵ��Եķ�ʽ�鿴gpio_status���� ���鿴��ǰD0���ŵ�״̬


int main(void)
{
    clock_init(SYSTEM_CLOCK_144M);      // ��ʼ��оƬʱ�� ����Ƶ��Ϊ 120MHz
    debug_init();                       // ��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���

    // �˴���д�û����� ���������ʼ�������
    ips114_init();

    Motor_Init();
    Encoder_TIM3_Init();
    Encoder_TIM4_Init();
    mpu6050_init();

    Community_Init();

   Beep_Init();

//    Key_Init();



    Y_angle_ZeroOFFset_get();

    uart_rx_interrupt(UART_1, ENABLE);//��ȡ��������

    pit_ms_init(TIM1_PIT, 10);

//     ��ʼ��GPIO E2 E9Ϊ������� Ĭ������͵�ƽ
    gpio_init(E2, GPO, 1, GPO_PUSH_PULL);
    gpio_init(E3, GPO, 1, GPO_PUSH_PULL);

    Beep_Ring_500MS();
    // �˴���д�û����� ���������ʼ�������

    while(1)
    {
    if(M0_Angle>5)gpio_set_level(E2,0);
    else if(M0_Angle<-5)gpio_set_level(E3,0);
    else
    {
        gpio_set_level(E2,1);
        gpio_set_level(E3,1);
    }
    }
}






