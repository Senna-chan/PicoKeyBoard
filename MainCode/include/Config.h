#ifndef _CONFIG_H
#define _CONFIG_H

#include <Arduino.h>

#define DEBUG				1
#define DEBUGKEYBOARD		0
#define DEBUGMOUSE			0
#define ENCODER_ENABLED		0
#define MOUSE_ENABLED		1
#define KEYBOARD_ENABLED	0
#define HID_ENABLED			1
#define OLED_ENABLED		1
#define BT_ENABLED			0
#define MATRIX_ENABLED		0
#define MASS_ENABLED		0 
#define DUCKY_ENABLED		0 // Duckyscripts enabled

// Wire1
#define WIRE1_SCL			D5
#define WIRE1_SDA			D4

// UART2(Bluetooth)
#define UART2_TX			D8
#define UART2_RX			D9
#define BLUETOOTH_SERIAL	Serial2

// SPI1(OLEDS)
#define OLED_SPI			SPI
#define SPI1_MISO			D16
#define SPI1_MOSI			D19
#define SPI1_SCLK			D18

// SPI2(KeyMatrix)
#define KEYMATRIX_SPI		SPI1
#define SPI2_MISO			D12 //PC11 // KBblue
#define SPI2_MOSI			D15 //PC12 // KBwhiteBLUE
#define SPI2_SCLK			D14 //PC10 // KBwhiteORAGE

// Mouse
#define DATA_PIN			D27 //PD0 // KBgreen		-> yellow
#define CLOCK_PIN			D26 //PD1 // KBwhiteGREEN -> orange

#define BATPIN				D28

// MCP23008
#define MCPINT				D2
#define BTMODEPIN			0
#define USBMODEPIN			1
#define SDUSBPIN			2
#define BT_CONNECTED_LED	3
#define INIT_LED			8

// ENCODER
#define ENC_INT				D3 // Encoder interrupt pin
#define ENC_ADDR			0x41

// Oled
#define OLED_DC				D20
#define OLED_CS				D17
#define OLED_RESET			D21


// Keyboard expenders
#define MCPS_CS				D13
#define ROW_CHIP_ADDR		0b110
#define COL_CHIP_ADDR		0b111

// Seconds things
#define menuReturnSeconds   5

//Keyboard
#define CAPS_LED			1
#define NUM_LED				2
#define SCROLL_LED			3
// Keyboard matrix
#define ROWS				8
#define COLS				16
// Keyboard macro
#define macroKeyDepth		4

#endif // _CONFIG_H