#include "init.h"
#include "delays.h"
#include "amb_led_ctrl.h"
#include "seg_led_ctrl.h"
#include "lcd_ctrl.h"
#include "light_sense.h"
#include "scheduler.h"
#include "threads.h"
#include "ui_builder.h"
#include "uart_protocol.h"
#include "stm32f10x.h"

/*
void do_smth() {
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
}

void (*thread_pointers[1])() = {do_smth};*/

// SysTick interrupt handler (scheduler time counter)
void SysTick_Handler() {
	sch_SchedulerTickInt();
}

void USART1_IRQHandler() {
	unsigned char temp, data;
	if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET) {
		data = USART_ReceiveData(USART1) & 0x00ff;
		temp = up_ProcessRXINT(data);
		switch (temp) {
		case UART_THREAD_NOP:
			sch_IntScheduleThreadRun(PROTOCOL_HANDLER_THREAD_ID, THREAD_SLEEP);
			break;
		case UART_THREAD_SET_TOUT:
			sch_IntScheduleThreadRun(PROTOCOL_HANDLER_THREAD_ID, 50);
			break;
		case UART_THREAD_RUN_NOW:
			sch_IntScheduleThreadRun(PROTOCOL_HANDLER_THREAD_ID, THREAD_RUN_NOW);
			break;
		}
	}

	/*unsigned char temp, data;
	if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET) {
		if (up_GetRXState() == UART_RX_READY_STATE) {
			data = USART_ReceiveData(USART1) & 0x00ff;
			temp = up_PutRXFIFO(data);
			if (temp >= UART_RX_PACKET_SIZE) {
				up_SetRXState(UART_PEND_PROCESS_STATE);
				sch_IntScheduleThreadRun(PROTOCOL_HANDLER_THREAD_ID, 1, PROTOCOL_HANDLER_THREAD_ID);
			}
			else {
				sch_IntScheduleThreadRun(PROTOCOL_HANDLER_THREAD_ID, 50, PROTOCOL_HANDLER_THREAD_ID);
			}
		}
	}*/

	/*
	temp = USART_ReceiveData(USART1) & 0x00ff;
	temp = temp - 0x30;
	slc_SetNumber(1, temp);*/
}

int main() {
	StartupInit();
	char x = 0;
	unsigned short light_level = 0;

	mbi_refresh();
	slc_SetNumber(1, 2);
	slc_SetNumber(2, 3);
	slc_SetNumber(3, 2);
	slc_SetNumber(4, 6);
	GPIO_SetBits(GPIOB, GPIO_Pin_0);
	
	lc_GLCDPowerOn();
	//lc_RefreshLCD(image);
	ui_UpdateUI();

	lsns_PowerUp();

	sch_InitScheduler();
	sch_RegisterThread(toggle_thread, TOGGLE_THREAD_ID, 5, 10);
	sch_RegisterThread(seg_update_thread, SEG_UPDATE_THREAD_ID, 5, 100);
	sch_RegisterThread(ProtocolHandlerThread, PROTOCOL_HANDLER_THREAD_ID, 1, THREAD_SLEEP);
	sch_RegisterThread(CommandHandlerThread, COMMAND_HANDLER_THREAD_ID, 1, THREAD_SLEEP);
	sch_RegisterThread(AnimateThread, ANIMATE_THREAD_ID, 0, 4);

	//up_SetRXState(UART_RX_READY_STATE);
	sch_RunScheduler();

	/*
	while (1) {


		mSDelay(1000);
		if (x == 0) {

			//GPIO_SetBits(GPIOB, GPIO_Pin_12);
			//(*thread_pointers[0])();
			light_level = lsns_ReadCh0Value();
			slc_SetNumber(1, light_level/1000);
			light_level = light_level % 1000;
			slc_SetNumber(2, light_level/100);
			light_level = light_level % 100;
			slc_SetNumber(3, light_level/10);
			while (light_level > 9 ) {
				light_level = light_level - 10;
			}
			slc_SetNumber(4, light_level);
			x = 1;
		}
		else {
			//GPIO_ResetBits(GPIOB, GPIO_Pin_12);
			
			x = 0;
		}
	}*/
}
