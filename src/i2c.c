#include "i2c.h"

void I2C_Start() {
	I2C_SDA_HI;
	uSDelay(USDELAY_CALC(4));
	I2C_SCL_HI;
	uSDelay(USDELAY_CALC(4));
	I2C_SDA_LOW;
	uSDelay(USDELAY_CALC(4));
	I2C_SCL_LOW;
}

void I2C_Stop() {
	I2C_SDA_LOW;
	uSDelay(USDELAY_CALC(4));
	I2C_SCL_HI;
	uSDelay(USDELAY_CALC(4));
	I2C_SDA_HI;
	uSDelay(USDELAY_CALC(4));
}

void I2C_SAck() {
	I2C_SDA_HI;
	uSDelay(USDELAY_CALC(4));
	I2C_SCL_HI;
	uSDelay(USDELAY_CALC(4));
	I2C_SCL_LOW;
	uSDelay(USDELAY_CALC(4));
}

void I2C_MAck() {
	I2C_SDA_LOW;
	uSDelay(USDELAY_CALC(4));
	I2C_SCL_HI;
	uSDelay(USDELAY_CALC(4));
	I2C_SCL_LOW;
	uSDelay(USDELAY_CALC(4));
}

void I2C_MNAck() {
	I2C_SDA_HI;
	uSDelay(USDELAY_CALC(4));
	I2C_SCL_HI;
	uSDelay(USDELAY_CALC(4));
	I2C_SCL_LOW;
	uSDelay(USDELAY_CALC(4));
}

void I2C_TXByte(unsigned char data) {
	char i = 0;
	for (i=0; i < 8; i++) {
		if (CHECK_BIT(data, 7)) {
			I2C_SDA_HI;
		}
		else {
			I2C_SDA_LOW;
		}
		uSDelay(USDELAY_CALC(4));
		I2C_SCL_HI;
		uSDelay(USDELAY_CALC(4));
		I2C_SCL_LOW;
		uSDelay(USDELAY_CALC(4));
		data = data << 1;
	}
}

unsigned char I2C_RXByte() {
	unsigned char data=0;
	char i = 0;
	for (i=0; i < 8; i++) {
		data = data << 1;
		I2C_SCL_HI;
		uSDelay(USDELAY_CALC(4));
		if ( GPIO_ReadInputDataBit(I2C_SDA_PORT, I2C_SDA_PIN) ) {
			data = data | 0x01;
		}
		uSDelay(USDELAY_CALC(4));
		I2C_SCL_LOW;
		uSDelay(USDELAY_CALC(4));
	}
	return data;
}
