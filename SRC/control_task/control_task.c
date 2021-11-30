#include "control_task/control_task.h"
#include "pid.h"

pid_t pid_motor_L,pid_motor_R;
_adc_measure_data adc_measure_data = {0};
_encoder_data encoder_data = {0};

void adc_measure(_adc_measure_data* adc_measure_data)
{
	adc_measure_data->output_voltage = ( (float)adc_measure_data->adc1_dma_buff[2] ) * 0.0128173828125f;
	adc_measure_data->input_voltage = ( (float)adc_measure_data->adc1_dma_buff[3] ) * 0.0128173828125f;
	adc_measure_data->output_current = ( (float)adc_measure_data->adc1_dma_buff[4] - 2041 ) * 0.0030517578125f;
	adc_measure_data->A0_voltage = adc_measure_data->adc1_dma_buff[5];
	adc_measure_data->A1_voltage = adc_measure_data->adc1_dma_buff[1];
	adc_measure_data->output_power = adc_measure_data->output_voltage*adc_measure_data->output_current;
	adc_measure_data->Middle_Err = (float)(adc_measure_data->A1_voltage - adc_measure_data->A0_voltage)/(float)(adc_measure_data->A1_voltage + adc_measure_data->A0_voltage);//计算偏差参考成电代码
}

/*

buff[0] PA0
buff[1]	PA1
buff[2] PA2
buff[3]	PA3
buff[4] PA4
buff[5] PA5
buff[6] PA6
buff[7] PA7

*/

void HAL_ADC_ConvCpltCallback(ADC_TypeDef* hadc)
{
	if(ADC1 == hadc)
	{
		adc_measure(&adc_measure_data);
		pid_calc(&pid_motor_L,adc_measure_data.A0_voltage,100);
		pid_calc(&pid_motor_R,adc_measure_data.A1_voltage,100);
		
		encoder_data.phasea = GPIO_ReadInputDataBit(Rotate_A_Port,Rotate_A_Pin);
		encoder_data.phaseb = GPIO_ReadInputDataBit(Rotate_B_Port,Rotate_B_Pin);
		if(encoder_data.phasea == 0 && encoder_data.phaseaL == 1)
		{
			if(encoder_data.phaseb==1)
				encoder_data.count++;
			else
				encoder_data.count--;
		}
		encoder_data.phaseaL = GPIO_ReadInputDataBit(Rotate_A_Port,Rotate_A_Pin);
		encoder_data.phasebL = GPIO_ReadInputDataBit(Rotate_B_Port,Rotate_B_Pin);
		
		HAL_GPIO_TogglePin(GPIOC,GPIO_Pin_4);
		
	}
}



void ControtLoopTaskInit(void)//给pid_inverter结构体赋初值
{
//  pid_user_init();
}

void adc_measure_init(void)
{
	HAL_Delay(50);
	HAL_ADC_Start_DMA(ADC1,
                   (uint32_t *)adc_measure_data.adc1_dma_buff,
                   8);

	ControtLoopTaskInit();
}

void HAL_TIM_PeriodElapsedCallback(TIM_TypeDef * htim)
{
	if(TIM1 == htim)
	{
		HAL_GPIO_TogglePin(GPIOC,GPIO_Pin_4);
	}
}

void HAL_GPIO_EXTI_Callback(uint32_t EXTI_Linex)
{
	if(EXTI_Line8 == EXTI_Linex)
	{
		
		
	}
	if(EXTI_Line10 == EXTI_Linex)
	{

	}
}

///**
// * @brief 串口回调函数
// * @param  huart            串口句柄
// */
//void HAL_UART_RxCpltCallback(uint32_t tim_base)
//{
////	if(huart->Instance == USART3)
//	{
////			ps("%c",recv_buf);
//		//调用处理数据的接口

//		//使能串口中断接收
////		HAL_UART_Receive_IT(&huart3, (uint8_t*)&recv_buf, 1);
//		
//	}	
//}


#define CHECK_TIMES 100
void check_current_offset(float* offset)
{
	uint32_t cur;
	for(uint8_t i=0;i<CHECK_TIMES;i++){
		cur+=adc_measure_data.adc1_dma_buff[4];
	}
	for(uint8_t i=0;i<3;i++)
		*offset=(float)cur/(float)CHECK_TIMES;
}
