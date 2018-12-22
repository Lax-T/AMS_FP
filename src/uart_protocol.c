#include "uart_protocol.h"

unsigned char g_rx_fifo[UART_RX_FIFO_SIZE];
unsigned char g_rx_fifo_write_ptr = 0;
unsigned char g_rx_fifo_read_ptr = 0;
unsigned char g_tx_fifo[UART_TX_FIFO_SIZE];
unsigned char g_tx_fifo_write_ptr = 0;
unsigned char g_tx_fifo_read_ptr = 0;
unsigned char g_msg_len = 0;
unsigned char g_expected_msg_len = 0;
unsigned char g_rx_status = UART_WAIT_START_SYMB;

static unsigned char crc8_table[256] = {
    0, 94,188,226, 97, 63,221,131,194,156,126, 32,163,253, 31, 65,
  157,195, 33,127,252,162, 64, 30, 95,  1,227,189, 62, 96,130,220,
   35,125,159,193, 66, 28,254,160,225,191, 93,  3,128,222, 60, 98,
  190,224,  2, 92,223,129, 99, 61,124, 34,192,158, 29, 67,161,255,
   70, 24,250,164, 39,121,155,197,132,218, 56,102,229,187, 89,  7,
  219,133,103, 57,186,228,  6, 88, 25, 71,165,251,120, 38,196,154,
  101, 59,217,135,  4, 90,184,230,167,249, 27, 69,198,152,122, 36,
  248,166, 68, 26,153,199, 37,123, 58,100,134,216, 91,  5,231,185,
  140,210, 48,110,237,179, 81, 15, 78, 16,242,172, 47,113,147,205,
   17, 79,173,243,112, 46,204,146,211,141,111, 49,178,236, 14, 80,
  175,241, 19, 77,206,144,114, 44,109, 51,209,143, 12, 82,176,238,
   50,108,142,208, 83, 13,239,177,240,174, 76, 18,145,207, 45,115,
  202,148,118, 40,171,245, 23, 73,  8, 86,180,234,105, 55,213,139,
   87,  9,235,181, 54,104,138,212,149,203, 41,119,244,170, 72, 22,
  233,183, 85, 11,136,214, 52,106, 43,117,151,201, 74, 20,246,168,
  116, 42,200,150, 21, 75,169,247,182,232, 10, 84,215,137,107, 53
};

unsigned char up_GetRXState() {
	return g_rx_status;
}

void up_SetRXState(unsigned char new_state) {
	g_rx_status = new_state;
}

void up_ResetRX () {
	g_rx_status = UART_WAIT_START_SYMB;
}

unsigned char up_ProcessRXINT (unsigned char data_byte) {
	switch (g_rx_status) {
	case UART_WAIT_START_SYMB:
		if (data_byte == 0x7e) {
			g_rx_status = UART_WAIT_STOP_SYMB;
			g_msg_len = 0;
			return UART_THREAD_SET_TOUT;
		}
		else {
			return UART_THREAD_NOP;
		}
	case UART_WAIT_STOP_SYMB:
		g_msg_len++;
		if (g_msg_len == 1) {
			g_expected_msg_len = data_byte;
		}
		if (g_msg_len == (g_expected_msg_len+1)) {
			if (data_byte == 0xe7) {
				g_rx_status = UART_PEND_PROCESSING;
				return UART_THREAD_RUN_NOW;
			}
			else {
				g_rx_status = UART_WAIT_START_SYMB;
				g_rx_fifo_write_ptr = 0;
				g_rx_fifo_read_ptr = 0;
				return UART_THREAD_NOP;
			}
		}
		up_PutRXFIFO(data_byte);
		return UART_THREAD_SET_TOUT;
	}
	return UART_THREAD_NOP;
}

/* Calculate FIFO usage by write/read pointers */
unsigned char CalculateFIFOUsage (unsigned char write_pointer, unsigned char read_pointer, unsigned char fifo_size) {
	if (write_pointer == read_pointer) {
		return 0;
	}
	if (read_pointer < write_pointer) {
		return write_pointer - read_pointer;
	}
	else {
		return (fifo_size - read_pointer) + write_pointer;
	}
}


/* Put data in RX FIFO, return current FIFO usage */
void up_PutRXFIFO(unsigned char data) {
	g_rx_fifo[g_rx_fifo_write_ptr] = data;
	g_rx_fifo_write_ptr++;
	if (g_rx_fifo_write_ptr >= UART_RX_FIFO_SIZE) {
		g_rx_fifo_write_ptr = 0;
	}
}

/* Get 1 data byte from RX FIFO. If FIFO is empty return 0xff */
unsigned char up_GetRXFIFO() {
	unsigned char data;
	//if (CalculateFIFOUsage(g_rx_fifo_write_ptr, g_rx_fifo_read_ptr, UART_RX_FIFO_SIZE) != 0) {
	data = g_rx_fifo[g_rx_fifo_read_ptr];
	g_rx_fifo_read_ptr++;
	if (g_rx_fifo_read_ptr >= UART_RX_FIFO_SIZE) {
		g_rx_fifo_read_ptr = 0;
	}
	return data;
}

/* Get RX FIFO usage */
unsigned char up_GetRXFIFOUsage() {
	return CalculateFIFOUsage(g_rx_fifo_write_ptr, g_rx_fifo_read_ptr, UART_RX_FIFO_SIZE);
}

/* Reset (clear) RX FIFO */
void up_ResetRXFIFO() {
	g_rx_fifo_write_ptr = 0;
	g_rx_fifo_read_ptr = 0;
}

/* Extract data package from FIFO, check CRC and write to buffer */
unsigned char up_ExtractData(unsigned char package_buffer[], unsigned char use_crc) {
	unsigned char i, data, len;
	unsigned char crc = 0;
	unsigned char next_char_escaped = 0;
	unsigned char buff_pointer = 0;
	len = up_GetRXFIFO();
	crc = crc8_table[crc ^ len];
	len = len-2;
	for (i=0; i<len; i++) {
		data = up_GetRXFIFO();
		crc = crc8_table[crc ^ data];
		if (next_char_escaped) {
			data = data | 0x02;
			next_char_escaped = 0;
			package_buffer[buff_pointer++] = data;
		}
		else {
			if (data == 0xAA) {
				next_char_escaped = 1;
			}
			else {
				package_buffer[buff_pointer++] = data;
			}
		}
	}
	if (use_crc) {
		data = up_GetRXFIFO();
		up_ResetRXFIFO();
		if (data == crc) {
			return UART_PACKET_OK;
		}
		else {
			return UART_PACKET_ERR;
		}
	}
	else {
		up_ResetRXFIFO();
		return UART_PACKET_OK;
	}
}

/*
unsigned char g_rx_fifo[UART_RX_FIFO_SIZE];
unsigned char g_rx_fifo_write_ptr = 0;
unsigned char g_rx_fifo_read_ptr = 0;


void up_PushRxFIFO(unsigned char data) {
	g_rx_fifo[g_rx_fifo_write_ptr] = data;
	g_rx_fifo_write_ptr++;
	if (g_rx_fifo_write_ptr >= UART_RX_FIFO_SIZE) {
		g_rx_fifo_write_ptr = 0;
	}
}


unsigned char up_FetchNextMessage(unsigned char buffer[]) {
	unsigned char result = 0;
	unsigned char start_symb_found = 0;
	unsigned char buffer_cnt = 0;
	unsigned char next_byte;
	unsigned char read_ptr = g_rx_fifo_read_ptr;

	while (uart_fx_fifo_write_ptr != uart_fx_fifo_read_ptr) {
		next_byte = g_rx_fifo[read_ptr];

		if (start_symb_found == 1) {
			buffer[buffer_cnt] = next_byte;

		}
		else {
			if (next_byte == MESSAGE_START_SYMB) {
				start_symb_found = 1;
			}
		}
	}
	return result;
}
*/
