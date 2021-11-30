#ifndef _user_usart_H
#define _user_usart_H

#include "stm32g4xx_hal.h"
#include "usart.h"
#include "stdio.h"

extern uint8_t  USART_TX_BUF_U3[200]; //发送缓冲,最大200字节，不能太小，如果你的内容太长会访问非法内存


#define _DEBUG_  1 	//串口打印宏函数开关，1是开，0是关，调试的时候开，调式完毕就可以一键关闭
/*------------------DEBUG DEFINE BEGIN------------------------*/
#if _DEBUG_
#define ps(...)  HAL_UART_Transmit(&huart3,USART_TX_BUF_U3,sprintf((char *)USART_TX_BUF_U3,__VA_ARGS__),0xffff);
#else
#define ps(...)
#endif
/*------------------DEBUG DEFINE END------------------------*/


#endif
