#pragma once

//Keycodes from https://github.com/NicoHood/HID
enum KeyboardKeycode {
	KEY_RESERVED = 0,
	KEY_ERROR_ROLLOVER = 1,
	KEY_POST_FAIL = 2,
	KEY_ERROR_UNDEFINED = 3,
	KEY_A = 4,
	KEY_B = 5,
	KEY_C = 6,
	KEY_D = 7,
	KEY_E = 8,
	KEY_F = 9,
	KEY_G = 10,
	KEY_H = 11,
	KEY_I = 12,
	KEY_J = 13,
	KEY_K = 14,
	KEY_L = 15,
	KEY_M = 16,
	KEY_N = 17,
	KEY_O = 18,
	KEY_P = 19,
	KEY_Q = 20,
	KEY_R = 21,
	KEY_S = 22,
	KEY_T = 23,
	KEY_U = 24,
	KEY_V = 25,
	KEY_W = 26,
	KEY_X = 27,
	KEY_Y = 28,
	KEY_Z = 29,
	KEY_1 = 30,
	KEY_2 = 31,
	KEY_3 = 32,
	KEY_4 = 33,
	KEY_5 = 34,
	KEY_6 = 35,
	KEY_7 = 36,
	KEY_8 = 37,
	KEY_9 = 38,
	KEY_0 = 39,
	KEY_ENTER = 40,
	KEY_ESCAPE = 41,
	KEY_BACKSPACE = 42,
	KEY_TAB = 43,
	KEY_SPACE = 44,
	KEY_MINUS = 45,
	KEY_EQUAL = 46,
	KEY_LEFT_BRACE = 47,
	KEY_RIGHT_BRACE = 48,
	KEY_BACKSLASH = 49,
	KEY_NON_US_NUM = 50,
	KEY_SEMICOLON = 51,
	KEY_QUOTE = 52,
	KEY_TILDE = 53,
	KEY_COMMA = 54,
	KEY_PERIOD = 55,
	KEY_SLASH = 56,
	KEY_PRINT = 0x46,
	KEY_PRINTSCREEN = 0x46, // Alias
	KEY_SCROLL_LOCK = 0x47,
	KEY_RIGHT = 0x4F, // Alias
	KEY_LEFT = 0x50, // Alias
	KEY_DOWN = 0x51, // Alias
	KEY_UP = 0x52, // Alias
	KEY_NUM_LOCK = 0x53,
	KEYPAD_DIVIDE = 0x54,
	KEYPAD_MULTIPLY = 0x55,
	KEYPAD_SUBTRACT = 0x56,
	KEYPAD_ADD = 0x57,
	KEYPAD_ENTER = 0x58,
	KEYPAD_1 = 0x59,
	KEYPAD_2 = 0x5A,
	KEYPAD_3 = 0x5B,
	KEYPAD_4 = 0x5C,
	KEYPAD_5 = 0x5D,
	KEYPAD_6 = 0x5E,
	KEYPAD_7 = 0x5F,
	KEYPAD_8 = 0x60,
	KEYPAD_9 = 0x61,
	KEYPAD_0 = 0x62,
	KEYPAD_DOT = 0x63,
	KEY_NON_US = 0x64,
	KEY_APPLICATION = 0x65, // Context menu/right click
	KEY_MENU = 0x65, // Alias
	KEY_DELETE = 0x2A,	// (BACKSPACE)
	KEY_CAPS_LOCK = 0x39,
	KEY_F1 = 0x3A,
	KEY_F2 = 0x3B,
	KEY_F3 = 0x3C,
	KEY_F4 = 0x3D,
	KEY_F5 = 0x3E,
	KEY_F6 = 0x3F,
	KEY_F7 = 0x40,
	KEY_F8 = 0x41,
	KEY_F9 = 0x42,
	KEY_F10 = 0x43,
	KEY_F11 = 0x44,
	KEY_F12 = 0x45,
	KEY_PAUSE = 0x48,
	KEY_INSERT = 0x49,
	KEY_HOME = 0x4A,
	KEY_PAGE_UP = 0x4B,
	KEY_END = 0x4D,
	KEY_PAGE_DOWN = 0x4E,
	//	0xDE-0xDF	 - RESERVED
	KEY_LEFT_CONTROL = 0xE0,
	KEY_LEFT_SHIFT = 0xE1,
	KEY_LEFT_ALT = 0xE2,
	KEY_LEFT_GUI = 0xE3,
	KEY_RIGHT_CONTROL = 0xE4,
	KEY_RIGHT_SHIFT = 0xE5,
	KEY_RIGHT_ALT = 0xE6,
	KEY_RIGHT_GUI = 0xE7,
};

const char* const KeyboardKeycode_string_table[] = {
	"KEY_RESERVED",
	"KEY_ERROR_ROLLOVER",
	"KEY_POST_FAIL",
	"KEY_ERROR_UNDEFINED",
	"KEY_A",
	"KEY_B",
	"KEY_C",
	"KEY_D",
	"KEY_E",
	"KEY_F",
	"KEY_G",
	"KEY_H",
	"KEY_I",
	"KEY_J",
	"KEY_K",
	"KEY_L",
	"KEY_M",
	"KEY_N",
	"KEY_O",
	"KEY_P",
	"KEY_Q",
	"KEY_R",
	"KEY_S",
	"KEY_T",
	"KEY_U",
	"KEY_V",
	"KEY_W",
	"KEY_X",
	"KEY_Y",
	"KEY_Z",
	"KEY_1",
	"KEY_2",
	"KEY_3",
	"KEY_4",
	"KEY_5",
	"KEY_6",
	"KEY_7",
	"KEY_8",
	"KEY_9",
	"KEY_0",
	"KEY_ENTER",
	"KEY_ESCAPE",
	"KEY_BACKSPACE",
	"KEY_TAB",
	"KEY_SPACE",
	"KEY_MINUS",
	"KEY_EQUAL",
	"KEY_LEFT_BRACE",
	"KEY_RIGHT_BRACE",
	"KEY_BACKSLASH",
	"KEY_NON_US_NUM",
	"KEY_SEMICOLON",
	"KEY_QUOTE",
	"KEY_TILDE",
	"KEY_COMMA",
	"KEY_PERIOD",
	"KEY_SLASH",
	"KEY_CAPS_LOCK",
	"KEY_F1",
	"KEY_F2",
	"KEY_F3",
	"KEY_F4",
	"KEY_F5",
	"KEY_F6",
	"KEY_F7",
	"KEY_F8",
	"KEY_F9",
	"KEY_F10",
	"KEY_F11",
	"KEY_F12",
	"KEY_PRINT",
	"KEY_SCROLL_LOCK",
	"KEY_PAUSE",
	"KEY_INSERT",
	"KEY_HOME",
	"KEY_PAGE_UP",
	"76",
	"KEY_END",
	"KEY_PAGE_DOWN",
	"KEY_RIGHT",
	"KEY_LEFT",
	"KEY_DOWN",
	"KEY_UP",
	"KEY_NUM_LOCK",
	"KEYPAD_DIVIDE",
	"KEYPAD_MULTIPLY",
	"KEYPAD_SUBTRACT",
	"KEYPAD_ADD",
	"KEYPAD_ENTER",
	"KEYPAD_1",
	"KEYPAD_2",
	"KEYPAD_3",
	"KEYPAD_4",
	"KEYPAD_5",
	"KEYPAD_6",
	"KEYPAD_7",
	"KEYPAD_8",
	"KEYPAD_9",
	"KEYPAD_0",
	"KEYPAD_DOT",
	"KEY_NON_US",
	"KEY_APPLICATION",
	"102",
	"103",
	"104",
	"105",
	"106",
	"107",
	"108",
	"109",
	"110",
	"111",
	"112",
	"113",
	"114",
	"115",
	"116",
	"117",
	"118",
	"119",
	"120",
	"121",
	"122",
	"123",
	"124",
	"125",
	"126",
	"127",
	"128",
	"129",
	"130",
	"131",
	"132",
	"133",
	"134",
	"135",
	"136",
	"137",
	"138",
	"139",
	"140",
	"141",
	"142",
	"143",
	"144",
	"145",
	"146",
	"147",
	"148",
	"149",
	"150",
	"151",
	"152",
	"153",
	"154",
	"155",
	"156",
	"157",
	"158",
	"159",
	"160",
	"161",
	"162",
	"163",
	"164",
	"165",
	"166",
	"167",
	"168",
	"169",
	"170",
	"171",
	"172",
	"173",
	"174",
	"175",
	"176",
	"177",
	"178",
	"179",
	"180",
	"181",
	"182",
	"183",
	"184",
	"185",
	"186",
	"187",
	"188",
	"189",
	"190",
	"191",
	"192",
	"193",
	"194",
	"195",
	"196",
	"197",
	"198",
	"199",
	"200",
	"201",
	"202",
	"203",
	"204",
	"205",
	"206",
	"207",
	"208",
	"209",
	"210",
	"211",
	"212",
	"213",
	"214",
	"215",
	"216",
	"217",
	"218",
	"219",
	"220",
	"221",
	"222",
	"223",
	"KEY_LEFT_CONTROL",
	"KEY_LEFT_SHIFT",
	"KEY_LEFT_ALT",
	"KEY_LEFT_GUI",
	"KEY_RIGHT_CONTROL",
	"KEY_RIGHT_SHIFT",
	"KEY_RIGHT_ALT",
	"KEY_RIGHT_GUI",
	"232",
	"233",
	"234",
	"235",
	"236",
	"237",
	"238",
	"239",
	"240",
	"241",
	"242",
	"243",
	"244",
	"245",
	"246",
	"247",
	"248",
	"249",
	"250",
	"251",
	"252",
	"253",
	"254",
};
