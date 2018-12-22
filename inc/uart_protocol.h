#define UART_RX_FIFO_SIZE 32
#define UART_TX_FIFO_SIZE 32

//#define UART_RX_PACKET_SIZE 6

//Protocol RX states
#define UART_RX_READY_STATE 1
#define UART_PEND_PROCESS_STATE 0

#define UART_WAIT_START_SYMB 0
#define UART_WAIT_STOP_SYMB 1
#define UART_PEND_PROCESSING 2

#define UART_THREAD_NOP 0
#define UART_THREAD_SET_TOUT 1
#define UART_THREAD_RUN_NOW 2

//Packet process result
#define UART_PACKET_ERR 0
#define UART_PACKET_OK 1

unsigned char up_ProcessRXINT(unsigned char data_byte);
unsigned char up_GetRXState();
void up_SetRXState(unsigned char new_state);
void up_PutRXFIFO(unsigned char data);
unsigned char up_GetRXFIFOUsage();
void up_ResetRXFIFO();
unsigned char up_ExtractData(unsigned char package_buffer[], unsigned char use_crc);
