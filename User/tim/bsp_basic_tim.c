#include "bsp_basic_tim.h"

 /**
  * @brief  ������ʱ�� TIMx,x[6,7]�ж����ȼ�����
  * @param  ��
  * @retval ��
  */
static void TIMx_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    // �����ж���Ϊ0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		
		// �����ж���Դ
    NVIC_InitStructure.NVIC_IRQChannel = BASIC_TIM_IRQn; 	
		// ������ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	 
	  // ���������ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


static void TIM_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	// ����TIMx_CLK,x[6,7] 
  RCC_APB1PeriphClockCmd(BASIC_TIM_CLK, ENABLE); 


  TIM_TimeBaseStructure.TIM_Period = TIM2_PRD;       
	
  TIM_TimeBaseStructure.TIM_Prescaler = 0;	
  
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	
	// ��ʼ����ʱ��TIMx, x[2,3,4,5]
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);



	TIM_SelectInputTrigger(TIM2, TIM_TS_ITR0);//ѡ�� TIMx ���봥��Դ��TIM �ڲ����� 0      
    TIM_SelectSlaveMode(TIM2,TIM_SlaveMode_External1 );// ��ͬ TIM2->SMCR|=0x07 //���ô�ģʽ�Ĵ��� 
    //   TIM2->SMCR|=0x07;  

	//���ô�ģʽ�Ĵ���       
    TIM_ITConfig(TIM2,TIM_IT_Update,DISABLE); //
	
	// �����ʱ�������жϱ�־λ
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//���TIMx ���жϴ�����λ
	
	// ������ʱ�������ж�
	TIM_ITConfig(TIM2,TIM_IT_Update,DISABLE);
	
	// ʹ�ܶ�ʱ��
	TIM_Cmd(TIM2, ENABLE);	
}

/**
  * @brief  ��ʼ��������ʱ����ʱ��1ms����һ���ж�
  * @param  ��
  * @retval ��
  */
void TIM2_Configuration(void)
{
	TIMx_NVIC_Configuration();	
  
  	TIM_Mode_Config();
}

/*********************************************END OF FILE**********************/
