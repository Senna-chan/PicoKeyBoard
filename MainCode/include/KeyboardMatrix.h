#pragma once

#include <KeyboardCodes.h>

#include "Config.h"

uint8_t keys[ROWS][COLS] =
{			//COL0				COL1			COL2				COL3			COL4			COL5			COL6	 COL7	COL8			COL9			COL10			COL11			 COL12			COL13			COL14			COL15
	/*R0*/	{ KEY_LEFT_ALT		,KEY_RESERVED	,KEY_RESERVED		,KEY_RESERVED	,KEY_RESERVED	,KEY_RESERVED	,KEY_B	,KEY_N	,KEY_DOWN		,KEY_LEFT		,KEY_RIGHT		,KEYPAD_SUBTRACT ,KEY_SPACE		,KEY_SLASH		,KEY_RESERVED	,KEY_RESERVED },
	/*R1*/	{ KEY_RESERVED		,KEY_RIGHT		,KEY_RIGHT_CONTROL	,KEY_Z			,KEY_X			,KEY_C			,KEY_V	,KEY_M	,KEY_NUM_LOCK	,KEY_PAUSE		,KEYPAD_DIVIDE	,KEYPAD_MULTIPLY ,KEY_ENTER		,KEY_RESERVED	,KEY_PERIOD		,KEY_COMMA },
	/*R2*/	{ KEY_RESERVED		,0xF7			,0xF3				,KEY_A			,KEY_S			,KEY_D			,KEY_F	,KEY_J	,KEYPAD_1		,KEY_ENTER		,KEYPAD_2		,KEYPAD_3		 ,KEY_BACKSLASH	,KEY_SEMICOLON	,KEY_L			,KEY_K },
	/*R3*/	{ KEY_RESERVED		,KEY_LEFT_SHIFT	,0xF2				,KEY_TAB		,KEY_CAPS_LOCK	,KEY_F3			,KEY_T	,KEY_Y	,KEYPAD_4		,KEY_RESERVED	,KEYPAD_5		,KEYPAD_6		 ,KEY_BACKSPACE ,KEY_LEFT_BRACE	,KEY_F7			,KEY_RIGHT_BRACE },
	/*R4*/	{ KEY_SCROLL_LOCK	,0xF6			,0xF1				,KEY_Q			,KEY_W			,KEY_E			,KEY_R	,KEY_U	,KEYPAD_7		,KEYPAD_ADD		,KEYPAD_8		,KEYPAD_9		 ,KEY_RESERVED	,KEY_P			,KEY_O			,KEY_I },
	/*R5*/	{ KEY_LEFT_ALT		,0xF8			,0xF4				,KEY_ESCAPE		,KEY_RESERVED	,KEY_F4			,KEY_G	,KEY_H	,KEY_RESERVED	,KEY_UP			,KEYPAD_0		,KEYPAD_DOT		 ,KEY_F5		,KEY_QUOTE		,KEY_RESERVED	,KEY_F6 },
	/*R6*/	{ KEY_PRINTSCREEN	,0xF5			,0xF0				,KEY_1			,KEY_2			,KEY_3			,KEY_4	,KEY_7	,KEY_F11		,KEY_RESERVED	,KEY_F12		,KEY_RESERVED	 ,KEY_F10		,KEY_0			,KEY_9			,KEY_8 },
	/*R7*/	{ 0xF9				,KEY_RESERVED	,KEY_LEFT_CONTROL	,KEY_TILDE		,KEY_F1			,KEY_F2			,KEY_5	,KEY_6	,KEY_DELETE		,KEY_RESERVED	,KEY_RESERVED	,KEY_RESERVED	 ,KEY_F9		,KEY_MINUS		,KEY_F8			,KEY_EQUAL }
};