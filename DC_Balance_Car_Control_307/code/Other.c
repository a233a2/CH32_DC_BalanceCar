/*
 * Other.c
 *LED初始化  控制按键  灯光预置效果 菜单等
 *  Created on: 2024年5月11日
 *      Author: SJY
 */


#include "zf_common_headfile.h"

void Beep_Init(void)
{
    gpio_init(E4, GPO, 0, GPIO_PIN_CONFIG);

}

void Beep_Ring_500MS(void)
{
    gpio_set_level(E4, 1);
    system_delay_ms(200);
    gpio_set_level(E4, 0);
}
void Key_Init(void)
{
    gpio_init(C4, GPI, 1, GPIO_INT_CONFIG);
    gpio_init(C5, GPI, 1, GPIO_INT_CONFIG);
}


void Beep_Test(void)
{
    if(gpio_get_level(C5)==0)
    {
        Beep_Ring_500MS();
    }
}

void ADC_Vol_get_Init(void)
{
    adc_init(ADC1_IN4_A4,ADC_12BIT);
}

float ADC_Vol;
void ADC_Vol_get(void)
{
    float Vol;
    Vol=adc_mean_filter_convert(ADC1_IN4_A4,5);
    ADC_Vol=Vol*15.7/4096;
}
