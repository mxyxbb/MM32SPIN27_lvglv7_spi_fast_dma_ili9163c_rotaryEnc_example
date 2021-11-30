/**
  ******************************************************************************
  * @file    user_hal_lib.c
  * @author  mxy in NJUST 6003 Team
  * @brief   GPIO HAL module driver.
  */
	
/* Includes ------------------------------------------------------------------*/

#include "user_hal_lib.h"
#include "main.h"

/**
  * @brief  Set the priority of an interrupt.
  * @param  IRQn: External interrupt number.
  *         This parameter can be a value of @ref IRQn_Type
  *         (For the complete MM32 Devices IRQ Channels list, please refer to HAL_device.h file)
  * @param  Priority: the priority level for the IRQ channel.
  *         This parameter can be a value between 0 and 3
  *         A lower priority value indicates a higher priority.
  * @param  Status: The status for the IRQn channel.
  *         This parameter can be set either to ENABLE or DISABLE
  * @retval None
  */
void HAL_NVIC_SetPriority(IRQn_Type IRQn,uint8_t Priority,uint8_t Status)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_InitStructure.NVIC_IRQChannel = IRQn;                       
	NVIC_InitStructure.NVIC_IRQChannelPriority = Priority;
	NVIC_InitStructure.NVIC_IRQChannelCmd = (FunctionalState)Status;
	NVIC_Init(&NVIC_InitStructure);
}

void MX_GPIO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	/* GPIO Ports Clock Enable */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);
	
	/*Configure GPIO pin Output Level */
	GPIO_SetBits(GPIOB,GPIO_Pin_10);
	GPIO_SetBits(GPIOC,GPIO_Pin_4);
	
	/*LED Pins*/
	/*Configure GPIO pins : PBPin */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/*Configure GPIO pins : PCPin */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	/*Rotary Encoder Pins*/
	/*Configure GPIO pins : RotatePin */
  GPIO_InitStructure.GPIO_Pin = Rotate_A_Pin;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(Rotate_A_Port, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = Rotate_B_Pin;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(Rotate_B_Port, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = Rotate_Btn_Pin;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(Rotate_Btn_Port, &GPIO_InitStructure);
	
	/*ADC1 Pins*/
	/*Configure GPIO pins : PAPin PAPin PAPin PAPin PAPin PAPin PAPin PAPin */
	GPIO_InitStructure.GPIO_Pin  =  GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/**TIM1 GPIO Configuration
	PB4     ------> TIM1_CH2N
	PB5     ------> TIM1_CH2
	PB6     ------> TIM1_CH1N
	PB7     ------> TIM1_CH1
	*/	
//	GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_7);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_7);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_7);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_7);
	
	GPIO_InitStructure.GPIO_Pin  =  /*GPIO_Pin_4|*/GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/**TIM8 GPIO Configuration
	PC0     ------> TIM8_CH1
	PC1     ------> TIM8_CH1N
	PC2     ------> TIM8_CH2
	PC3     ------> TIM8_CH2N
	*/	
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource0, GPIO_AF_6);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource1, GPIO_AF_5);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource2, GPIO_AF_5);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource3, GPIO_AF_5);
	
	GPIO_InitStructure.GPIO_Pin  =  GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	/**TIM2 Encoder GPIO Configuration
	PC7     ------> TIM2_CH1
	PC8     ------> TIM2_CH2
	*/	
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_5);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_5);
	
	GPIO_InitStructure.GPIO_Pin  =  GPIO_Pin_7|GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	/**TIM3 Encoder GPIO Configuration
	PD7     ------> TIM3_CH1
	PB8     ------> TIM3_CH2
	*/	
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource7, GPIO_AF_5);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_6);
	
	GPIO_InitStructure.GPIO_Pin  =  GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin  =  GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void MX_EXTI_Init(void)
{
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource8);
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource10);
	
	EXTI_InitTypeDef EXTI_InitTypeStruct;
	EXTI_StructInit(&EXTI_InitTypeStruct);
//	EXTI_InitTypeStruct.EXTI_Line = EXTI_Line8;
//	EXTI_InitTypeStruct.EXTI_LineCmd = ENABLE;
//	EXTI_InitTypeStruct.EXTI_Mode = EXTI_Mode_Interrupt;
//	EXTI_InitTypeStruct.EXTI_Trigger = EXTI_Trigger_Rising;
//	EXTI_Init(&EXTI_InitTypeStruct);

	EXTI_InitTypeStruct.EXTI_Line = EXTI_Line10;
	EXTI_InitTypeStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitTypeStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitTypeStruct.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitTypeStruct);
	
	/*EXTI interrupt init*/
	HAL_NVIC_SetPriority(EXTI4_15_IRQn, 2, ENABLE);
}

void MX_ADC1_Init(void)
{
	ADC_InitTypeDef  ADC_InitStructure;
	ADC_StructInit(&ADC_InitStructure);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	//ADC prescale factor
	ADC_InitStructure.ADC_PRESCARE = ADC_PCLK2_PRESCARE_16;
	//Set ADC mode to continuous conversion mode
	ADC_InitStructure.ADC_Mode = ADC_Mode_Single_Period;
	//AD data right-justified
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC3;
	ADC_Init(ADC1, &ADC_InitStructure);

	ADC_ExternalTrigConvCmd(ADC1,ENABLE);
	//ADC_RegularChannelConfig(ADC, ADC_Channel_All_Disable, 0, ADC_SampleTime_13_5Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 0, ADC_SampleTime_6_5Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_6_5Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 2, ADC_SampleTime_6_5Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 3, ADC_SampleTime_6_5Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 4, ADC_SampleTime_6_5Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 5, ADC_SampleTime_6_5Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 6, ADC_SampleTime_6_5Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 7, ADC_SampleTime_6_5Cycles);

	ADC_DMACmd(ADC1, ENABLE);
	ADC_Cmd(ADC1, ENABLE);
	
	//ADC interrupt initialization
	ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);
	HAL_NVIC_SetPriority(ADC1_IRQn, 1, ENABLE);
}

/*******************************************************************************
* @name   : DMAInit
* @brief  : Initialize DMA
* @param  : None
* @retval : void
*******************************************************************************/
void MX_DMA_Init(void)
{
//	NVIC_InitTypeDef NVIC_InitStruct;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
//	//DMA interrupt initialization
//	DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, DISABLE);
//	NVIC_InitStruct.NVIC_IRQChannel = DMA1_Channel1_IRQn;
//	NVIC_InitStruct.NVIC_IRQChannelPriority = 0;
//	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStruct);
}

void HAL_ADC_Start_DMA(ADC_TypeDef * ADCx, uint32_t *pData, uint32_t Length)
{
  DMA_InitTypeDef DMA_InitStructure;

	DMA_DeInit(DMA1_Channel1);
	//DMA transfer peripheral address
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) & (ADCx->ADDATA);
	//DMA transfer memory address
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)pData;
	//DMA transfer direction from peripheral to memory
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	//DMA cache size
	DMA_InitStructure.DMA_BufferSize = Length;
	//After receiving the data, the peripheral address is forbidden to move backward
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	//After receiving the data, the memory address is shifted backward
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	//Define the peripheral data width to 16 bits
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	//Define the memory data width to 16 bits
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	//Cycle conversion mode
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	//DMA priority is high
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	DMA_Cmd(DMA1_Channel1, ENABLE);
}

/* TIM1 init function */
void MX_TIM1_Init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	TIM_BDTRInitTypeDef TIM_Bdtrinitstructure;//死区设置
	
	/* TIM1 clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period = 12800-1;
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);
	TIM_OC3Init(TIM1, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
	
	TIM1->CCR3=4000; // trigger adc conversion
	
	TIM_Bdtrinitstructure.TIM_AutomaticOutput=TIM_AutomaticOutput_Enable;
	TIM_Bdtrinitstructure.TIM_Break=TIM_Break_Disable;
	TIM_Bdtrinitstructure.TIM_BreakPolarity=TIM_BreakPolarity_High;
	TIM_Bdtrinitstructure.TIM_DeadTime=0x2A;	//450ns deadtime inserted
	TIM_Bdtrinitstructure.TIM_LOCKLevel=TIM_LOCKLevel_OFF;
	TIM_Bdtrinitstructure.TIM_OSSIState=TIM_OSSIState_Disable;
	TIM_Bdtrinitstructure.TIM_OSSRState=TIM_OSSRState_Disable;
	TIM_BDTRConfig(TIM1,&TIM_Bdtrinitstructure);
	
	TIM_ARRPreloadConfig(TIM1, ENABLE);

	TIM_SelectOutputTrigger(TIM1, TIM_TRGOSource_Update);
	
	/* TIM1 interrupt Init */
	HAL_NVIC_SetPriority(TIM1_BRK_UP_TRG_COM_IRQn, 1, ENABLE);
//	HAL_NVIC_SetPriority(TIM1_CC_IRQn, 1, ENABLE);
//	TIM_ITConfig(TIM1,TIM_IT_CC3,ENABLE );
}

/* TIM8 init function */
void MX_TIM8_Init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	TIM_BDTRInitTypeDef TIM_Bdtrinitstructure;//死区设置
	
	/* TIM8 clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);

	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period = 12800-1;
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	TIM_OC1Init(TIM8, &TIM_OCInitStructure);
	TIM_OC2Init(TIM8, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);
	
	TIM_Bdtrinitstructure.TIM_AutomaticOutput=TIM_AutomaticOutput_Enable;
	TIM_Bdtrinitstructure.TIM_Break=TIM_Break_Disable;
	TIM_Bdtrinitstructure.TIM_BreakPolarity=TIM_BreakPolarity_High;
	TIM_Bdtrinitstructure.TIM_DeadTime=0x2A;	//450ns deadtime inserted
	TIM_Bdtrinitstructure.TIM_LOCKLevel=TIM_LOCKLevel_OFF;
	TIM_Bdtrinitstructure.TIM_OSSIState=TIM_OSSIState_Disable;
	TIM_Bdtrinitstructure.TIM_OSSRState=TIM_OSSRState_Disable;
	TIM_BDTRConfig(TIM8,&TIM_Bdtrinitstructure);
	
	TIM_ARRPreloadConfig(TIM8, ENABLE);
	
//	TIM_SelectSlaveMode(TIM8, TIM_SlaveMode_Trigger); //TIM8 triggered by TIM2
//	TIM_SelectInputTrigger(TIM8, TIM_TS_ITR1);
	
	TIM_SelectOutputTrigger(TIM8, TIM_TRGOSource_Update);
	
	/* TIM8 interrupt Init */
	HAL_NVIC_SetPriority(TIM8_BRK_UP_TRG_COM_IRQn, 1, ENABLE);
}

/* TIM2 init function */
void MX_TIM2_Init(void)
{
	/* TIM2 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	TIM_TimeBaseStructure.TIM_Period = 65536-1;
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Update);
	
	/* TIM2 interrupt Init */
	HAL_NVIC_SetPriority(TIM2_IRQn, 1, ENABLE);
}

/* TIM3 init function */
void MX_TIM3_Init(void)
{
	/* TIM3 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	TIM_TimeBaseStructure.TIM_Period = 65536-1;
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	TIM_SelectOutputTrigger(TIM3, TIM_TRGOSource_Update);
	
	/* TIM3 interrupt Init */
	HAL_NVIC_SetPriority(TIM3_IRQn, 1, ENABLE);
}

/* TIM14 init function */
void MX_TIM14_Init(void)
{
	/* TIM14 clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM14, ENABLE);
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	TIM_TimeBaseStructure.TIM_Period = 1000-1;
	TIM_TimeBaseStructure.TIM_Prescaler = 96-1;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM14, &TIM_TimeBaseStructure);
	
	/* TIM14 interrupt Init */
	HAL_NVIC_SetPriority(TIM14_IRQn, 1, ENABLE);
}

void HAL_TIM_PWM_Start(TIM_TypeDef * htim)
{
	TIM_CtrlPWMOutputs(htim, ENABLE);
	
	TIM_Cmd(htim, ENABLE);
}

void HAL_TIM_Base_Start(TIM_TypeDef * htim)
{
	TIM_Cmd(htim, ENABLE);
}

void HAL_TIM_Base_Start_IT(TIM_TypeDef * htim)
{
	TIM_ITConfig(htim,TIM_IT_Update,ENABLE );

	TIM_Cmd(htim, ENABLE);
}

void HAL_TIM_Encoder_Start(TIM_TypeDef * htim)
{
	TIM_EncoderInterfaceConfig(htim, TIM_EncoderMode_TI12, TIM_ICPolarity_Falling, TIM_ICPolarity_Falling);

	TIM_Cmd(htim, ENABLE);
}



void HAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	uint32_t odr;

	/* Check the parameters */
	assert_param(IS_GPIO_PIN(GPIO_Pin));

	/* get current Output Data Register value */
	odr = GPIOx->ODR;

	/* Set selected pins that were at low level, and reset ones that were high */
	GPIOx->BSRR = ((odr & GPIO_Pin) << 16U) | (~odr & GPIO_Pin);
}

void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, BitAction BitVal)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GET_GPIO_PIN(GPIO_Pin));
    assert_param(IS_GPIO_BIT_ACTION(BitVal));

    if (BitVal != Bit_RESET)
    {
        GPIOx->BSRR = GPIO_Pin;
    }
    else
    {
        GPIOx->BRR = GPIO_Pin;
    }
}

__weak void HAL_TIM_PeriodElapsedCallback(TIM_TypeDef * htim)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(htim);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_TIM_PeriodElapsedCallback could be implemented in the user file
   */
}
/**
  * @brief  Conversion complete callback in non-blocking mode.
  * @param hadc ADC handle
  * @retval None
  */
__weak void HAL_ADC_ConvCpltCallback(ADC_TypeDef * hadc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hadc);

  /* NOTE : This function should not be modified. When the callback is needed,
            function HAL_ADC_ConvCpltCallback must be implemented in the user file.
   */
}
/**
  * @brief  Conversion complete callback in non-blocking mode.
  * @param hadc ADC handle
  * @retval None
  */
__weak void HAL_GPIO_EXTI_Callback(uint32_t EXTI_Linex)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(EXTI_Linex);

  /* NOTE : This function should not be modified. When the callback is needed,
            function HAL_ADC_ConvCpltCallback must be implemented in the user file.
   */
}
