#include "stm32f10x.h"
#include "macros.h"
#include "delays.h"

#define MBI_SDI_PORT GPIOA
#define MBI_SDI_PIN GPIO_Pin_5
#define MBI_SDI_LOW GPIO_ResetBits(GPIOA, GPIO_Pin_5);
#define MBI_SDI_HI GPIO_SetBits(GPIOA, GPIO_Pin_5);

#define MBI_CLK_PORT GPIOA
#define MBI_CLK_PIN GPIO_Pin_6
#define MBI_CLK_LOW GPIO_ResetBits(GPIOA, GPIO_Pin_6);
#define MBI_CLK_HI GPIO_SetBits(GPIOA, GPIO_Pin_6);

#define MBI_LE_PORT GPIOA
#define MBI_LE_PIN GPIO_Pin_7
#define MBI_LE_LOW GPIO_ResetBits(GPIOA, GPIO_Pin_7);
#define MBI_LE_HI GPIO_SetBits(GPIOA, GPIO_Pin_7);


void mbi_amb_send(int data, unsigned char latch_pulse);
void mbi_refresh(void);
