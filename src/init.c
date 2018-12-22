#include "init.h"

	GPIO_InitTypeDef gpio;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef timerPWM;
	DAC_InitTypeDef DACinit;
	USART_InitTypeDef USARTInitStruct;

void StartupInit() {

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6 , ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
	RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);
	RCC_PLLCmd(DISABLE);
	RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_4);
	RCC_PLLCmd(ENABLE);
	while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
		{
		}
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	//
	GPIO_SetBits(GPIOC, GPIO_Pin_10);// Set LCD buffers to Z state
	GPIO_ResetBits(GPIOA, GPIO_Pin_1); // Disable LCD power
	// PORT D init
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio.GPIO_Pin = GPIO_Pin_2;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &gpio);
	// PORT C init
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_7 | GPIO_Pin_8;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &gpio);

	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &gpio);
	GPIO_SetBits(GPIOC, GPIO_Pin_10);// Set LCD buffers to Z state
	// PORT B init
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio.GPIO_Pin = GPIO_Pin_1;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &gpio);

	gpio.GPIO_Mode = GPIO_Mode_Out_OD;
	gpio.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &gpio);
	GPIO_SetBits(GPIOB, GPIO_Pin_12);

	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &gpio);
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	// PORT A init
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_9;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio);

	gpio.GPIO_Mode = GPIO_Mode_AIN;
	gpio.GPIO_Pin = GPIO_Pin_4;
	GPIO_Init(GPIOA, &gpio);

	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_15;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio);
	GPIO_ResetBits(GPIOA, GPIO_Pin_1); // Disable LCD power
	// Timers init
	TIM_TimeBaseStructure.TIM_Period  = 0xffff;
	TIM_TimeBaseStructure.TIM_Prescaler = (1)-1;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode =  TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);
	TIM_Cmd(TIM6, ENABLE);
	//TIMER 2 GRAYSCALE CLOCK
	TIM_TimeBaseStructure.TIM_Period  = 0x0004;
	TIM_TimeBaseStructure.TIM_Prescaler = (1)-1;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode =  TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	TIM_Cmd(TIM2, ENABLE);

	timerPWM.TIM_OCMode = TIM_OCMode_PWM1;
	timerPWM.TIM_OutputState = TIM_OutputState_Enable;
	timerPWM.TIM_Pulse = 0x0002;
	timerPWM.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC3Init(TIM2, &timerPWM);
	//TIMER 8 LCD BACKLIGHT
	TIM_TimeBaseStructure.TIM_Period  = 0xAFFF;
	TIM_TimeBaseStructure.TIM_Prescaler = (1)-1;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode =  TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);

	timerPWM.TIM_OCMode = TIM_OCMode_PWM1;
	timerPWM.TIM_OutputState = TIM_OutputState_Enable;
	timerPWM.TIM_OutputNState = TIM_OutputNState_Disable;
	timerPWM.TIM_Pulse = 0x1500;
	timerPWM.TIM_OCPolarity = TIM_OCPolarity_High;
	timerPWM.TIM_OCNPolarity = TIM_OCPolarity_High;
	timerPWM.TIM_OCIdleState = TIM_OCIdleState_Reset;
	timerPWM.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	TIM_OC4Init(TIM8, &timerPWM);
	timerPWM.TIM_Pulse = 0x8500;
	TIM_OC3Init(TIM8, &timerPWM);
	timerPWM.TIM_Pulse = 0x0100;
	TIM_OC2Init(TIM8, &timerPWM);
	TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM8, ENABLE);
	TIM_CtrlPWMOutputs(TIM8, ENABLE);
	TIM_Cmd(TIM8, ENABLE);

	//TIMER 3 SEPARATOR
	TIM_TimeBaseStructure.TIM_Period  = 0xFFFF;
	TIM_TimeBaseStructure.TIM_Prescaler = (1)-1;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode =  TIM_CounterMode_CenterAligned1;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	timerPWM.TIM_OCMode = TIM_OCMode_PWM1;
	timerPWM.TIM_OutputState = TIM_OutputState_Enable;
	//timerPWM.TIM_OutputNState = TIM_OutputNState_Disable;
	timerPWM.TIM_Pulse = 0x0800;
	timerPWM.TIM_OCPolarity = TIM_OCPolarity_High;
	//timerPWM.TIM_OCNPolarity = TIM_OCPolarity_High;
	//timerPWM.TIM_OCIdleState = TIM_OCIdleState_Reset;
	//timerPWM.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	TIM_OC4Init(TIM3, &timerPWM);
	//TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM3, ENABLE);
	//TIM_CtrlPWMOutputs(TIM3, ENABLE);
	TIM_Cmd(TIM3, ENABLE);

	// LCD bias DAC init
	DACinit.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
	DAC_Init(DAC_Channel_1, &DACinit);
	DAC_SetChannel1Data(DAC_Align_12b_R, 0x0000);
	DAC_Cmd(DAC_Channel_1, ENABLE);
	// SysTick configuration
	SysTick_Config(320000);
	// UART init
	USARTInitStruct.USART_BaudRate = 128000;
	USARTInitStruct.USART_WordLength = USART_WordLength_8b;
	USARTInitStruct.USART_StopBits = USART_StopBits_1;
	USARTInitStruct.USART_Parity = USART_Parity_No;
	USARTInitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USARTInitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART1, &USARTInitStruct);
	USART_Cmd(USART1, ENABLE);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	//USART int enable
	NVIC_InitTypeDef nvicStructure;
	nvicStructure.NVIC_IRQChannel = USART1_IRQn;
	nvicStructure.NVIC_IRQChannelPreemptionPriority = 0;
	nvicStructure.NVIC_IRQChannelSubPriority = 1;
	nvicStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvicStructure);

	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
}
