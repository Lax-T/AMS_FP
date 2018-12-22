#include "stm32f10x.h"
#include "macros.h"
#include "delays.h"

#define I2C_SDA_LOW GPIO_ResetBits(GPIOB, GPIO_Pin_7);
#define I2C_SDA_HI GPIO_SetBits(GPIOB, GPIO_Pin_7);
#define I2C_SDA_PORT GPIOB
#define I2C_SDA_PIN GPIO_Pin_7
#define I2C_SCL_LOW GPIO_ResetBits(GPIOB, GPIO_Pin_6);
#define I2C_SCL_HI GPIO_SetBits(GPIOB, GPIO_Pin_6);

void I2C_Start();
void I2C_Stop();
void I2C_SAck();
void I2C_MAck();
void I2C_MNAck();
void I2C_TXByte(unsigned char data);
unsigned char I2C_RXByte();
