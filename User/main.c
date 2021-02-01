#include "stm32f4xx.h"
#include "bsp_basic_tim.h"
#include "bsp_led.h"
#include "bsp_debug_usart.h"
#include "bsp_general_tim.h"
#include "string.h"

uint16_t Index = 0;
uint16_t RecvData[256];
uint16_t Mode_switch_flag = 0;
uint16_t FlagStart = 0;
uint16_t Frequency = 500;


int VariableInit()
{
	memset(RecvData,0,Index);
	Index = 0;
	return 0;
}


int Mode0()
{
    uint16_t i;
	uint32_t data = 0;

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
    return 0;
}


int Mode1()
{
	int i;
	for(i = Index;i < 0;--i)
	{
		USART_SendData(DEBUG_USART,RecvData[i]);
	}
	while(USART_GetFlagStatus(DEBUG_USART,USART_FLAG_TC)==RESET)
  	{}
    return 0;
}



int main(void) 
{
    
	uint32_t b = 0xfffff;
	LED_GPIO_Config();
	Debug_USART_Config();
	TIMx_Configuration(); 

	
	printf("Serial port parameters\n");
	printf("Baud rate£º19200\n");
    printf("Data bits£º8\n");
    printf("Check digit£ºNo check\n");
    printf("Stop bit£º1\n");
    printf("Please enter function code 01 or 02\n");
	
 	while(1)
  	{
		if(FlagStart == 1)
		{
			for(b;b != 0;--b);
            FlagStart = 0;
			b = 0xfffff;
			if(Index < 3)
			{
				printf("Wrong data lenth\n");
				VariableInit();
				continue;	
			}
			switch((RecvData[0] - 48) + (RecvData[1] - 48))
			{	
			case 1:{Mode0();break;}
			case 2:{Mode1();break;}
			printf("Wrong function code\n");
			break;
			}
			VariableInit();
		}
  	}
}



/*********************************************END OF FILE**********************/

