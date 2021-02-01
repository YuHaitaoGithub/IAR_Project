#ifndef __BASIC_TIM_H
#define	__BASIC_TIM_H

#include "stm32f4xx.h"

extern uint16_t a;



#define BASIC_TIM           	TIM6
#define BASIC_TIM_CLK       	RCC_APB1Periph_TIM6

#define BASIC_TIM_IRQn			TIM6_DAC_IRQn
#define BASIC_TIM_IRQHandler    TIM6_DAC_IRQHandler
#define Period                 (a - 1)
#define Prescaler             (42000-1)

void TIMx_Configuration(void);

#endif /* __BASIC_TIM_H */

