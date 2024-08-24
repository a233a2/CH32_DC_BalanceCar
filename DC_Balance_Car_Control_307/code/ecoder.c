/*
 * ecoder.c
 *
 *  Created on: 2024��8��10��
 *      Author: SJY
 */
#include "zf_common_headfile.h"
#include <stdlib.h>

void Encoder_TIM3_Init(void)   //��ʱ��3��������ʼ��
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���
    TIM_TimeBaseInitStructure.TIM_Period = 65535;    //ARR(0~65535)      1s
    TIM_TimeBaseInitStructure.TIM_Prescaler = 0;  //PSC(0~65535)      ��ʱƵ��=72M/(PSC+1)/(ARR+1)
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;   //�ظ����������߼����������У�
    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);

    TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);//���ñ�����ģʽ

    TIM_ICInitTypeDef TIM_ICInitStructure;
    TIM_ICStructInit(&TIM_ICInitStructure);//��ʼ�����벶��
    TIM_ICInitStructure.TIM_ICFilter=10;
    TIM_ICInit(TIM3,&TIM_ICInitStructure);

    TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);//������������жϱ�־λ
    TIM_SetCounter(TIM3,0);//���㶨ʱ������ֵ

    TIM_Cmd(TIM3,ENABLE);
}

void Encoder_TIM4_Init(void)    //��ʱ��4��������ʼ��
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);

    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���
    TIM_TimeBaseInitStructure.TIM_Period = 65535;    //ARR(0~65535)      1s
    TIM_TimeBaseInitStructure.TIM_Prescaler = 0;  //PSC(0~65535)      ��ʱƵ��=72M/(PSC+1)/(ARR+1)
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;   //�ظ����������߼����������У�
    TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);

    TIM_EncoderInterfaceConfig(TIM4,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);//���ñ�����ģʽ

    TIM_ICInitTypeDef TIM_ICInitStructure;
    TIM_ICStructInit(&TIM_ICInitStructure);//��ʼ�����벶��
    TIM_ICInitStructure.TIM_ICFilter=10;
    TIM_ICInit(TIM4,&TIM_ICInitStructure);

    TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);//������������жϱ�־λ
    TIM_SetCounter(TIM4,0);//���㶨ʱ������ֵ

    TIM_Cmd(TIM4,ENABLE);
}

/**********************
������
�ٶȶ�ȡ����
��ڲ�������ʱ��
**********************/
int Read_Speed(int TIMx)
{
    int value_1;
    switch(TIMx)
    {
        /*             1.�ɼ��������ļ���ֵ������ 2.����ʱ���ļ���ֵ���㡣*/
        case 3:value_1=(short)TIM_GetCounter(TIM3);TIM_SetCounter(TIM3,0);break;
        case 4:value_1=(short)TIM_GetCounter(TIM4);TIM_SetCounter(TIM4,0);break;
        default:value_1=0;
    }
    return value_1;
}

void TIM3_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM3,TIM_IT_Update) == SET)
    {

        TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
    }
}

void TIM4_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM3,TIM_IT_Update) == SET)
    {

        TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
    }
}


