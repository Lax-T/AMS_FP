#include "context.h"

unsigned char global_context[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void gc_SetGlobalValue(unsigned char value_id, unsigned char value) {
	global_context[value_id] = value;
}

void gc_SetGlobalSector(unsigned char data_id, unsigned char data_set[]) {
	unsigned char i;

	for (i=0; i < 4; i++) {
		global_context[data_id + i] = data_set[i];
	}
}

unsigned char gc_GetGlobalValue(unsigned char value_id) {
	return global_context[value_id];
}

void gc_GetGlobalSector(unsigned char data_id, unsigned char data_set[]) {
	unsigned char i;

	for (i=0; i < 4; i++) {
		data_set[i] = global_context[data_id + i];
	}
}
