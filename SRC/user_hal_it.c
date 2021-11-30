/**
  ******************************************************************************
  * @file    user_hal_lib.c
  * @author  mxy in NJUST 6003 Team
  * @brief   GPIO HAL module driver.
  */
	
/* Includes ------------------------------------------------------------------*/

#include "user_hal_lib.h"
#include "lvgl.h"

void SysTick_Handler(void)
{
	HAL_IncTick();
	lv_tick_inc(1);
}

void TIM1_BRK_UP_TRG_COM_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
  {
    TIM_ClearITPendingBit(TIM1, TIM_IT_Update );
    HAL_TIM_PeriodElapsedCallback(TIM1);
	}  
}

void TIM1_CC_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM1, TIM_IT_CC3) != RESET)
  {
    TIM_ClearITPendingBit(TIM1, TIM_IT_CC3 );
    HAL_TIM_PeriodElapsedCallback(TIM1);
	}  
}

void TIM2_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
  {
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update );
    HAL_TIM_PeriodElapsedCallback(TIM2);
	}  
}

void TIM3_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
  {
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update );
    HAL_TIM_PeriodElapsedCallback(TIM3);
	}  
}

void TIM14_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM14, TIM_IT_Update) != RESET)
  {
    TIM_ClearITPendingBit(TIM14, TIM_IT_Update );
    HAL_TIM_PeriodElapsedCallback(TIM14);
	}  
}

void ADC1_IRQHandler(void)
{
	if (ADC_GetITStatus(ADC1, ADC_IT_EOC) != RESET)
  {
    ADC_ClearITPendingBit(ADC1, ADC_IT_EOC );
    HAL_ADC_ConvCpltCallback(ADC1);
	} 
}

void EXTI4_15_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line8) != RESET)
  {
    EXTI_ClearITPendingBit(EXTI_Line8);
    HAL_GPIO_EXTI_Callback(EXTI_Line8);
	}
	if (EXTI_GetITStatus(EXTI_Line10) != RESET)
  {
    EXTI_ClearITPendingBit(EXTI_Line10);
    HAL_GPIO_EXTI_Callback(EXTI_Line10);
	} 
}

void DMA1_Channel4_5_IRQHandler(void)
{
	
}