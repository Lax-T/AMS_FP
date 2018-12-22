#include "seg_led_ctrl.h"

#define BR_level 0x9fff

const unsigned char IND1_SEGMENTS[] = {26, 20, 4, 2, 0, 28, 30, 6};
const unsigned char IND2_SEGMENTS[] = {22, 24, 10, 14, 8, 16, 18, 12};
const unsigned char IND3_SEGMENTS[] = {11, 9, 21, 19, 17, 13, 15, 23};
const unsigned char IND4_SEGMENTS[] = {3, 1, 29, 27, 25, 5, 7, 31};
const unsigned char NUM_TO_7SEG[] = {0xfc, 0x60, 0xda, 0xf2, 0x66, 0xb6, 0xbe, 0xe0, 0xfe, 0xf6};

//0 2 4 6 8 10 12 14 16 18 20 22 24 26 28 30 (ind 1, 2)
//1 3 5 7 9 11 13 15 17 19 21 23 25 27 29 31 (ind 3, 4)

unsigned short brt_level = 2000;
unsigned char hour = 0;
unsigned char minute = 0;
unsigned short seg_buff[32];

void MapValueToSegmentsBuffer(unsigned char value, const unsigned char segments_buff_adr[8]) {
	unsigned char mask = NUM_TO_7SEG[value];
	unsigned char i;
	unsigned char segment_adr;
	for (i=0; i<8; i++) {
		segment_adr = segments_buff_adr[i];
		if (CHECK_BIT(mask, 7)) {
			seg_buff[segment_adr] = brt_level;
		}
		else {
			seg_buff[segment_adr] = 0;
		}
		mask = mask << 1;
	}
}

void slc_SetHours(unsigned char value) {
	slc_SetNumber(1, value / 10);
	slc_SetNumber(2, value % 10);
}

void slc_SetMinutes(unsigned char value) {
	slc_SetNumber(3, value / 10);
	slc_SetNumber(4, value % 10);
}

void slc_SetNumber(char ind_number, char value) {
	switch (ind_number) {
	case 1:
		MapValueToSegmentsBuffer(value, IND1_SEGMENTS);
		break;
	case 2:
		MapValueToSegmentsBuffer(value, IND2_SEGMENTS);
		break;
	case 3:
		MapValueToSegmentsBuffer(value, IND3_SEGMENTS);
		break;
	case 4:
		MapValueToSegmentsBuffer(value, IND4_SEGMENTS);
		break;
	}
	RefreshSegments();
}


void RefreshSegments() {
	SEG_LE_LOW;
	SEG_CLK_LOW;
	
	unsigned char i;
	unsigned char p=0;
	for (i=0;i<31;i++) {
		if (p == 0) {
			p = 1;
			SegDriverSend(seg_buff[i], 16);
		}
		else {
			p = 0;
			SegDriverSend(seg_buff[i], 15);
		}
	}
	SegDriverSend(seg_buff[31], 13);
}

void SegDriverSend(short data, unsigned char latch_pulse) {
	unsigned char bit_counter = 0;
	for (bit_counter=0; bit_counter < 16; bit_counter++) {
		
		if (CHECK_BIT(data, 15)) {
			SEG_SDI_HI;
		}
		else {
			SEG_SDI_LOW;
		}
		
		if (bit_counter == latch_pulse) {
			SEG_LE_HI;
		}
		
		uSDelay(100);
		SEG_CLK_HI;
		uSDelay(100);
		SEG_CLK_LOW;
		data = data << 1;
	}
	SEG_LE_LOW;
}
