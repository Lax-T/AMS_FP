#include "stm32f10x.h"
#include "macros.h"
#include "delays.h"

#define LCD_D0_LOW GPIO_ResetBits(GPIOB, GPIO_Pin_9);
#define LCD_D0_HI GPIO_SetBits(GPIOB, GPIO_Pin_9);
#define LCD_D1_LOW GPIO_ResetBits(GPIOB, GPIO_Pin_8);
#define LCD_D1_HI GPIO_SetBits(GPIOB, GPIO_Pin_8);
#define LCD_D2_LOW GPIO_ResetBits(GPIOB, GPIO_Pin_5);
#define LCD_D2_HI GPIO_SetBits(GPIOB, GPIO_Pin_5);
#define LCD_D3_LOW GPIO_ResetBits(GPIOB, GPIO_Pin_4);
#define LCD_D3_HI GPIO_SetBits(GPIOB, GPIO_Pin_4);

#define LCD_D4_LOW GPIO_ResetBits(GPIOB, GPIO_Pin_3);
#define LCD_D4_HI GPIO_SetBits(GPIOB, GPIO_Pin_3);
#define LCD_D5_LOW GPIO_ResetBits(GPIOD, GPIO_Pin_2);
#define LCD_D5_HI GPIO_SetBits(GPIOD, GPIO_Pin_2);
#define LCD_D6_LOW GPIO_ResetBits(GPIOC, GPIO_Pin_12);
#define LCD_D6_HI GPIO_SetBits(GPIOC, GPIO_Pin_12);
#define LCD_D7_LOW GPIO_ResetBits(GPIOC, GPIO_Pin_11);
#define LCD_D7_HI GPIO_SetBits(GPIOC, GPIO_Pin_11);

#define LCD_CS1_LOW GPIO_ResetBits(GPIOA, GPIO_Pin_12);
#define LCD_CS1_HI GPIO_SetBits(GPIOA, GPIO_Pin_12);
#define LCD_CS2_LOW GPIO_ResetBits(GPIOA, GPIO_Pin_11);
#define LCD_CS2_HI GPIO_SetBits(GPIOA, GPIO_Pin_11);
#define LCD_RST_LOW GPIO_ResetBits(GPIOA, GPIO_Pin_8);
#define LCD_RST_HI GPIO_SetBits(GPIOA, GPIO_Pin_8);

#define LCD_RW_LOW GPIO_ResetBits(GPIOB, GPIO_Pin_15);
#define LCD_RW_HI GPIO_SetBits(GPIOB, GPIO_Pin_15);
#define LCD_DI_LOW GPIO_ResetBits(GPIOB, GPIO_Pin_14);
#define LCD_DI_HI GPIO_SetBits(GPIOB, GPIO_Pin_14);
#define LCD_E_LOW GPIO_ResetBits(GPIOB, GPIO_Pin_13);
#define LCD_E_HI GPIO_SetBits(GPIOB, GPIO_Pin_13);

#define LCD_PWR_LOW GPIO_ResetBits(GPIOA, GPIO_Pin_1);
#define LCD_PWR_HI GPIO_SetBits(GPIOA, GPIO_Pin_1);
#define LCD_BOE_LOW GPIO_ResetBits(GPIOC, GPIO_Pin_10);
#define LCD_BOE_HI GPIO_SetBits(GPIOC, GPIO_Pin_10);
#define LCD_DDIR_LOW GPIO_ResetBits(GPIOA, GPIO_Pin_15);
#define LCD_DDIR_HI GPIO_SetBits(GPIOA, GPIO_Pin_15);

void lc_GLCDPowerOn();
void lc_RefreshLCD();

