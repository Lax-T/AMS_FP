#include "ui_builder.h"

unsigned char g_buffer[1024];
unsigned char g_xpointer = 0;
unsigned char g_ypointer = 0;
unsigned char g_ui_vars[] = {0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 5};

/*
unsigned char img[] = {64, 8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x80, 0xC0, 0xE0, 0xF0, 0xF0, 0xF0, 0xE0, 0xE0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0xE0, 0xF0, 0xF0, 0xF0, 0xE0, 0xE0, 0xC0,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x3C, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0xF0, 0x00,
		0x00, 0x00, 0x00, 0xF0, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xC0, 0xE0, 0xE0, 0xE0, 0xC0, 0xC0, 0xC0, 0x80,
		0x00, 0x00, 0x03, 0x0F, 0x1F, 0x7F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x1F, 0x00,
		0x00, 0x00, 0x00, 0x1F, 0x7F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x7F, 0x3F, 0x0F, 0x03,
		0x00, 0x00, 0x80, 0xC0, 0xC0, 0xC0, 0xE0, 0xE0, 0xE0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFE, 0xF8, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xF8,
		0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0F, 0x1F, 0x3F, 0x3F, 0x7F, 0x7F, 0x7F, 0x7F,
		0x7F, 0x7F, 0x3F, 0x0F, 0x00, 0x80, 0xE0, 0xF0, 0xF8, 0xF8, 0xFC, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFC, 0xFC, 0xF8, 0xF8, 0xF0, 0xE0, 0xC0, 0x80, 0x0F, 0x3F,
		0x3F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x3F, 0x3F, 0x1F, 0x0F, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0xC0, 0xF8, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC7, 0xC7, 0xC7, 0x00,
		0x00, 0x00, 0x00, 0xC7, 0xC7, 0xC7, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFC,
		0xF8, 0xE0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7E,
		0x7E, 0x3E, 0x7E, 0x7F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x03, 0x03, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x03, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x03, 0x03, 0x07, 0x07, 0x07, 0x07,
		0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};*/



unsigned char ui_GetUIVar(unsigned char var_id) {
	return g_ui_vars[var_id];
}

void ui_SetUIVar(unsigned char var_id, unsigned char value) {
	g_ui_vars[var_id] = value;
}

void LoadTemplateToBuffer(unsigned char template[]) {
	unsigned short i = 0;
	for (i=0; i < 1024; i++) {
		g_buffer[i] = template[i];
	}
}

unsigned char MergeTile(unsigned char tile[]) {
	unsigned char tile_x_size, tile_y_size, row_pointer, row_shift, temp, y, x;
	unsigned short buff_pointer, tile_pointer;
	tile_x_size = tile[0];
	tile_y_size = tile[1];
	tile_pointer = 2;
	if (g_ypointer == 0) {
		row_pointer = 0;
		row_shift = 0;
	}
	else {
		row_pointer = g_ypointer / 8;
		row_shift = g_ypointer % 8;
	}

	for (y = 0; y < tile_y_size; y++) {
		buff_pointer = (row_pointer * 128) + g_xpointer;

		for (x = 0; x < tile_x_size; x++) {
			temp = g_buffer[buff_pointer];
			temp = temp | (tile[tile_pointer] << row_shift);
			g_buffer[buff_pointer] = temp;
			if (row_shift > 0) {
				if (row_pointer <= 6) {
					temp = g_buffer[buff_pointer + 128];
					temp = temp | (tile[tile_pointer] >> (8 - row_shift));
					g_buffer[buff_pointer + 128] = temp;
				}
			}
			buff_pointer++;
			tile_pointer++;
		}
		row_pointer++;
	}
	return tile_x_size;
}

/* Dummy function to get blank tile x size w/o actual processing */
unsigned char MergeTileDummy(unsigned char tile[]) {
	return tile[0];
}

/* Simple UI build functions */

unsigned char SF_DrawFont(unsigned char value, unsigned char digit_fnt_id) {
	unsigned char **ptr;
	ptr = get_fnt_digit_ptr(digit_fnt_id);
	return MergeTile(*(ptr + value));
}

/* Draw text string */
void SF_DrawString(unsigned char string_id, unsigned char font_id) {
	unsigned char temp, i, string_len;
	unsigned char **fnt_ptr;
	unsigned char *text_string;
	fnt_ptr = GetFontPointer(font_id);
	text_string = GetTextStringPointer(string_id);
	string_len = text_string[0] + 1;

	for (i=1; i < string_len; i++) {
		temp = MergeTile(*(fnt_ptr + text_string[i]));
		g_xpointer += temp;
	}
}

/* Complex UI build functions */
/*FLAGS:
 * 7b - ten
 * 6b - reserved
 * 5b - skip ten zero
 * 4b - left align 0/right align 1
 * 3b - MSB minus sign
 * 2..0b - digits spacing sps1p | sps2p | sps3p | sps4p
 * */
void CF_Draw2DigitNum(unsigned char value, unsigned char digit_fnt_id, unsigned char flags) {
	unsigned char temp, i;
	unsigned char **ptr;
	ptr = get_fnt_digit_ptr(digit_fnt_id);
	unsigned char x_shift_offset;
	x_shift_offset = flags & 0x07;
	unsigned char string[3];
	unsigned char string_size=0;
	unsigned char string_expected_size=1;

	if (flags & 0x08) { // if minus sign is allowed
		string_expected_size++;
		if (value & 0x80) { // MSB is minus sign
			string[string_size++] = 18;
		}
	}
	if (flags & 0x80) { // if 2nd digit is allowed
		string_expected_size++;
		temp = (value & 0x7f) / 10;
		if(temp!=0) { // if not zero
			string[string_size++] = temp;
		}
		else { // if zero
			if ((flags & 0x20) == 0) { // if no zero skipping, add to string
				string[string_size++] = temp;
			}
		}
	}
	string[string_size++] = (value & 0x7f) % 10;

	if (flags & 0x10) { // Right align
		while (string_size < string_expected_size) { // Put blank tiles to get expected total string size
			temp = MergeTileDummy(*(ptr + 16));
			g_xpointer += (temp + x_shift_offset);
			string_expected_size--;
		}
	}
	for (i=0; i < string_size; i++) {  // Print formatted string data
		temp = MergeTile(*(ptr + string[i]));
		g_xpointer += (temp + x_shift_offset);
	}
}

/* FLAGS
 * 7b - 4th digit
 * 6b - reserved
 * 5b - skip zeros (except low digit)
 * 4b - left align 0/right align 1
 * 3b - reserved
 * 2..0b - digits spacing sps1p | sps2p | sps3p | sps4p
 */
void CF_Draw4DigitNum(unsigned int value, unsigned char digit_fnt_id, unsigned char flags) {
	unsigned char temp, i;
	unsigned char **ptr;
	ptr = get_fnt_digit_ptr(digit_fnt_id);
	unsigned char x_shift_offset;
	x_shift_offset = flags & 0x07;
	unsigned char string[4];
	unsigned char string_size=0;
	unsigned char string_expected_size=3;

	if (flags & 0x80) {  // if 4 digit is allowed
		string_expected_size++;
		temp = value / 1000;
		if(temp!=0) { // if not zero
			string[string_size++] = temp;
		}
		else { // if zero
			if ((flags & 0x20) == 0) { // if no zero skipping, add to string
				string[string_size++] = temp;
			}
		}
	}
	if (flags & 0x20) { // if skip zeros
		temp = value / 100;
		if(temp!=0) { // if not zero
			string[string_size++] = temp;
		}
		temp = value / 10;
		if(temp!=0) { // if not zero
			string[string_size++] = temp;
		}
	}
	else {
		string[string_size++] = value / 100;
		string[string_size++] = (value % 100) / 10;
	}
	string[string_size++] = value % 10;

	if (flags & 0x10) { // Right align
		while (string_size < string_expected_size) { // Put blank tiles to get expected total string size
			temp = MergeTileDummy(*(ptr + 16));
			g_xpointer += (temp + x_shift_offset);
			string_expected_size--;
		}
	}
	for (i=0; i < string_size; i++) {  // Print formatted string data
		temp = MergeTile(*(ptr + string[i]));
		g_xpointer += (temp + x_shift_offset);
	}
}

/* UI build megafunctions */
/*FLAGS
 * 7..4b - number of drawn lines
 * 3..0b - line vertical spacing
 * */
void MF_DrawMenuList(unsigned char first_line, unsigned char menu_set_id, unsigned char font_id, unsigned char flags){
	unsigned char x_pointer_stash = g_xpointer;
	unsigned char *menu_set = GetMenuSetPointer(menu_set_id);


}

//static unsigned char string[] = {_1, _3, _SLASH, __G, __r, __u, __d, _SPACE,  __S, __e, __r};

static unsigned char CMSET_MAIN_SCREEN[] = {
		CM_MOVE_CURSOR, 14, 1, CM_DRAW_2DIGIT_VAR, 4, FNT_DIGIT_XL_ID, F_2DIGIT_NUM_TSZRA2,  // Temperature IN
		CM_MOVE_CURSOR, 44, 5, CM_DRAW_2DIGIT_VAR, 5, FNT_DIGIT_M_ID, F_2DIGIT_NUM_LA0,
		CM_MOVE_CURSOR, 67, 1, CM_DRAW_2DIGIT_STATIC, 0, FNT_DIGIT_XL_ID, F_2DIGIT_NUM_TSZRAM2,  // Temperature OUT
		CM_MOVE_CURSOR, 110, 5, CM_DRAW_2DIGIT_STATIC, 0, FNT_DIGIT_M_ID, F_2DIGIT_NUM_LA0,
		CM_MOVE_CURSOR, 0, 28, CM_DRAW_2DIGIT_VAR, 6, FNT_DIGIT_L_ID, F_2DIGIT_NUM_TLA2,  // Humidity IN
		CM_MOVE_CURSOR, 96, 28, CM_DRAW_2DIGIT_STATIC, 0, FNT_DIGIT_L_ID, F_2DIGIT_NUM_TLA2,  // Humidity OUT
		CM_MOVE_CURSOR, 39, 30, CM_DRAW_4DIGIT_VAR, 8, 9, FNT_DIGIT_M_ID, F_4DIGIT_NUM_RA2,  // Pressure
		CM_MOVE_CURSOR, 0, 52, CM_DRAW_TEXT_CHOICE, 15, 7, FNT_ARIAL10, T_MONDAY_SHORT_ID, T_TUESDAY_SHORT_ID, T_WEDNESDAY_SHORT_ID,
		T_THURSDAY_SHORT_ID, T_FRIDAY_SHORT_ID, T_SATURDAY_SHORT_ID, T_SUNDAY_SHORT_ID,
		255};

/* Process command set mixing tiles into preloaded template */
void ProcessUICommandSet(unsigned char command_set[]) {
	unsigned char i, command, arg_1, arg_2, arg_3, arg_4;
	unsigned int arg_5_int;
	unsigned char buff[5];

	for (i=0; i<254; i++) {
		command = command_set[i];

		switch(command) {

		case CM_MOVE_CURSOR:  // Set cursor position
			g_xpointer = command_set[++i];
			g_ypointer = command_set[++i];
			break;

		case CM_DRAW_2DIGIT_STATIC:
			arg_1 = command_set[++i];
			arg_2 = command_set[++i];
			arg_3 = command_set[++i];
			CF_Draw2DigitNum(arg_1, arg_2, arg_3);
			break;

		case CM_DRAW_2DIGIT_VAR:
			arg_1 = g_ui_vars[command_set[++i]];
			arg_2 = command_set[++i];
			arg_3 = command_set[++i];
			CF_Draw2DigitNum(arg_1, arg_2, arg_3);
			break;

		case CM_DRAW_4DIGIT_STATIC:
			arg_5_int = 0 | command_set[++i];
			arg_5_int = (arg_5_int << 8) | command_set[++i];
			arg_1 = command_set[++i];
			arg_2 = command_set[++i];
			CF_Draw4DigitNum(arg_5_int, arg_1, arg_2);
			break;

		case CM_DRAW_4DIGIT_VAR:
			arg_5_int = 0 | g_ui_vars[command_set[++i]];
			arg_5_int = (arg_5_int << 8) | g_ui_vars[command_set[++i]];
			arg_1 = command_set[++i];
			arg_2 = command_set[++i];
			CF_Draw4DigitNum(arg_5_int, arg_1, arg_2);
			break;

		case CM_DRAW_TEXT_CHOICE:
			arg_1 = g_ui_vars[command_set[++i]]; // UI var value
			arg_2 = command_set[++i]; // Max choices
			arg_3 = command_set[++i]; // Font ID
			if (arg_1 < arg_2) {
				arg_4 = command_set[i + arg_1 + 1];
			}
			SF_DrawString(arg_4, arg_3);
			i = i + arg_2;
			break;

		case 255:
			i = 254;
			break;
		}
	}
}

void ui_UpdateUI() {
	//unsigned char **ptr;
	//ptr = get_fnt_digit_xl_ptr();

	LoadTemplateToBuffer(get_t_main_screen());
	ProcessUICommandSet(CMSET_MAIN_SCREEN);

	/*
	g_xpointer = 14;
	g_ypointer = 1;

	CF_Draw2DigitNum(21, 0, 0xb2);*/

	/*
	MergeTile(*(ptr+2));
	g_xpointer = 27;
	g_ypointer = 1;
	MergeTile(*(ptr+3));*/
	/*
	g_xpointer = 67;
	g_ypointer = 1;
	CF_Draw2DigitNum(0x83, 0, 0xba);*/
	/*
	MergeTile(*(ptr+16));
	g_xpointer = 93;
	g_ypointer = 1;
	MergeTile(*(ptr+4));*/

	/*
	ptr = get_fnt_digit_l_ptr();

	g_xpointer = 0;
	g_ypointer = 28;
	MergeTile(*(ptr+5));
	g_xpointer = 12;
	g_ypointer = 28;
	MergeTile(*(ptr+3));
	g_xpointer = 96;
	g_ypointer = 28;
	MergeTile(*(ptr+8));
	g_xpointer = 108;
	g_ypointer = 28;
	MergeTile(*(ptr+4));

	ptr = get_fnt_digit_m_ptr();

	g_xpointer = 44;
	g_ypointer = 5;
	MergeTile(*(ptr+3));
	g_xpointer = 110;
	g_ypointer = 5;
	MergeTile(*(ptr+6));

	g_xpointer = 39;
	g_ypointer = 30;
	MergeTile(*(ptr+7));
	g_xpointer = 50;
	g_ypointer = 30;
	MergeTile(*(ptr+2));
	g_xpointer = 61;
	g_ypointer = 30;
	MergeTile(*(ptr+9));*/


	lc_RefreshLCD(g_buffer);
}





