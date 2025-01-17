#ifndef Keypadlib_KEY_H_
#define Keypadlib_KEY_H_

#include <Arduino.h>

#define OPEN LOW
#define CLOSED HIGH

typedef enum
{
    IDLE,
    PRESSED,
    HOLD,
    RELEASED
} KeyState;

class Key {
public:
	// members
	uint8_t kcode;
	int kpos;
	KeyState kstate;
	KeyState oldState;
	bool stateChanged;

	uint8_t col;
	uint8_t row;

	// methods
	Key();
	Key(uint8_t userKeyCode);
    void key_update(uint8_t userKeyCode, KeyState userState, bool userStatus);

private:

};

#endif
