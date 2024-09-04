/*
 * buletooth.c
 *
 *  Created on: 2024年5月23日
 *      Author: SJY
 */
#include "zf_common_headfile.h"
#include <stdlib.h>
#include "math.h"


int16 M0_Angle;
int16 M1_Angle;


void BuleTooth_Test(void)
{
    uart_write_string(UART_1,(const char *)"12345");
    system_delay_ms(100);
}

void Community_Init(void)
{
    uart_init(UART_2, 115200, UART2_MAP0_TX_A2, UART2_MAP0_RX_A3);
}

void Control_Community_Init(void)
{
    uart_init(UART_3, 9600, UART3_MAP0_TX_B10, UART3_MAP0_RX_B11);
}

uint8_t Control_receivedChar;    //接收遥控数据
// A前进，B后退
void UART_Control_Read(void)
{
    Control_receivedChar='E';
    uart_query_byte(UART_3, &Control_receivedChar);
}

//遥控数据解析，将收到的数据转化为目标速度
void Control_Read(void)
{

    if(Control_receivedChar=='E') Target_Speed_1=0;   //停止
    if(Control_receivedChar=='A') Target_Speed_1=10;  //前进
    if(Control_receivedChar=='B') Target_Speed_1=-10; //后退
    if(Control_receivedChar=='C') zhuanxiang_IN=1000;   //左转
    if(Control_receivedChar=='D') zhuanxiang_IN=-1000;   //右转
}



float data[9];
unsigned char tail[4] = {0x00, 0x00, 0x80, 0x7f};
void VOFA_Test(void)
{
    data[0] = Angle_Y;
    data[1] = Gyro_Y;
    data[2] = M0_Angle;
    data[3] = M1_Angle;
    data[4] = Target_Angle_1;
    data[5] = Target_Speed_1;
    data[6] = MOTOR1;
    data[7] = MOTOR2;
    data[8] = ADC_Vol;
    uart_write_buffer(UART_2, (const uint8 *)data, sizeof(float) * 9);//DATA
    uart_write_buffer(UART_2, (const uint8 *)tail, 4);//尾

}
