#ifndef __CONTROL_TASK_H
#define __CONTROL_TASK_H


#ifdef __cplusplus
extern "C" {
#endif

#include "user_hal.h"
#include "main.h"

typedef struct{
	volatile uint16_t adc1_dma_buff[8];
	volatile uint16_t A0_voltage;
	volatile uint16_t A1_voltage;
	volatile float input_voltage;
	volatile float output_voltage;
	volatile float output_current;
	volatile float output_power;
	volatile float Middle_Err;
}_adc_measure_data;

typedef struct{
	volatile int8_t phasea;
	volatile int8_t phaseb;
	volatile int8_t phaseaL;
	volatile int8_t phasebL;
	
	volatile int8_t btn_level;
	volatile int8_t data_event;
	volatile int32_t count;
	volatile uint32_t time_stamp;
}_encoder_data;

typedef struct{
	volatile uint8_t input_ovp_flag;
	volatile uint8_t input_uvp_flag;
	volatile uint8_t input_ocp_flag;
	volatile uint8_t output_ocp_flag;
}_fault_flag;


//typedef struct  
//{
//	float current_buffer[10];
//	float current_buffer2[10];
//	float out,out2;
//	uint16_t buffer_index;
//}_filter_handle;

//typedef struct  
//{
//	float voltage_out;
//	float current_out;
//	float power_out;
//	float voltage_in;
//	float motor1_pwm;
//	float motor2_pwm;
//	uint16_t charge_flag;
//	uint16_t pwm_out;
//}_power_set_data;

extern _adc_measure_data adc_measure_data;
extern _encoder_data encoder_data;
//extern _power_set_data power_set_data;

void adc_measure_init(void);
//void power_set_struct_init(_power_set_data* power_set_data);
void check_current_offset(float* offset);



#ifdef __cplusplus
}
#endif

#endif
