#include "bsp_general_tim.h"


extern uint16_t period1;
//extern uint16_t prescaler;

#if 0
static void TIMx_GPIO_Config(void) 
{
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*开启相关的GPIO外设时钟*/
	RCC_AHB1PeriphClockCmd (GENERAL_OCPWM_GPIO_CLK, ENABLE); 
  /* 定时器通道引脚复用 */
	GPIO_PinAFConfig(GENERAL_OCPWM_GPIO_PORT,GENERAL_OCPWM_PINSOURCE,GENERAL_OCPWM_AF); 
  
	/* 定时器通道引脚配置 */															   
	GPIO_InitStructure.GPIO_Pin = GENERAL_OCPWM_PIN;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;  //复用功能模式  
	GPIO_InitStructure.GPIO_OType = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
	GPIO_Init(GENERAL_OCPWM_GPIO_PORT, &GPIO_InitStructure);
}
#endif


static void TIM1_PWMOUTPUT_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; //GPIO设置，创建结构体
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	
	RCC_APB2PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_APB2Periph_TIM1 , ENABLE); //开启时钟
	 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;  //TIM1_CH1 PA8
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* 累计 TIM_Period个后产生一个更新或者中断*/		
	TIM_TimeBaseStructure.TIM_Period = period1-1;       

	// 设定定时器频率为=TIMxCLK/(TIM_Prescaler+1)Hz
	TIM_TimeBaseStructure.TIM_Prescaler = 84-1;	
	// 采样时钟分频
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	// 计数方式
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;

	// 初始化定时器TIMx, x[2,3,4,5,12,13,14] 
	TIM_TimeBaseInit(GENERAL_TIM, &TIM_TimeBaseStructure);

	/*PWM模式配置*/
	/* PWM1 Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //配置为PWM模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
	TIM_OCInitStructure.TIM_Pulse = (period1 / DUTY_CYCLE) - 1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  	  //当定时器计数值小于CCR1_Val时为高电平
	TIM_OC1Init(GENERAL_TIM, &TIM_OCInitStructure);	 //使能通道1
  
	/*使能或者失能 TIMx 在 CCR1 上的预装载寄存器*/
	//TIM_OC1PreloadConfig(GENERAL_TIM, TIM_OCPreload_Enable);

	TIM_SelectMasterSlaveMode(GENERAL_TIM, TIM_MasterSlaveMode_Enable);//设置或者重置 TIMx 主/从模式
	TIM_SelectOutputTrigger(TIM1, TIM_TRGOSource_Update);//选择 TIMx 更新事件作为触发输出

	TIM_ARRPreloadConfig(TIM1, ENABLE);  // 使能或者失能 TIMx 在 ARR 上的预装载寄存器 
	// 使能定时器
	TIM_Cmd(GENERAL_TIM, ENABLE);	
   
}



/**	
  * @brief  初始化控制通用定时器
  * @param  无
  * @retval 无
  */
void TIMx_PWMConfiguration(void)
{
	//TIMx_GPIO_Config();
  
  	TIM1_PWMOUTPUT_Config();
	TIM_CtrlPWMOutputs(TIM1, ENABLE);   //高级定时器一定要加上，主输出使能
	
}

/*********************************************END OF FILE**********************/
