/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ������ʱ����ʱ
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ��  STM32 F407 ������
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
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
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void) 
{

	LED_GPIO_Config();
	Debug_USART_Config();
 
	TIMx_Configuration(); 
	
	printf("�ں���\n");
	
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

