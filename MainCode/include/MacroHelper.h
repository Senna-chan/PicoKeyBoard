// MacroHelper.h

#ifndef _MACROHELPER_h
#define _MACROHELPER_h

#include <Arduino.h>
#include <HIDKeyboard.h>

void loadMacros();
void saveMacro();
void genMacro(uint8_t macroPos);
void pressMacro(uint8_t macroPos);
// Gets the keys in a hold blocking way from the keyboard
KeyReport getMacroKeysFromKeyboard();

#endif