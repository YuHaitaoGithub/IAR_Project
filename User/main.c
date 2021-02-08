#include "main.h"



//volatile uint8_t ReceiveArray[ReceiveDataSize];
//volatile uint16_t Index = 0;
//volatile uint16_t ReceiveFlag = 0;
//volatile uint16_t erroyFlag = 0;

volatile uint32_t period1 = 1000;
volatile uint32_t period2 = 8000;
volatile uint16_t erroyFlag = 0;

//volatile uint16_t prescaler;


volatile long f = 1;


#if 0
int FrequencyCalculation()
{
	float midFloat;
	long clkInt;
	long midInt;
	float clkFloat;
	if(f <= 0)
		return 0;
    clkFloat = CK_INT / f;
	if(clkFloat-(long)clkFloat >= 0.5f)  		
		clkInt = clkFloat + 1;
	else							 		
		clkInt = (long)clkFloat;
	
	midFloat = sqrt(clkFloat);// 开方
	if(midFloat - (long)midFloat >= 0.5f)  		
		midInt = (long)midFloat + 1;
	else									
		midInt = (long)midFloat;
	// 找一组最接近的
	for(int i = midInt;i >= 1;--i)
	{
		if(clkInt % i == 0)
		{
			if((clkInt / i > 0 && clkInt / i <= 65535) || (i > 0 && i <= 65535))
			{
				prescaler = i;
				period = clkInt / i;
				break;
			}
			else
			{
				printf("Data out of range\n");
				return 0;
			}
		}	
	}
	return 1;
}
#endif


#if 0
int ChangeFry(void)
{
	int i;
	if(!erroyFlag)
	{
		f = 0;
		for(i = 0;i < Index;++i)
		{
			if(f / 10 > 214748364 || (f / 10 == 214748364 && f % 10 > 7))
				return 0;
			f = f * 10 + (uint16_t)(0xFF & (ReceiveArray[i] - '0'));		
		}
	}
	else
	{
		for(i = Index - 1;i >= 0;--i)
		{
			USART_SendData(DEBUG_USART, ReceiveArray[i]);
			while(USART_GetFlagStatus(DEBUG_USART,USART_FLAG_TC) == RESET){}
		}
		printf("\n");
		erroyFlag = 0;
		return 0;
	}
	return 1;
}

#endif







int main(void) 
{
	LED_GPIO_Config();
	Debug_USART_Config();
	
    //FrequencyCalculation();
	
	//printf("Current frequency:%d HZ\n",f);
	//Pulse_output(1000,8000);//1KHZ，8000个脉冲
	while(1)
 	{
		
		LED1_ON;
		LED2_ON;
		LED3_ON;
		TIM2_Configuration(); 
		TIMx_PWMConfiguration();
		while(f)
	  	{
			printf("%d\n",TIM2->CNT);
	  	}
        printf("8000\n");
        f = 1;
        while(erroyFlag != 1);
		erroyFlag = 0;
	}
}



/*********************************************END OF FILE**********************/

