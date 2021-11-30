/**
  ******************************************************************************
  * @file    user_hal_spi.h
  * @author  mxy in NJUST 6003 Team
  * @brief   SPI HAL module driver.
  */
	

#ifndef __user_hal_spi_h__
#define __user_hal_spi_h__

#include "HAL_conf.h"
#include "user_hal.h"
#include "user_hal_lib.h"

void MX_SPI2_Init(void);
void HAL_SPI_Transmit(SPI_TypeDef *SPIx, uint8_t *pData, uint16_t Size, uint32_t Timeout);
void HAL_SPI_Transmit_DMA(SPI_TypeDef *SPIx, uint8_t *pData, uint16_t Size);
#endif
