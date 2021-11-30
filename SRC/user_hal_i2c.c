/**
  ******************************************************************************
  * @file    user_hal_lib.c
  * @author  mxy in NJUST 6003 Team
  * @brief   GPIO HAL module driver.
  */
	
/* Includes ------------------------------------------------------------------*/

#include "user_hal_i2c.h"
#include "string.h"
//Device address of SSD1306
#define SSD1306_ADDR 0x3C

i2c_def i2c;

static void I2C_MasterMode_Init(I2C_TypeDef *I2Cx, u32 uiI2C_speed)
{
    I2C_InitTypeDef I2C_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);

    GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_1);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_1);

    //I2C uses PB10, PB11
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_20MHz;
    //Need extra pull
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    //Configure I2C as master mode
    I2C_InitStructure.I2C_Mode = I2C_Mode_MASTER;
    I2C_InitStructure.I2C_OwnAddress = 0;
    I2C_InitStructure.I2C_Speed = I2C_Speed_STANDARD;
    I2C_InitStructure.I2C_ClockSpeed = uiI2C_speed;

    I2C_Init(I2Cx, &I2C_InitStructure);
    I2C_Cmd(I2Cx, ENABLE);

}

/*******************************************************************************
* @name             : I2CSetDeviceAddr
* @brief            : Set the device address
* @param I2Cx       : where x can be 1 or 2 to select the I2C peripheral.
* @param deviceaddr : device address
* @retval           : void
*******************************************************************************/
static void I2CSetDeviceAddr(I2C_TypeDef *I2Cx, u8 deviceaddr)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    //I2C uses PB10, PB11
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10 | GPIO_Pin_11;

    //Set GPIO spped
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_20MHz;
    //Keep the bus free which means SCK & SDA is high
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    I2C_Cmd(I2Cx, DISABLE);
    //Set the device address
    I2C_Send7bitAddress(I2Cx, deviceaddr, I2C_Direction_Transmitter);
    I2C_Cmd(I2Cx, ENABLE);

    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_20MHz;
    //Need extra pull
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void MX_I2C1_Init(void)
{
    //Initial value of i2c struct
    memset(&i2c, 0x00, sizeof(i2c));
    //Initializes the I2C master mode
    I2C_MasterMode_Init(I2C1, 100000);
    //Set the SSD1306 address
    I2CSetDeviceAddr(I2C1, SSD1306_ADDR);
}
