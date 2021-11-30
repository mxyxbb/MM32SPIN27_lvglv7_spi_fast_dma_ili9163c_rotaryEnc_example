/**
  ******************************************************************************
  * @file    user_hal.h
  * @author  mxy in NJUST 6003 Team
  * @brief   GPIO HAL module driver.
  */
	

#ifndef __user_hal_h__
#define __user_hal_h__

#include "HAL_conf.h"
#include "user_hal_lib.h"

#define UNUSED(X) (void)X

extern __IO uint32_t uwTick;

/* Initialization and Configuration functions  ******************************/
void HAL_Init(void);

/* Peripheral Control functions  ************************************************/
void HAL_IncTick(void);
void HAL_Delay(uint32_t Delay);
uint32_t HAL_GetTick(void);

#endif
