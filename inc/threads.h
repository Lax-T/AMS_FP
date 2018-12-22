#include "context.h"
#include "scheduler.h"
#include "light_sense.h"
#include "seg_led_ctrl.h"
#include "uart_protocol.h"
#include "ui_builder.h"
#include "stm32f10x.h"

#define TOGGLE_THREAD_ID 0
#define SEG_UPDATE_THREAD_ID 1
#define PROTOCOL_HANDLER_THREAD_ID 2
#define COMMAND_HANDLER_THREAD_ID 3
#define ANIMATE_THREAD_ID 4

void toggle_thread();
void seg_update_thread();
void ProtocolHandlerThread();
void CommandHandlerThread();
void AnimateThread();

#define CMD_SET_TIME_DISPLAY 10
#define CMD_SET_VIEW_ID 30
#define CMD_UPDATE_DISPLAY 31
#define CMD_SET_UI_SECTOR0 100
#define CMD_SET_UI_SECOTR1 101
#define CMD_SET_UI_SECTOR2 102
#define CMD_SET_UI_SECOTR3 103
