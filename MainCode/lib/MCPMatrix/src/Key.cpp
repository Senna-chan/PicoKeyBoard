#include <KeyboardCodes.h>

#include "Key.h"

// default constructor
Key::Key() {
	kcode = KEY_RESERVED;
	kstate = IDLE;
	stateChanged = false;
}

// constructor
Key::Key(uint8_t userKeyChar) {
	kcode = userKeyChar;
	kpos = -1;
	kstate = IDLE;
	stateChanged = false;
}


void Key::key_update (uint8_t userKeyChar, KeyState userState, bool userStatus) {
	oldState = kstate;
	kcode = userKeyChar;
	kstate = userState;
	stateChanged = userStatus;
}