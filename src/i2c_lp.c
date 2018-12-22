#include "i2c_lp.h"

void I2C_StartLP() {
	I2C_SDA_HI_LP;
	uSDelay(USDELAY_CALC(4));
	I2C_SCL_HI_LP;
	uSDelay(USDELAY_CALC(4));
	I2C_SDA_LOW_LP;
	uSDelay(USDELAY_CALC(4));
	I2C_SCL_LOW_LP;
}

void I2C_StopLP() {
	I2C_SDA_LOW_LP;
	uSDelay(USDELAY_CALC(4));
	I2C_SCL_HI_LP;
	uSDelay(USDELAY_CALC(4));
	I2C_SDA_HI_LP;
	uSDelay(USDELAY_CALC(4));
}

void I2C_SAckLP() {
	I2C_SDA_HI_LP;
	uSDelay(USDELAY_CALC(4));
	I2C_SCL_HI_LP;
	uSDelay(USDELAY_CALC(4));
	I2C_SCL_LOW_LP;
	uSDelay(USDELAY_CALC(4));
}

void I2C_MAckLP() {
	I2C_SDA_LOW_LP;
	uSDelay(USDELAY_CALC(4));
	I2C_SCL_HI_LP;
	uSDelay(USDELAY_CALC(4));
	I2C_SCL_LOW_LP;
	uSDelay(USDELAY_CALC(4));
}

void I2C_MNAckLP() {
	I2C_SDA_HI_LP;
	uSDelay(USDELAY_CALC(4));
	I2C_SCL_HI_LP;
	uSDelay(USDELAY_CALC(4));
	I2C_SCL_LOW_LP;
	uSDelay(USDELAY_CALC(4));
}

void I2C_TXByteLP(unsigned char data) {
	char i = 0;
	for (i=0; i < 8; i++) {
		if (CHECK_BIT(data, 7)) {
			I2C_SDA_HI_LP;
		}
		else {
			I2C_SDA_LOW_LP;
		}
		uSDelay(USDELAY_CALC(4));
		I2C_SCL_HI_LP;
		uSDelay(USDELAY_CALC(4));
		I2C_SCL_LOW_LP;
		uSDelay(USDELAY_CALC(4));
		data = data << 1;
	}
}

unsigned char I2C_RXByteLP() {
	unsigned char data=0;
	char i = 0;
	for (i=0; i < 8; i++) {
		data = data << 1;
		I2C_SCL_HI_LP;
		uSDelay(USDELAY_CALC(4));
		if ( GPIO_ReadInputDataBit(I2C_SDA_PORT_LP, I2C_SDA_PIN_LP) ) {
			data = data | 0x01;
		}
		uSDelay(USDELAY_CALC(4));
		I2C_SCL_LOW_LP;
		uSDelay(USDELAY_CALC(4));
	}
	return data;
}
