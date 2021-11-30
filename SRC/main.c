#include "main.h"
#include "user_hal_spi.h"
#include "control_task/control_task.h"
//#include "ssd1306.h"
//#include "ssd1306_tests.h"
#include "ili9163.h"
#include <stdio.h> //use sprintf
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lvgl_app.h"
#include "lv_port_indev.h"
#include "multi_button/multi_button.h"

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
	/* Configure the system clock */
	HAL_Init();
	
	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_DMA_Init();
	MX_ADC1_Init();
	MX_TIM1_Init();
	MX_TIM8_Init();
	MX_TIM2_Init();
	MX_TIM3_Init();
	MX_SPI2_Init();
//	MX_TIM14_Init();
//	MX_EXTI_Init();
	
	/* USER CODE BEGIN 1 */
	adc_measure_init();
	
	lv_init();
	lv_port_disp_init();
	lv_port_indev_init();
//	my_button_init();
	
	HAL_TIM_Encoder_Start(TIM2);
	HAL_TIM_Encoder_Start(TIM3);
	
	/* 开启TIM1/TIM8各四路互补PWM
	 * 没法同步定时器，只能这样打开了
	 * 间隔时间120ns
	 */
	TIM1->CR1 |= TIM_CR1_CEN;
	TIM8->CR1 |= TIM_CR1_CEN;
	
	TIM1->CCR1=2000;
	
//	lv_ex_spinner_1();
	lv_ex_btn_1();
	
	/* USER CODE END 1 */
	
	/* Infinite loop */
	while (1)
  {
		/* USER CODE BEGIN 2 */
		lv_task_handler(); /* let the GUI do its work */
//		button_ticks();
    HAL_Delay(5);
  }
	/* USER CODE END 2 */
}


