#include "bsp_basic_tim.h"

 /**
  * @brief  基本定时器 TIMx,x[6,7]中断优先级配置
  * @param  无
  * @retval 无
  */
static void TIMx_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    // 设置中断组为0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		
		// 设置中断来源
    NVIC_InitStructure.NVIC_IRQChannel = BASIC_TIM_IRQn; 	
		// 设置抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	 
	  // 设置子优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


static void TIM_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	// 开启TIMx_CLK,x[6,7] 
  RCC_APB1PeriphClockCmd(BASIC_TIM_CLK, ENABLE); 


  TIM_TimeBaseStructure.TIM_Period = TIM2_PRD;       
	
  TIM_TimeBaseStructure.TIM_Prescaler = 0;	
  
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	
	// 初始化定时器TIMx, x[2,3,4,5]
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);



	TIM_SelectInputTrigger(TIM2, TIM_TS_ITR0);//选择 TIMx 输入触发源，TIM 内部触发 0      
    TIM_SelectSlaveMode(TIM2,TIM_SlaveMode_External1 );// 等同 TIM2->SMCR|=0x07 //设置从模式寄存器 
    //   TIM2->SMCR|=0x07;  

	//设置从模式寄存器       
    TIM_ITConfig(TIM2,TIM_IT_Update,DISABLE); //
	
	// 清除定时器更新中断标志位
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//清除TIMx 的中断待处理位
	
	// 开启定时器更新中断
	TIM_ITConfig(TIM2,TIM_IT_Update,DISABLE);
	
	// 使能定时器
	TIM_Cmd(TIM2, ENABLE);	
}

/**
  * @brief  初始化基本定时器定时，1ms产生一次中断
  * @param  无
  * @retval 无
  */
void TIM2_Configuration(void)
{
	TIMx_NVIC_Configuration();	
  
  	TIM_Mode_Config();
}

/*********************************************END OF FILE**********************/
