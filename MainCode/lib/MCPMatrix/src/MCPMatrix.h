// MCPMatrix.h

#ifndef _MCPMATRIX_h
#define _MCPMATRIX_h

#include <Arduino.h>

#include "Key.h"
#include <Adafruit_MCP23X17.h>

#define OPEN LOW
#define CLOSED HIGH

typedef char KeypadEvent;
typedef unsigned int uint;
typedef unsigned long ulong;

// Made changes according to this post http://arduino.cc/forum/index.php?topic=58337.0
// by Nick Gammon. Thanks for the input Nick. It actually saved 78 bytes for me. :)
typedef struct {
	byte rows;
	byte columns;
} KeypadSize;

#define LIST_MAX 6		// Max number of keys on the active list.
#define MAPSIZE 8		// MAPSIZE is the number of rows (times 16 columns)
#define makeKeymap(x) ((KeyboardKeycode*)x)

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

//class Keypad : public Key, public HAL_obj {
class MCPMatrixClass : public Key {
public:
	MCPMatrixClass();
	void init(KeyboardKeycode* userKeymap, Adafruit_MCP23X17* rowchip, Adafruit_MCP23X17* colchip, byte numRows, byte numCols);

	uint bitMap[MAPSIZE];	// 10 row x 16 column array of bits. Except Due which has 32 columns.
	Key key[LIST_MAX];
	unsigned long holdTimer;

	char getKey();
	bool getKeys();
	KeyState getState();
	void begin();
	bool isPressed(char keyChar);
	void setDebounceTime(uint);
	void setHoldTime(uint16_t hold);
	void addEventListener(void(*listener)(char));
	int findInList(char keyChar);
	int findInList(int keyCode);
	char waitForKey();
	bool keyStateChanged();
	byte numKeys();
	uint16_t getHoldTime()
	{
		return holdTime;
	}

private:
	unsigned long startTime;
	KeyboardKeycode* keymap;
	Adafruit_MCP23X17* rowChip;
	Adafruit_MCP23X17* colChip;
	KeypadSize sizeKpd;
	uint debounceTime;
	uint16_t holdTime;
	bool single_key;

	void scanKeys();
	bool updateList();
	void nextKeyState(byte n, boolean button);
	void transitionTo(byte n, KeyState nextState);
	void(*keypadEventListener)(char);

	virtual bool getBit(byte thebyte, int position)
	{
		return (1 == ((thebyte >> position) & 1));
	}

};

extern MCPMatrixClass MCPMatrix;

#endif

