#include "amb_led_ctrl.h"

void mbi_refresh(void) {
	mbi_amb_send(0x01ff, 15);
	mbi_amb_send(0x01ff, 15);
	mbi_amb_send(0x01ff, 15);
	mbi_amb_send(0x01ff, 15);
	
	mbi_amb_send(0x01ff, 15);
	mbi_amb_send(0x01ff, 15);
	mbi_amb_send(0x01ff, 15);
	mbi_amb_send(0x01ff, 15);
	
	mbi_amb_send(0x01ff, 15);
	mbi_amb_send(0x01ff, 15);
	mbi_amb_send(0x01ff, 15);
	mbi_amb_send(0x01ff, 15);
	
	mbi_amb_send(0x01ff, 15);
	mbi_amb_send(0x01ff, 15);
	mbi_amb_send(0x01ff, 15);
	mbi_amb_send(0x01ff, 13);

}

void mbi_amb_send(int data, unsigned char latch_pulse) {
	unsigned char bit_counter = 0;
	for (bit_counter=0; bit_counter < 16; bit_counter++) {
		
		if (CHECK_BIT(data, 15)) {
			MBI_SDI_HI;
		}
		else {
			MBI_SDI_LOW;
		}
		
		if (bit_counter == latch_pulse) {
			MBI_LE_HI;
		}
		
		uSDelay(100);
		MBI_CLK_HI;
		uSDelay(100);
		MBI_CLK_LOW
		data = data << 1;
	}
	MBI_LE_LOW;
}
