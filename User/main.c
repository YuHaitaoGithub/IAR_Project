#include "main.h"


volatile uint32_t period1 = 1000;
volatile uint32_t period2 = 2000;
volatile uint16_t Flag = 1;
uint16_t Index;
uint8_t ReceiveArray[100];
volatile uint16_t ReceiveFlag = 1;



int main(void) 
{
    int i;
    int num;
    
	LED_GPIO_Config();
	Debug_USART_Config();

	while(1)
 	{
        num = 0;
        while(ReceiveFlag);
        ReceiveFlag = 1;
        for(i = 0;i < Index;++i)
        {
            num = num * 10 + (ReceiveArray[i] - '0');
        }
        Index = 0;
        memset(ReceiveArray,0,100);
        
        if(num > 0 && num <= 65535)
		{
            period2 = num;
            LED1_ON;
            LED2_ON;
            LED3_ON;
            TIM2_Configuration(); 
            TIMx_PWMConfiguration();
            while(Flag)
            {
                printf("%d\n",TIM2->CNT);
            }
            printf("%d\nsend seccece\n",period2);
            Flag = 1;  
        }
        else
          printf("send fail\n");
	}
}



/*********************************************END OF FILE**********************/

