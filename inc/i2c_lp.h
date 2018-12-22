#include "stm32f10x.h"
#include "macros.h"
#include "delays.h"

#define I2C_SDA_LOW_LP GPIO_ResetBits(GPIOC, GPIO_Pin_12);
#define I2C_SDA_HI_LP GPIO_SetBits(GPIOC, GPIO_Pin_12);
#define I2C_SDA_PORT_LP GPIOC
#define I2C_SDA_PIN_LP GPIO_Pin_12
#define I2C_SCL_LOW_LP GPIO_ResetBits(GPIOC, GPIO_Pin_11);
#define I2C_SCL_HI_LP GPIO_SetBits(GPIOC, GPIO_Pin_11);
