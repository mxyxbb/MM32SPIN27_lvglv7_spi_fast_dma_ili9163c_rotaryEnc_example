/**
  ******************************************************************************
  * @file    user_hal_lib.h
  * @author  mxy in NJUST 6003 Team
  * @brief   GPIO HAL module driver.
  */
	

#ifndef __user_hal_lib_h__
#define __user_hal_lib_h__

#include "HAL_conf.h"
#include "user_hal.h"

#define GPIO_PIN_SET Bit_SET
#define GPIO_PIN_RESET Bit_RESET
#define HAL_MAX_DELAY 0xffff

void MX_GPIO_Init(void);
void MX_DMA_Init(void);
void MX_ADC1_Init(void);
void HAL_ADC_Start_DMA(ADC_TypeDef * ADCx, uint32_t *pData, uint32_t Length);
void HAL_ADC_ConvCpltCallback(ADC_TypeDef * hadc);
void MX_TIM1_Init(void);
void MX_TIM2_Init(void);
void MX_TIM3_Init(void);
void MX_TIM8_Init(void);
void MX_TIM14_Init(void);
void HAL_TIM_Base_Start(TIM_TypeDef * htim);
void HAL_TIM_PWM_Start(TIM_TypeDef * htim);
void HAL_TIM_Base_Start_IT(TIM_TypeDef * htim);
void HAL_TIM_Encoder_Start(TIM_TypeDef * htim);
void HAL_TIM_PeriodElapsedCallback(TIM_TypeDef * htim);
void HAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, BitAction BitVal);
void MX_EXTI_Init(void);
void HAL_GPIO_EXTI_Callback(uint32_t EXTI_Linex);

#endif
