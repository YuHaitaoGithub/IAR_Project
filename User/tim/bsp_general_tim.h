#ifndef __GENERAL_TIM_H
#define	__GENERAL_TIM_H

#include "stm32f4xx.h"


#define GENERAL_OCPWM_PIN             GPIO_Pin_9              
#define GENERAL_OCPWM_GPIO_PORT       GPIOF                      
#define GENERAL_OCPWM_GPIO_CLK        RCC_AHB1Periph_GPIOF
#define GENERAL_OCPWM_PINSOURCE		  GPIO_PinSource9
#define GENERAL_OCPWM_AF			  GPIO_AF_TIM14

#define GENERAL_TIM           		  TIM14
#define GENERAL_TIM_CLK       		  RCC_APB1Periph_TIM14

//#define GENERAL_TIM_IRQn			  TIM14_IRQn
//#define GENERAL_TIM_IRQHandler        TIM14_IRQHandler

#define DUTY_CYCLE                    2  //Õ¼¿Õ±È

void TIMx_PWMConfiguration(void);

#endif /* __GENERAL_TIM_H */

