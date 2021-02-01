#include "stm32f4xx.h"
#include "bsp_basic_tim.h"
#include "bsp_led.h"
#include "bsp_debug_usart.h"
#include "bsp_general_tim.h"


uint16_t Index = 0;
uint16_t RecvData[256];
uint16_t Mode_switch_flag = 0;
uint16_t FlagStart = 0;
uint16_t a = 500;


int VariableInit()
{
	memset(RecvData,0,Index);
	Index = 0;
	
}


int Mode0()
{
    uint16_t i;
	uint32_t data = 0;
    if(Index <= 3)
		return 0;
	for(i = 2;i < Index;++i)
	{
		if(RecvData[i] < 48 || RecvData[i] > 57)
		{
			printf("Illegal data,Write failed\n");
			return 0;
		}
		data = data * 10 + (RecvData[i] - 48);
	}
	a = data;
    TIMx_Configuration();
    printf("Write success\n");
    printf("The current frequency is:%d ms\n",a);
    data = 0;

}


int Mode1()
{
	int i;
	if(Index <= 3)
		return 0;
	for(i = Index;i < 0;--i)
	{
		USART_SendData(DEBUG_USART,RecvData[i]);
	}
	while(USART_GetFlagStatus(DEBUG_USART,USART_FLAG_TC)==RESET)
  	{}
}



int main(void) 
{
    
	uint32_t b = 0xfffff;
	LED_GPIO_Config();
	Debug_USART_Config();
 
	TIMx_Configuration(); 

	
	printf("Serial port parameters\n");
	printf("Baud rate��19200\n");
    printf("Data bits��8\n");
    printf("Check digit��No check\n");
    printf("Stop bit��1\n");
    printf("Please enter function code 01 or 02\n");
	
 	while(1)
  	{
		if(FlagStart == 1)
		{
			FlagStart = 0;
			for(b;b != 0;--b);
			b = 0xfffff;
			if((Index <= 1) || (((RecvData[0] - 48) + (RecvData[1] - 48)) != 1)\
				|| (((RecvData[0] - 48) + (RecvData[1] - 48)) != 2))
			{
				printf("Wrong function code\n");
				VariableInit();
				continue;	
			}
			if(((RecvData[0] - 48) + (RecvData[1] - 48)) == 1)
			{
				Mode1();
				
			}
			else
			{
				Mode0();
			}
			VariableInit();
		}
  	}
}



/*********************************************END OF FILE**********************/

