#include "lcd_ctrl.h"

void SetDatabits(unsigned char data) {
	if (CHECK_BIT(data, 0)) {LCD_D0_HI;}
		else {LCD_D0_LOW;}
	if (CHECK_BIT(data, 1)) {LCD_D1_HI;}
		else {LCD_D1_LOW;}
	if (CHECK_BIT(data, 2)) {LCD_D2_HI;}
		else {LCD_D2_LOW;}
	if (CHECK_BIT(data, 3)) {LCD_D3_HI;}
		else {LCD_D3_LOW;}
	if (CHECK_BIT(data, 4)) {LCD_D4_HI;}
		else {LCD_D4_LOW;}
	if (CHECK_BIT(data, 5)) {LCD_D5_HI;}
		else {LCD_D5_LOW;}
	if (CHECK_BIT(data, 6)) {LCD_D6_HI;}
		else {LCD_D6_LOW;}
	if (CHECK_BIT(data, 7)) {LCD_D7_HI;}
		else {LCD_D7_LOW;}
}

void SendByte(unsigned char data) {
	LCD_E_HI;
	SetDatabits(data);
	uSDelay(USDELAY_CALC(1));
	LCD_E_LOW;
	uSDelay(USDELAY_CALC(1));
}

void SetY(unsigned char y_address) {
	y_address = y_address | 0x40;
	LCD_DI_LOW;
	uSDelay(USDELAY_CALC(1));
	LCD_E_HI;
	SetDatabits(y_address);
	uSDelay(USDELAY_CALC(1));
	LCD_E_LOW;
	uSDelay(USDELAY_CALC(1));
	LCD_DI_HI;
	uSDelay(USDELAY_CALC(1));
}

void SetX(unsigned char x_address) {
	x_address = x_address | 0xB8;
	LCD_DI_LOW;
	uSDelay(USDELAY_CALC(1));
	LCD_E_HI;
	SetDatabits(x_address);
	uSDelay(USDELAY_CALC(1));
	LCD_E_LOW;
	uSDelay(USDELAY_CALC(1));
	LCD_DI_HI;
	uSDelay(USDELAY_CALC(1));
}

void lc_ClearLcd() {
	LCD_CS1_LOW;
	LCD_CS2_LOW;
	char x=0;
	char y=0;
	for (x=0; x<8; x++) {
		SetX(x);
		SetY(0);
		for (y=0; y<64; y++) {
			SendByte(0x00);
		}
	}
	LCD_CS1_HI;
	LCD_CS2_HI;
}

void lc_RefreshLCD(unsigned char buffer[]) {
	char x=0;
	char y=0;
	unsigned short pointer=0;
	LCD_CS1_LOW;
	for (x=0; x<8; x++) {
		SetX(x);
		SetY(0);
		for (y=0; y<64; y++) {
			SendByte(buffer[pointer+y]);
		}
		pointer += 128;
	}
	LCD_CS1_HI;
	LCD_CS2_LOW;
	pointer = 64;
	for (x=0; x<8; x++) {
		SetX(x);
		SetY(0);
		for (y=0; y<64; y++) {
			SendByte(buffer[pointer+y]);
		}
		pointer += 128;
	}
	LCD_CS2_HI;
}

void lc_GLCDPowerOn() {
	LCD_DDIR_LOW;
	LCD_RW_LOW;
	LCD_E_LOW;
	LCD_DI_LOW;
	LCD_RST_LOW;
	LCD_CS1_LOW;
	LCD_CS2_LOW;
	SetDatabits(0x00);
	LCD_PWR_HI;
	uSDelay(USDELAY_CALC(10));
	LCD_BOE_LOW;
	mSDelay(5);
	DAC_SetChannel1Data(DAC_Align_12b_R, 0x0900);
	LCD_RST_HI;
	mSDelay(1);
	LCD_RST_LOW;
	mSDelay(2);
	LCD_RST_HI;
	SendByte(0x3F);
	LCD_DI_HI;
	lc_ClearLcd();


	LCD_CS1_LOW;
	LCD_CS2_LOW;
	SetX(0);
	SetY(0);
	SendByte(0x51);
	SendByte(0x91);
	SendByte(0xFF);
	LCD_CS1_HI;
	LCD_CS1_HI;
}
