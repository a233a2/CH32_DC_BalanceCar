/*
 * motor.c
 *
 *  Created on: 2024年8月10日
 *      Author: SJY
 */
#include "zf_common_headfile.h"
#define MOTOR_PWM_FREC 7000

void Motor_Init(void)
{
    gpio_init(A0, GPO, 0, GPIO_PIN_CONFIG);//
    gpio_init(A1, GPO, 0, GPIO_PIN_CONFIG);//

    gpio_init(B12, GPO, 0, GPIO_PIN_CONFIG);//BIN2
    gpio_init(B13, GPO, 0, GPIO_PIN_CONFIG);//BIN1
    gpio_init(B14, GPO, 0, GPIO_PIN_CONFIG);//AIN1
    gpio_init(B15, GPO, 0, GPIO_PIN_CONFIG);//AIN2

    pwm_init(TIM2_PWM_MAP0_CH1_A0, MOTOR_PWM_FREC, 0);  //17KHZ DUTY_MAX=10000
    pwm_init(TIM2_PWM_MAP0_CH2_A1, MOTOR_PWM_FREC, 0);
    pwm_set_freq(TIM2_PWM_MAP0_CH1_A0, MOTOR_PWM_FREC, 0);
    pwm_set_freq(TIM2_PWM_MAP0_CH2_A1, MOTOR_PWM_FREC, 0);

}
/*赋值函数*/
/*限幅函数*/
#define PWM_MAX 7000
#define PWM_MIN -7000
void Load(int16_t moto1,int16_t moto2)
{
    if(moto1>PWM_MAX)moto1=PWM_MAX;
    if(moto1<PWM_MIN)moto1=PWM_MIN;

    if(moto2>PWM_MAX)moto2=PWM_MAX;
    if(moto2<PWM_MIN)moto2=PWM_MIN;


    if(moto1 >= 0)
    {
        gpio_set_level(B14, 1);
        gpio_set_level(B15, 0);
        pwm_set_duty(TIM2_PWM_MAP0_CH1_A0,moto1);      //运行过程更改CCR
//        TIM_SetCompare1(TIM1,moto1);      //运行过程更改CCR
    }
    else if(moto1 < 0)
    {
        gpio_set_level(B14, 0);
        gpio_set_level(B15, 1);
        pwm_set_duty(TIM2_PWM_MAP0_CH1_A0,-moto1);//moto1是负数，PWM_SetCompare3函数需要传入正数，所以加负号。
//        TIM_SetCompare1(TIM1,-moto1);      //运行过程更改CCR
    }

    if(moto2 >= 0)
    {
        gpio_set_level(B13, 0);
        gpio_set_level(B12, 1);
        pwm_set_duty(TIM2_PWM_MAP0_CH2_A1,moto2);
//        TIM_SetCompare4(TIM1,moto2);      //运行过程更改CCR
    }
    else if(moto2 < 0)
    {
        gpio_set_level(B13, 1);
        gpio_set_level(B12, 0);
        pwm_set_duty(TIM2_PWM_MAP0_CH2_A1,-moto2);
//        TIM_SetCompare4(TIM1,-moto2);      //运行过程更改CCR
    }

}


void PWM_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA  | RCC_APB2Periph_AFIO,ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;//
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    TIM_InternalClockConfig(TIM1);       //内部时钟

    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数
    TIM_TimeBaseInitStructure.TIM_Period =  7200- 1;    //ARR(0~65535)       1KHz
    TIM_TimeBaseInitStructure.TIM_Prescaler = 1 - 1;  //PSC(0~65535)      定时频率=72M/(PSC+1)/(ARR+1)
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;   //重复计数器（高级计数器特有）
    TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStructure);

    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCStructInit(&TIM_OCInitStructure);   //结构体赋初始值
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;    //CCR     占空比=CCR/(ARR+1)，分辨率=1/(ARR+1)

    TIM_OC1Init(TIM1,&TIM_OCInitStructure);   //初始化通道
    TIM_OC4Init(TIM1,&TIM_OCInitStructure);   //初始化通道

    //控制波形是立即生效还是定时器发生下一次更新事件时被更新的
    //Enable:下一次更新事件时被更新
    //Disable:立即生效
    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
    TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);

    TIM_Cmd(TIM1,ENABLE);     //使能TIM1的外设

    TIM_CtrlPWMOutputs(TIM1,ENABLE);        //MOE 主输出使能,高级定时器必须开启这个
}


