#include "bsp_general_tim.h"


extern uint16_t period;
extern uint16_t prescaler;


static void TIMx_GPIO_Config(void) 
{
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*������ص�GPIO����ʱ��*/
	RCC_AHB1PeriphClockCmd (GENERAL_OCPWM_GPIO_CLK, ENABLE); 
  /* ��ʱ��ͨ�����Ÿ��� */
	GPIO_PinAFConfig(GENERAL_OCPWM_GPIO_PORT,GENERAL_OCPWM_PINSOURCE,GENERAL_OCPWM_AF); 
  
	/* ��ʱ��ͨ���������� */															   
	GPIO_InitStructure.GPIO_Pin = GENERAL_OCPWM_PIN;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;  //���ù���ģʽ  
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
	GPIO_Init(GENERAL_OCPWM_GPIO_PORT, &GPIO_InitStructure);
}



static void TIM_PWMOUTPUT_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	// ����TIMx_CLK,x[2,3,4,5,12,13,14] 
	RCC_APB1PeriphClockCmd(GENERAL_TIM_CLK, ENABLE); 

	/* �ۼ� TIM_Period�������һ�����»����ж�*/		
	//����ʱ����0������8399����Ϊ8400�Σ�Ϊһ����ʱ����
	TIM_TimeBaseStructure.TIM_Period = period-1;       

	// ͨ�ÿ��ƶ�ʱ��ʱ��ԴTIMxCLK = HCLK/2=84MHz 
	// �趨��ʱ��Ƶ��Ϊ=TIMxCLK/(TIM_Prescaler+1)=100KHz
	TIM_TimeBaseStructure.TIM_Prescaler = prescaler-1;	
	// ����ʱ�ӷ�Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	// ������ʽ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;

	// ��ʼ����ʱ��TIMx, x[2,3,4,5,12,13,14] 
	TIM_TimeBaseInit(GENERAL_TIM, &TIM_TimeBaseStructure);

	/*PWMģʽ����*/
	/* PWM1 Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //����ΪPWMģʽ1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
	TIM_OCInitStructure.TIM_Pulse = (period / DUTY_CYCLE) - 1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  	  //����ʱ������ֵС��CCR1_ValʱΪ�ߵ�ƽ
	TIM_OC1Init(GENERAL_TIM, &TIM_OCInitStructure);	 //ʹ��ͨ��1
  
	/*ʹ��ͨ��1����*/
	TIM_OC1PreloadConfig(GENERAL_TIM, TIM_OCPreload_Enable);
	
	// ʹ�ܶ�ʱ��
	TIM_Cmd(GENERAL_TIM, ENABLE);	
}

/**
  * @brief  ��ʼ������ͨ�ö�ʱ��
  * @param  ��
  * @retval ��
  */
void TIMx_PWMConfiguration(void)
{
	TIMx_GPIO_Config();
  
  	TIM_PWMOUTPUT_Config();
}

/*********************************************END OF FILE**********************/
