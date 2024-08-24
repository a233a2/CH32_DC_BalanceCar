/*
 * buletooth.c
 *
 *  Created on: 2024Äê5ÔÂ23ÈÕ
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



float data[5];
unsigned char tail[4] = {0x00, 0x00, 0x80, 0x7f};
void VOFA_Test(void)
{
    data[0] = Angle_Y;
    data[1] = Gyro_Y;
    data[2] = 0;
    data[3] = M0_Angle;
    data[4] = M1_Angle;
    uart_write_buffer(UART_2, (const uint8 *)data, sizeof(float) * 5);//DATA
    uart_write_buffer(UART_2, (const uint8 *)tail, 4);//Î²

}
