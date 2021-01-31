/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   基本定时器定时
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火  STM32 F407 开发板
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */


#include "stm32f4xx.h"
#include "bsp_basic_tim.h"
#include "bsp_led.h"
#include "bsp_debug_usart.h"


uint16_t a = 5000; 
uint16_t b = 0; 

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void) 
{

	LED_GPIO_Config();
	Debug_USART_Config();
 
	TIMx_Configuration(); 
	
	printf("于海涛\n");
	
 	while(1)
  	{  
		if(b == 1)
		{
			b = 0;
			a = 10000;
			TIMx_Configuration();
		}
		if(b == 2)
		{
			b = 0;
			a = 5000;
			TIMx_Configuration();
		}
			
  	}
}



/*********************************************END OF FILE**********************/

