#include "lcd_ctrl.h"
#include "graphics.h"

#define F_2DIGIT_NUM_TSZRA2 0xb2 // draw ten, skip ten zero, right align, 2pix tile spacing
#define F_2DIGIT_NUM_TSZRAM2 0xba// draw ten, skip ten zero, right align, MSB - minus sign, 2pix tile spacing
#define F_2DIGIT_NUM_LA0 0x00 // left align
#define F_2DIGIT_NUM_TLA2 0x82 // draw ten, left align, 2pix tile spacing

#define F_4DIGIT_NUM_RA2 0x12 // right align, 2pix tile spacing

/* UI build commands */
#define CM_MOVE_CURSOR 1 // Move cursor to position, [1arg - X position, 2arg - Y position]
#define CM_DRAW_2DIGIT_STATIC 2 // Draw 2digit number, [1arg - value, 2arg - font_id, 3arg - flags]
#define CM_DRAW_2DIGIT_VAR 3 // Draw 2digit number, [1arg - ui_var_id, 2arg - font_id, 3arg - flags]
#define CM_DRAW_4DIGIT_STATIC 4 // Draw 4digit number, [1arg - value_h, 2arg - value_l, 3arg - font_id, 4arg - flags]
#define CM_DRAW_4DIGIT_VAR 5 // Draw 4digit number, [1arg - var_h_id, 2arg - var_l_id, 3arg - font_id, 4arg - flags]

#define CM_DRAW_TEXT_CHOICE 8 //Draw string, [1 - condition var id, 2 - max choices, 3 - font id, 4 - string 0 id, 5 -string n id ...]

void ui_UpdateUI();
void ui_SetUIVar(unsigned char var_id, unsigned char value);
