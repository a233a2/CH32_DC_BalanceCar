/*
 * motor.c
 *
 *  Created on: 2024��8��10��
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
/*��ֵ����*/
/*�޷�����*/
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
        pwm_set_duty(TIM2_PWM_MAP0_CH1_A0,moto1);      //���й��̸���CCR
//        TIM_SetCompare1(TIM1,moto1);      //���й��̸���CCR
    }
    else if(moto1 < 0)
    {
        gpio_set_level(B14, 0);
        gpio_set_level(B15, 1);
        pwm_set_duty(TIM2_PWM_MAP0_CH1_A0,-moto1);//moto1�Ǹ�����PWM_SetCompare3������Ҫ�������������ԼӸ��š�
//        TIM_SetCompare1(TIM1,-moto1);      //���й��̸���CCR
    }

    if(moto2 >= 0)
    {
        gpio_set_level(B13, 0);
        gpio_set_level(B12, 1);
        pwm_set_duty(TIM2_PWM_MAP0_CH2_A1,moto2);
//        TIM_SetCompare4(TIM1,moto2);      //���й��̸���CCR
    }
    else if(moto2 < 0)
    {
        gpio_set_level(B13, 1);
        gpio_set_level(B12, 0);
        pwm_set_duty(TIM2_PWM_MAP0_CH2_A1,-moto2);
//        TIM_SetCompare4(TIM1,-moto2);      //���й��̸���CCR
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

    TIM_InternalClockConfig(TIM1);       //�ڲ�ʱ��

    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���
    TIM_TimeBaseInitStructure.TIM_Period =  7200- 1;    //ARR(0~65535)       1KHz
    TIM_TimeBaseInitStructure.TIM_Prescaler = 1 - 1;  //PSC(0~65535)      ��ʱƵ��=72M/(PSC+1)/(ARR+1)
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;   //�ظ����������߼����������У�
    TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStructure);

    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCStructInit(&TIM_OCInitStructure);   //�ṹ�帳��ʼֵ
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;    //CCR     ռ�ձ�=CCR/(ARR+1)���ֱ���=1/(ARR+1)

    TIM_OC1Init(TIM1,&TIM_OCInitStructure);   //��ʼ��ͨ��
    TIM_OC4Init(TIM1,&TIM_OCInitStructure);   //��ʼ��ͨ��

    //���Ʋ�����������Ч���Ƕ�ʱ��������һ�θ����¼�ʱ�����µ�
    //Enable:��һ�θ����¼�ʱ������
    //Disable:������Ч
    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
    TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);

    TIM_Cmd(TIM1,ENABLE);     //ʹ��TIM1������

    TIM_CtrlPWMOutputs(TIM1,ENABLE);        //MOE �����ʹ��,�߼���ʱ�����뿪�����
}


