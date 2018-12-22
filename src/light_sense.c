#include "light_sense.h"
#include <math.h>

#define SLAVE_ADR 0x52

unsigned short ReadByte(unsigned char slave_adr, unsigned char register_adr ) {
	unsigned char data = 0;

	I2C_Start();
	I2C_TXByte(slave_adr);
	I2C_SAck();
	I2C_TXByte(register_adr | 0x80);
	I2C_SAck();

	I2C_Start();
	I2C_TXByte(slave_adr | 0x01);
	I2C_SAck();
	data = I2C_RXByte();
	I2C_MNAck();
	I2C_Stop();
	return data;
}

void lsns_PowerUp() {
	I2C_Start();
	I2C_TXByte(SLAVE_ADR);
	I2C_SAck();
	I2C_TXByte(0x80);
	I2C_SAck();
	I2C_TXByte(0x03);
	I2C_SAck();
	I2C_Stop();
}

unsigned short lsns_ReadCh0Value() {
	unsigned char data = 0;
	unsigned short datah = 0;
	double d;
	data = ReadByte(SLAVE_ADR, 0x0C);
	datah = ReadByte(SLAVE_ADR, 0x0D);
	datah = datah << 8;
	datah = datah | data;
	d = log10((double)datah);
	datah = (unsigned short)(d*10);
	return datah;
}
