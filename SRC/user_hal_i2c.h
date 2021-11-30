/**
  ******************************************************************************
  * @file    user_hal_i2c.h
  * @author  mxy in NJUST 6003 Team
  * @brief   GPIO HAL module driver.
  */
	

#ifndef __user_hal_i2c_h__
#define __user_hal_i2c_h__

#include "HAL_conf.h"
#include "user_hal.h"
#include "user_hal_lib.h"

typedef struct
{
    //Flag of whether I2C is transmitting
    uint8_t busy;
	
    uint8_t ack;
    //Flag of whether I2C is right
    uint8_t fault;
    //Flag of I2C transmission direction
    uint8_t opt;
    //sub address
    uint8_t sub;
    //number
    uint8_t cnt;
    //buffer
    uint8_t *ptr;
    //used to determine if sub addresses need to be sent in interrupt
    uint8_t sadd;
} i2c_def;

void MX_I2C1_Init(void);

#endif
