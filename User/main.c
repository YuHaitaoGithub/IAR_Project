#include "stm32f4xx.h"
#include "bsp_basic_tim.h"
#include "bsp_led.h"
#include "bsp_debug_usart.h"


uint16_t a = 500; 
uint16_t b = 0; 


int main(void) 
{

	LED_GPIO_Config();
	Debug_USART_Config();
 
	TIMx_Configuration(); 
	
	
 	while(1)
  	{  
		if(b == 1)
		{
			b = 0;
			a = 1000;
			TIMx_Configuration();
		}
		if(b == 2)
		{
			b = 0;
			a = 500;
			TIMx_Configuration();
		}
			
  	}
}



/*********************************************END OF FILE**********************/

