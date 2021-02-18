#include "bsp_general_tim.h"


extern uint16_t period1;



static void TIM1_PWMOUTPUT_Config(void)
{
//	GPIO_InitTypeDef GPIO_InitStructure; //GPIO���ã������ṹ��
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	
	RCC_APB2PeriphClockCmd(GENERAL_TIM_CLK, ENABLE); //����ʱ��
	 
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;  //TIM1_CH1 PA8
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//
//	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* �ۼ� TIM_Period�������һ�����»����ж�*/		
	TIM_TimeBaseStructure.TIM_Period = period1 - 1;       

	// �趨��ʱ��Ƶ��Ϊ=TIMxCLK/(TIM_Prescaler+1)Hz
	TIM_TimeBaseStructure.TIM_Prescaler = 168 - 1;	
	// ����ʱ�ӷ�Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	// ������ʽ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	// ��ʼ����ʱ��TIMx, x[2,3,4,5,12,13,14] 
	TIM_TimeBaseInit(GENERAL_TIM, &TIM_TimeBaseStructure);

	/*PWMģʽ����*/
	/* PWM1 Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //����ΪPWMģʽ1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
	TIM_OCInitStructure.TIM_Pulse = (period1 / DUTY_CYCLE) - 1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  	  //����ʱ������ֵС��CCR1_ValʱΪ�ߵ�ƽ
	TIM_OC1Init(GENERAL_TIM, &TIM_OCInitStructure);	 //ʹ��ͨ��1
  
	/*ʹ�ܻ���ʧ�� TIMx �� CCR1 �ϵ�Ԥװ�ؼĴ���*/
	//TIM_OC1PreloadConfig(GENERAL_TIM, TIM_OCPreload_Enable);

	TIM_SelectMasterSlaveMode(GENERAL_TIM, TIM_MasterSlaveMode_Enable);//���û������� TIMx ��/��ģʽ
	TIM_SelectOutputTrigger(TIM1, TIM_TRGOSource_Update);//ѡ�� TIMx �����¼���Ϊ�������

	TIM_ARRPreloadConfig(TIM1, ENABLE);  // ʹ�ܻ���ʧ�� TIMx �� ARR �ϵ�Ԥװ�ؼĴ��� 
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
	//TIMx_GPIO_Config();
  
  	TIM1_PWMOUTPUT_Config();
	TIM_CtrlPWMOutputs(TIM1, ENABLE);   //�߼���ʱ��һ��Ҫ���ϣ������ʹ��
	
}

/*********************************************END OF FILE**********************/
