#include "stm32f10x.h"
#include "macros.h"
#include "delays.h"

#define SEG_SDI_PORT GPIOB
#define SEG_SDI_PIN GPIO_Pin_2
#define SEG_SDI_LOW GPIO_ResetBits(GPIOB, GPIO_Pin_2);
#define SEG_SDI_HI GPIO_SetBits(GPIOB, GPIO_Pin_2);

#define SEG_CLK_PORT GPIOC
#define SEG_CLK_PIN GPIO_Pin_4
#define SEG_CLK_LOW GPIO_ResetBits(GPIOC, GPIO_Pin_4);
#define SEG_CLK_HI GPIO_SetBits(GPIOC, GPIO_Pin_4);

#define SEG_LE_PORT GPIOC
#define SEG_LE_PIN GPIO_Pin_5
#define SEG_LE_LOW GPIO_ResetBits(GPIOC, GPIO_Pin_5);
#define SEG_LE_HI GPIO_SetBits(GPIOC, GPIO_Pin_5);


void slc_SetNumber(char ind_number, char value);
void slc_SetHours(unsigned char value);
void slc_SetMinutes(unsigned char value);
void RefreshSegments();
void SegDriverSend(short data, unsigned char latch_pulse);
