#ifndef __BASIC_TIM_H
#define	__BASIC_TIM_H

#include "stm32f4xx.h"




#define BASIC_TIM           	TIM2
#define BASIC_TIM_CLK       	RCC_APB1Periph_TIM2

#define BASIC_TIM_IRQn			TIM2_IRQn;
#define TIM2_PRD                1000-1

void TIM2_Configuration(void);

#endif /* __BASIC_TIM_H */

