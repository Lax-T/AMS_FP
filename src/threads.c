#include "threads.h"

unsigned char g_command_buffer[10];

unsigned char toggle = 0;
void toggle_thread() {
	if (toggle == 0) {
		toggle = 1;
		GPIO_SetBits(GPIOB, GPIO_Pin_12);
	}
	else {
		toggle = 0;
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	}

	//USART_SendData(USART1, 0x39);
	sch_ScheduleSelfRun(50);
}

void seg_update_thread() {

	/*
	unsigned short light_level = 0;
	light_level = lsns_ReadCh0Value();
	//slc_SetNumber(1, light_level/1000);
	light_level = light_level % 1000;
	slc_SetNumber(2, light_level/100);
	light_level = light_level % 100;
	slc_SetNumber(3, light_level/10);
	while (light_level > 9 ) {
		light_level = light_level - 10;
	}
	slc_SetNumber(4, light_level);*/

	sch_ScheduleSelfRun(100);
}

void CommandHandlerThread() {
	unsigned char cmd, temp, adr_offset, i;
	cmd = g_command_buffer[0];

	switch (cmd) {
	case CMD_SET_TIME_DISPLAY:
		slc_SetHours(g_command_buffer[1]);
		slc_SetMinutes(g_command_buffer[2]);
		break;

	case CMD_SET_VIEW_ID:
		gc_SetGlobalValue(C_UI_VIEW_ID, g_command_buffer[1]);
		break;

	case CMD_UPDATE_DISPLAY:
		ui_UpdateUI();
		break;

	case CMD_SET_UI_SECTOR0:
	case CMD_SET_UI_SECOTR1:
	case CMD_SET_UI_SECTOR2:
	case CMD_SET_UI_SECOTR3:
		adr_offset = (cmd - CMD_SET_UI_SECTOR0) * 4;
		for (i=0; i < 4; i++) {
			ui_SetUIVar((adr_offset + i), g_command_buffer[i + 1]);
		}
		break;
	}

	/*
	unsigned char cmd, temp, adr_offset, i;
	cmd = g_command_buffer[0];
	switch (cmd) {
	case 1: // Set UI vars
		temp = g_command_buffer[1];
		slc_SetNumber(1, temp / 10);
		slc_SetNumber(2, temp % 10);
		temp = g_command_buffer[2];
		slc_SetNumber(3, temp / 10);
		slc_SetNumber(4, temp % 10);
		break;

	case 2: // Set UI vars
		adr_offset = g_command_buffer[1];
		for (i=0; i < 4; i++) {
			ui_SetUIVar((adr_offset + i), g_command_buffer[i + 2]);
		}
		ui_UpdateUI();
		break;
	}*/
}

void ProtocolHandlerThread() {
	if (up_GetRXState() == UART_PEND_PROCESSING) {
		if (up_ExtractData(g_command_buffer, 0) == UART_PACKET_OK) {
			USART_SendData(USART1, 0x31);
		}
		else {
			USART_SendData(USART1, 0x30);
		}
	}
	else {
		USART_SendData(USART1, 0x39);
	}
	up_ResetRXFIFO();
	up_SetRXState(UART_WAIT_START_SYMB);
	sch_ScheduleThreadRun(COMMAND_HANDLER_THREAD_ID, THREAD_RUN_NOW);
}


void AnimateThread() {
	unsigned int temp;
	static unsigned char step = 0;
	static unsigned char direction = 0;

	if (direction == 0) {
		step++;
		if (step >= 25)  {
			direction = 1;
		}
	}
	else {
		step--;
		if (step == 0)  {
			direction = 0;
		}
	}
	temp = (unsigned int)(80 * step);
	TIM_SetCompare4(TIM3, temp + 10);
	sch_ScheduleSelfRun(4);
}

