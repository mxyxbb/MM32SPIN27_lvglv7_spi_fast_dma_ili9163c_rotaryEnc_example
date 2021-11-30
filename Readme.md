# MM32SPIN27PS improve project

## -MM32SPIN27PS HAL_lib

## -MM32SPIN27PS IOSELECT

## -LVGL-v7.11 demo

- MCU: MM32SPIN27PS "128k Flash + 12k Sram"
- 使用硬件SPI+DMA发送数据，刷屏速率约15FPS
- 使用旋转编码器Rotary Encoder作为输入设备
- 驱动1.8寸LCD屏幕ili9163c作为显示设备（162*132）

本工程在`lv_conf.h`中定义的缓冲区长度为5kB，缓冲区过小时，若绘制过多的控件将导致lvgl卡死。

```c
/* Size of the memory used by `lv_mem_alloc` in bytes (>= 2kB)*/
define LV_MEM_SIZE    (5U * 1024U)
```

本工程的空间总开销如下：

```c
Total RO  Size (Code + RO Data)               111588 ( 108.97kB)
Total RW  Size (RW Data + ZI Data)             11528 (  11.26kB)
Total ROM Size (Code + RO Data + RW Data)     111860 ( 109.24kB)
```

本工程配置了8路4对互补PWM（TIM1、TIM8），插入了约450ns的死区，用于驱动H桥电路，控制电机。

- 本工程配置了使用TIM1的TRGO事件触发8通道ADC采样，使用DMA方式搬运ADC数据，采样完成后产生ADC采样完成中断；
- 通过TIM1的通道3产生TRGO事件，设置TRGO事件在PWM下降沿之后一段时间再产生，以避开PWM对ADC采样的干扰。

本工程配置了TIM2、TIM3为编码器模式，用作正交编码器接口。

本工程仿照STM32的HAL库，编写了简陋的MM32_HAL库，支持了以下函数，在一定程度上可以方便MM32SPIN27的引脚配置。

配置了Systick，支持最常用的延时函数和GetTick函数，声明了全局变量uwtick。

```c
void HAL_Delay(uint32_t Delay);
uint32_t HAL_GetTick(void);
```

支持开启定时器，开启定时器中断，开启编码器模式，并支持了一些中断回调函数。

```C
void MX_GPIO_Init(void);
void MX_DMA_Init(void);
void MX_ADC1_Init(void);
void HAL_ADC_Start_DMA(ADC_TypeDef * ADCx, uint32_t *pData, uint32_t Length);
void HAL_ADC_ConvCpltCallback(ADC_TypeDef * hadc);
void MX_TIM1_Init(void);
void MX_TIM2_Init(void);
void MX_TIM3_Init(void);
void MX_TIM8_Init(void);
void MX_TIM14_Init(void);
void HAL_TIM_Base_Start(TIM_TypeDef * htim);
void HAL_TIM_PWM_Start(TIM_TypeDef * htim);
void HAL_TIM_Base_Start_IT(TIM_TypeDef * htim);
void HAL_TIM_Encoder_Start(TIM_TypeDef * htim);
void HAL_TIM_PeriodElapsedCallback(TIM_TypeDef * htim);
void HAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, BitAction BitVal);
void MX_EXTI_Init(void);
void HAL_GPIO_EXTI_Callback(uint32_t EXTI_Linex);
```

对于SPI的实现比较简略，仅支持SPI2，建议使用者先阅读源码后再使用。

```c
void MX_SPI2_Init(void);
void HAL_SPI_Transmit(SPI_TypeDef *SPIx, uint8_t *pData, uint16_t Size, uint32_t Timeout);
void HAL_SPI_Transmit_DMA(SPI_TypeDef *SPIx, uint8_t *pData, uint16_t Size);
```

参考HK32F030M_IOSELECT.xlsx，制作了MM32_IOSELECT.xlsx，进一步方便了MM32SPIN27的引脚配置。

![IO__](https://i.loli.net/2021/11/30/9NvdVgjYr3Rz5ZC.png)

## 实物预览

![pic1](https://i.loli.net/2021/11/30/vKRoZk6TVO54CAg.png)

![pic2](https://i.loli.net/2021/11/30/sY7rmv5EzydNoL2.png)