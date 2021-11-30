/**
  ******************************************************************************
  * @file    user_hal_spi.c
  * @author  mxy in NJUST 6003 Team
  * @brief   SPI HAL module driver.
  */
	
/* Includes ------------------------------------------------------------------*/

#include "user_hal_spi.h"
#include "string.h"
#include "main.h"

/*******************************************************************************
* @name   : SPIM_Init
* @brief  : SPIM Init
* @param  : SPI_TypeDef* SPIx,unsigned short spi_baud_div
* @retval : void
*******************************************************************************/
void MX_SPI2_Init(void)
{
    SPI_InitTypeDef SPI_InitStructure;
    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);   
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);   
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);//SPI2 clk enable
		
		GPIO_InitStructure.GPIO_Pin  = SPI2_DC_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(SPI2_DC_Port, &GPIO_InitStructure);
	
		GPIO_InitStructure.GPIO_Pin  = SPI2_Reset_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(SPI2_Reset_Port, &GPIO_InitStructure);
	
		GPIO_InitStructure.GPIO_Pin  = SPI2_CS_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(SPI2_CS_Port, &GPIO_InitStructure);

//    //SPI_NSS
//    GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_1);
    //SPI_SCK
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource12, GPIO_AF_1);
    //SPI_MOSI
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_4);

    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12 | GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_DataWidth = SPI_DataWidth_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    //	SPI_InitStructure.SPI_NSS = SPI_NSS_Hard;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_Init(SPI2, &SPI_InitStructure);

    SPI_Cmd(SPI2, ENABLE);
    SPI_BiDirectionalLineConfig(SPI2, SPI_Direction_Tx);
		
		DMA_InitTypeDef DMA_InitStructure;
		DMA_DeInit(DMA1_Channel5);
		DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) & (SPI2->TXREG);
		DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
		DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
		DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
		DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
		DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
		DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
		DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; 
		DMA_Init(DMA1_Channel5, &DMA_InitStructure);
//		DMA_ITConfig(DMA1_Channel5, DMA_IT_TC, ENABLE);
		
		/* Enable SPI2 DMA TX request */
		SPI_DMACmd(SPI2, SPI_DMAReq_EN, ENABLE);
//		DMA_Cmd(DMA1_Channel5, ENABLE);
}
/**
  * @brief  Transmit an amount of data in blocking mode.
  * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @param  pData pointer to data buffer
  * @param  Size amount of data to be sent
  * @param  Timeout Timeout duration
  * @retval HAL status
  */
void HAL_SPI_Transmit(SPI_TypeDef *SPIx, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
	uint16_t TxXferCount,tickstart;
	uint8_t *pTxBuffPtr;
	tickstart = HAL_GetTick();
	pTxBuffPtr  = (uint8_t *)pData;
	TxXferCount = Size;
	while (TxXferCount > 0U)
	{
		/* Wait until TXE flag is set to send data */
		if(SPIx->CSTAT & SPI_FLAG_TXEPT)
		{
			SPI_SendData(SPIx, *pTxBuffPtr);
			pTxBuffPtr += sizeof(uint8_t);
      TxXferCount--;
		}
		else 
		{	
			/* Timeout management */
			if ((((HAL_GetTick() - tickstart) >=  Timeout) && (Timeout != HAL_MAX_DELAY)))
      {
        return;
      }
		}
	}
}
void HAL_SPI_Transmit_DMA(SPI_TypeDef *SPIx, uint8_t *pData, uint16_t Size)
{
	DMA1_Channel5->CCR &= ~1;
	DMA1_Channel5->CMAR = (u32) pData; //mem地址
	DMA1_Channel5->CNDTR = Size ; //传输长度
	DMA1_Channel5->CCR |= 1;
	
//	while(DMA_GetFlagStatus(DMA1_FLAG_TC5)!=RESET) //等待DMA传输完成
//  DMA_ClearFlag(DMA1_FLAG_TC5); // 清除标志
}