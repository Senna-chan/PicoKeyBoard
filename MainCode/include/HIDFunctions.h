// HIDFunctions.h

#ifndef _HIDFUNCTIONS_h
#define _HIDFUNCTIONS_h

#include <Arduino.h>
#include <HIDKeyboard.h> // Needed for KeyReport

void releaseAllKeyboardMouse();

void pressMouse(uint8_t button);
void releaseMouse(uint8_t button);
void releaseMouseAll();
void moveMouse(int8_t x, int8_t y, int8_t scroll, int8_t pan);
void moveMouse(int8_t x, int8_t y);
void moveMouseAbs(int16_t x, int16_t y);
void moveScrollWheel(int8_t scroll, int8_t pan);
void moveMouseRel(int8_t x, int8_t y);
void pressKeyboardKey(uint8_t key);
void printKeyboardString(String string);
void releaseKeyboardKey(uint8_t key);
void releaseAllKeyboardKeys();
void writeKeyboardKey(uint8_t key);
void pressConsumerKey(uint16_t key);
void releaseConsumerKey();
void writeConsumerKey(uint16_t key);
void writeKeyReport(KeyReport report);


#endif

