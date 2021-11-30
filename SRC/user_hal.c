/**
  ******************************************************************************
  * @file    user_hal_lib.c
  * @author  mxy in NJUST 6003 Team
  * @brief   GPIO HAL module driver.
  */
	
/* Includes ------------------------------------------------------------------*/

#include "user_hal.h"

__IO uint32_t uwTick;

void HAL_Init(void)
{
	SystemInit();
	
	/* Use SysTick as time base source and configure 1ms tick */
	//	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
	SysTick_Config(SystemCoreClock/1000);
	
	NVIC_SetPriority(SysTick_IRQn, 0x00);
}

/**
  * @brief This function is called to increment a global variable "uwTick"
  *        used as application time base.
  * @note In the default implementation, this variable is incremented each 1ms
  *       in SysTick ISR.
  * @note This function is declared as __weak to be overwritten in case of other
  *      implementations in user file.
  * @retval None
  */
__weak void HAL_IncTick(void)
{
  uwTick += 1U;
}

/**
  * @brief Provides a tick value in millisecond.
  * @note This function is declared as __weak to be overwritten in case of other
  *       implementations in user file.
  * @retval tick value
  */
__weak uint32_t HAL_GetTick(void)
{
  return uwTick;
}

/**
  * @brief This function provides minimum delay (in milliseconds) based
  *        on variable incremented.
  * @note In the default implementation , SysTick timer is the source of time base.
  *       It is used to generate interrupts at regular time intervals where uwTick
  *       is incremented.
  * @note This function is declared as __weak to be overwritten in case of other
  *       implementations in user file.
  * @param Delay specifies the delay time length, in milliseconds.
  * @retval None
  */
__weak void HAL_Delay(uint32_t Delay)
{
  uint32_t tickstart = HAL_GetTick();
  uint32_t wait = Delay;

  /* Add a freq to guarantee minimum wait */
  if (wait < 0xFFFFFFFFU)
  {
    wait += (uint32_t)(1U);
  }

  while ((HAL_GetTick() - tickstart) < wait)
  {
  }
}


