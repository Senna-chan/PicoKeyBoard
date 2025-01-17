#pragma once

#include <Arduino.h>
#include "Config.h"

#define STRINGIZE(str) #str
#define STR_CONCAT(str1, str2) (str1 ## str2)

#if DEBUGMOUSE
#define MouseDebugf(fmt, ...) Serial.printf("MOUSE: " fmt, ##__VA_ARGS__);
#define MouseDebugln(s) Serial.println("MOUSE: " s);
#else
#define MouseDebugf(fmt, ...)
#define MouseDebugln(s)
#endif

#if DEBUGKEYBOARD
#define KeyboardDebugf(fmt, ...) Serial.printf("KEYBOARD: " fmt, ##__VA_ARGS__);
#define KeyboardDebugln(s) Serial.println("KEYBOARD: " s);
#else
#define KeyboardDebugf(fmt, ...)
#define KeyboardDebugln(s)
#endif