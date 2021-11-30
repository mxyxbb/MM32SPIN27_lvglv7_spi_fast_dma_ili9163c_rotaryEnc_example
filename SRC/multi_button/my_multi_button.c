#include "multi_button/multi_button.h"
#include "user_hal.h"
#include "main.h"
#include "lvgl_app.h"

uint8_t read_button1_GPIO(void);
uint8_t read_button2_GPIO(void);


void BTN1_SINGLE_Click_Handler(void* btn);
void BTN2_SINGLE_Click_Handler(void* btn);
void BTN1_LONG_PRESS_START_Handler(void* btn);
void BTN2_LONG_PRESS_START_Handler(void* btn);
void BTN1_DOUBLE_Click_Handler(void* btn);
void BTN2_DOUBLE_Click_Handler(void* btn);
void BTN1_LONG_PRESS_HOLD_Handler(void* btn);
void BTN2_LONG_PRESS_HOLD_Handler(void* btn);	

struct Button button1;
struct Button button2;

void my_button_init(void)
{
	button_init(&button1, read_button1_GPIO, 0);//multibtn初始化
	button_init(&button2, read_button2_GPIO, 0);//multibtn初始化
	
//	button_attach(&button1, PRESS_DOWN,       BTN1_PRESS_DOWN_Handler);
//	button_attach(&btn1, PRESS_UP,         BTN1_PRESS_UP_Handler);
//	button_attach(&btn1, PRESS_REPEAT,     BTN1_PRESS_REPEAT_Handler);
	button_attach(&button1, SINGLE_CLICK,     BTN1_SINGLE_Click_Handler);
	button_attach(&button1, DOUBLE_CLICK,     BTN1_DOUBLE_Click_Handler);
//	button_attach(&button1, LONG_PRESS_START, BTN1_LONG_PRESS_START_Handler);
	button_attach(&button1, LONG_PRESS_HOLD,  BTN1_LONG_PRESS_HOLD_Handler);

//	button_attach(&button2, PRESS_DOWN,       BTN2_PRESS_DOWN_Handler);
//	button_attach(&btn2, PRESS_UP,         BTN2_PRESS_UP_Handler);
//	button_attach(&btn2, PRESS_REPEAT,     BTN2_PRESS_REPEAT_Handler);
	button_attach(&button2, SINGLE_CLICK,     BTN2_SINGLE_Click_Handler);
	button_attach(&button2, DOUBLE_CLICK,     BTN2_DOUBLE_Click_Handler);
//	button_attach(&button2, LONG_PRESS_START, BTN2_LONG_PRESS_START_Handler);
	button_attach(&button2, LONG_PRESS_HOLD,  BTN2_LONG_PRESS_HOLD_Handler);
	button_start(&button1);
	button_start(&button2);
}

void BTN1_SINGLE_Click_Handler(void* btn)
{
	HAL_GPIO_TogglePin(GPIOB,GPIO_Pin_10);
//	lv_btn_toggle(btn2);
}

void BTN2_SINGLE_Click_Handler(void* btn)
{

}

void BTN1_DOUBLE_Click_Handler(void* btn)
{

}
void BTN2_DOUBLE_Click_Handler(void* btn)
{
	
}


//void BTN1_LONG_PRESS_START_Handler(void* btn)
//{
//	buzzer_flag=1;

//}

//void BTN2_LONG_PRESS_START_Handler(void* btn)
//{
//	buzzer_flag=1;

//}

void BTN1_LONG_PRESS_HOLD_Handler(void* btn)
{

}

void BTN2_LONG_PRESS_HOLD_Handler(void* btn)
{
	
}

uint8_t read_button1_GPIO()
{
	return GPIO_ReadInputDataBit(Rotate_Btn_Port,Rotate_Btn_Pin);
}
uint8_t read_button2_GPIO()
{
	return GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2);
}