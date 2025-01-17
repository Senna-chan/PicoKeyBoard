// OledFunctions.h

#ifndef _OLEDFUNCTIONS_h
#define _OLEDFUNCTIONS_h


#include <Arduino.h>
#include "Variables.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
static const char* LOWER_ALPHABET		= "abcdefghijklmnopqrstuvwxyz";
static const char* UPPER_ALPHABET		= "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static const char* NUMBERS				= "0123456789.-";
static const char* HEXCHARS				= "ABCDEF0123456789";
static const char* ALPHABET				= "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
#pragma GCC diagnostic pop

const int cursorBlinkTimeout = 250; // millis

void clearNonHudArea();
void redrawhud();
void drawmenu();
void fulloledupdate();
void drawMenuAction();
void drawSettingsAction();
void drawfunctype();
bool yesnoScreen(bool defaultval, const char* line1 = "", const char* line2 = "");
int drawMultilineMenu(char* lines[], size_t lineAmount);
String inputScreen(uint8_t maxLength, const char* line);
String inputScreen(uint8_t maxLength, const char* line, const char* regex);
String inputScreen(uint8_t maxLength, const char* line, uint16_t startx, uint16_t starty);
String inputScreen(uint8_t maxLength, const char* line, uint16_t startx, uint16_t starty, const char* regex);

float encoderScreen(const char* line1,						int32_t min, int32_t max, int32_t change, int decimal);
float encoderScreen(const char* line1, const char* line2,   int32_t min, int32_t max, int32_t change, int decimal);


#endif

