#include "stm32f4xx.h"
#include "bsp_basic_tim.h"
#include "bsp_led.h"
#include "bsp_debug_usart.h"



uint16_t a = 500; 
uint32_t data = 0;
uint16_t contrastData = 0;
uint16_t flag = 0;

int main(void) 
{
    uint32_t b = 0xfffff;
	LED_GPIO_Config();
	Debug_USART_Config();
 
	TIMx_Configuration(); 
    
	printf("��ǰ����\n");
	printf("�����ʣ�19200\n");
    printf("����λ��8\n");
    printf("У��λ����У��\n");
    printf("ֹͣλ��1\n");
    
 	while(1)
  	{  
		if(flag == 1)
		{
          for(b;b != 0;--b){}
            printf("\n");
            b = 0xfffff;
            flag = 0;
            if((contrastData == 0) && (data > 0) && (((data / 10) < 6553) || (((data / 10) == 6553) && ((data % 100) <= 5))))
            {   
                a = data;
                TIMx_Configuration();
                printf("д��ɹ�\n");
                printf("��ǰƵ��Ϊ:%d ms\n",a);
            }
            else
            { 
                contrastData = 0;
                printf("д��ʧ��\n");           
             }
            data = 0;
		}
			
  	}
}



/*********************************************END OF FILE**********************/

