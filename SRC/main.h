/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  */

#ifndef __MAIN_H
#define __MAIN_H

#include "user_hal.h"

#define SPI2_CS_Port         GPIOC
#define SPI2_CS_Pin          GPIO_Pin_7
#define SPI2_DC_Port         GPIOB
#define SPI2_DC_Pin          GPIO_Pin_15
#define SPI2_Reset_Port      GPIOB
#define SPI2_Reset_Pin       GPIO_Pin_14

#define Rotate_A_Pin				 GPIO_Pin_4
#define Rotate_A_Port				 GPIOD
#define Rotate_B_Pin				 GPIO_Pin_5
#define Rotate_B_Port				 GPIOD
#define Rotate_Btn_Pin			 GPIO_Pin_4
#define Rotate_Btn_Port			 GPIOB





#endif
