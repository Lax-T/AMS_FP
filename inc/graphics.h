
//extern static unsigned char DEMO_TML[];

#define FNT_DIGIT_XL_ID 0
#define FNT_DIGIT_L_ID 1
#define FNT_DIGIT_M_ID 2
#define FNT_ARIAL11NB 3
#define FNT_ARIAL10 4

/* Font letter codes definitions */
#define _SPACE 0x00
#define _EXCL 0x01
#define _QUOTE 0x02
#define _NUMBER 0x03
#define _NULL 0x04
#define _PERCENT 0x05
#define _APOST 0x07

#define _LBRACK0x08
#define _RBRACK0x09
#define _PLUS 0x0B
#define _COMMA 0x0C
#define _MINUS 0x0D
#define _DOT 0x0E
#define _SLASH 0x0F

#define _0 0x10
#define _1 0x11
#define _2 0x12
#define _3 0x13
#define _4 0x14
#define _5 0x15
#define _6 0x16
#define _7 0x17

#define _8 0x18
#define _9 0x19
#define _COLON 0x1A
#define _SCOLON 0x1B
#define _LESS 0x1C
#define _EQUAL 0x1D
#define _MORE 0x1E
#define _QUEST 0x1F

#define _A 0x21
#define _B 0x22
#define _C 0x23
#define _D 0x24
#define _E 0x25
#define _F 0x26
#define _G 0x27

#define _H 0x28
#define _I 0x29
#define _J 0x2A
#define _K 0x2B
#define _L 0x2C
#define _M 0x2D
#define _N 0x2E
#define _O 0x2F

#define _P 0x30
#define _Q 0x31
#define _R 0x32
#define _S 0x33
#define _T 0x34
#define _U 0x35
#define _V 0x36
#define _W 0x37

#define _X 0x38
#define _Y 0x39
#define _Z 0x3A
#define _UNDER 0x3F

#define _a 0x41
#define _b 0x42
#define _c 0x43
#define _d 0x44
#define _e 0x45
#define _f 0x46
#define _g 0x47

#define _h 0x48
#define _i 0x49
#define _j 0x4A
#define _k 0x4B
#define _l 0x4C
#define _m 0x4D
#define _n 0x4E
#define _o 0x4F

#define _p 0x50
#define _q 0x51
#define _r 0x52
#define _s 0x53
#define _t 0x54
#define _u 0x55
#define _v 0x56
#define _w 0x57

#define _x 0x58
#define _y 0x59
#define _z 0x5A
#define _PIPE 0x5C
#define _3DOT 0x5D

#define _PERMILLE 0x60
#define _LAPOST 0x61
#define _RAPOST 0x62
#define _LQUOTE 0x63
#define _RQUOTE 0x64
#define _BULLET 0x65
#define _DEGREE 0x66
#define _PLUSMIN 0x67

#define __A 0x70
#define __B 0x71
#define __V 0x72
#define __G 0x73
#define __D 0x75
#define __E 0x76
#define __YE 0x77

#define __ZH 0x78
#define __Z 0x79
#define __II 0x7A
#define __I 0x7B
#define __YI 0x7C
#define __Y 0x7D
#define __K 0x7E
#define __L 0x7F

#define __M 0x80
#define __N 0x81
#define __O 0x82
#define __P 0x83
#define __R 0x84
#define __S 0x85
#define __T 0x86
#define __U 0x87

#define __F 0x88
#define __H 0x89
#define __TS 0x8A
#define __CH 0x8B
#define __SH 0x8C
#define __SCH 0x8D
#define __MZ 0x8E
#define __YU 0x8F

#define __YA 0x90

#define __a 0x98
#define __b 0x99
#define __v 0x9A
#define __g 0x9B
#define __d 0x9D
#define __e 0x9E
#define __ye 0x9F

#define __zh 0xA0
#define __z 0xA1
#define __ii 0xA2
#define __i 0xA3
#define __y 0xA5
#define __k 0xA6
#define __l 0xA7

#define __m 0xA7
#define __n 0xA9
#define __o 0xAA
#define __p 0xAB
#define __r 0xAC
#define __s 0xAD
#define __t 0xAE
#define __u 0xAF

#define __f 0xB0
#define __h 0xB1
#define __ts 0xB2
#define __ch 0xB3
#define __sh 0xB4
#define __sch 0xB5
#define __mz 0xB6
#define __yu 0xB7
#define __ya 0xB8

#define T_MONDAY_SHORT_ID 0
#define T_TUESDAY_SHORT_ID 1
#define T_WEDNESDAY_SHORT_ID 2
#define T_THURSDAY_SHORT_ID 3
#define T_FRIDAY_SHORT_ID 4
#define T_SATURDAY_SHORT_ID 5
#define T_SUNDAY_SHORT_ID 6


unsigned char* get_demo_tml();
unsigned char* get_t_main_screen();
unsigned char* get_fnt_digit_xl(unsigned char char_n);
unsigned char** get_fnt_digit_xl_ptr();
unsigned char** get_fnt_digit_l_ptr();
unsigned char** get_fnt_digit_m_ptr();
unsigned char** get_fnt_digit_ptr(unsigned char fnt_n);
unsigned char** GetFontPointer(unsigned char fnt_n);
unsigned char* GetTextStringPointer(unsigned char text_id);
unsigned char* GetMenuSetPointer(unsigned char menu_set_id);

