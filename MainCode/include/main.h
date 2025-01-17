#ifndef _KEYBOARD_CORE_H
#define _KEYBOARD_CORE_H

// Core includes
#include <Arduino.h>
#include <Adafruit_TinyUSB.h>
#include "Config.h"
// Library includes

#include <ArduinoJson.h>
#include <MCP23S17.h>
#include <MyHelpers.h>
#include <SPI.h>
#include <i2cEncoderLibV2.h>
#include <PS2Mouse.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MCP23X17.h>
#include <Wire.h>
#include <TimedAction.h>
#include <Adafruit_SPIFlash.h>
#include <LittleFS.h>
#include <KeyboardCodes.h>
#include <ConsumerKeyCodes.h>
#include <BPLib.h>
#include <Crypto.h>

#include <RPi_Pico_TimerInterrupt.h> // Pico timer
#include <RPi_Pico_ISR_Timer.h>		 // Pico timer

// My library includes

#include <BTKeyboard.h>
#include <BTMouse.h>
#include <HIDMouse.h>
#include <HIDKeyboard.h>
#include <MCPMatrix.h>
#include <Key.h>

// Local includes
#include "KeyboardMatrix.h"
#include "KeyboardHelpers.h"
#include "Variables.h"
#include "Helpers.h"
#include "MacroHelper.h"
#include "HIDFunctions.h"
#include "SettingsHelper.h"
#include "OledFunctions.h"

#include "DuckyReadWriter.h"
#include "CommonSetup.h"
#include "Debug.h"


Adafruit_FlashTransport_RP2040 HWFlashTransport;
Adafruit_SPIFlash flash(&HWFlashTransport);
FatVolume fatfs;
bool isFormatted;

Adafruit_USBD_MSC usb_msc;

BPLib* bt = new BPLib(BLUETOOTH_SERIAL);


PS2Mouse ps2_mouse(CLOCK_PIN, DATA_PIN);

Adafruit_MCP23X08 expender = Adafruit_MCP23X08();

bool encoderInterupted = false;
bool secondTicked = false;
int16_t lastEncPos, currentEncPos;


bool leftMouseButton = 0;
bool rightMouseButton = 0;
bool mouseResetSend = true; // Mouse starts not active
bool capsState = false, numState = false, scrollState = false;
TimedAction doMouseStuffAction = TimedAction();
TimedAction checkBatteryAction = TimedAction();
TimedAction secondsTickAction = TimedAction();
MCPMatrixClass matrix = MCPMatrixClass();
float batteryvoltage;
String funcType = "MEDIA";
String oldFuncType = "STARTUP";
bool functionKeyPressed = false;

bool forceOperateMode = true;
OperateMode operateMode = CABLE;

uint32_t cardSize = 0;

i2cEncoderLibV2* encoder = new i2cEncoderLibV2(&Wire, ENC_ADDR);
bool bluetoothConnected = false;


Settings settings;

uint8_t menuindex = 0; // 0 = showing func type

bool massStarted = false;
bool sdInitialized = false;


uint8_t leds = 0;
uint8_t oldLeds = 255;

RPI_PICO_Timer ITimer1(1);

void ErrorHandler(const char* file, const char* func, size_t line, const char* message) {
	main_oled.printf("ERROR in %s %s:%u\r\n", file, func, line);
	main_oled.println(message);
	pinMode(LED_BUILTIN, OUTPUT);
	while (1) {
		Serial.printf("ERROR in %s %s:%u\r\n", file, func, line);
		Serial.println(message);
		Serial.println();
		digitalWrite(LED_BUILTIN, digitalRead(LED_BUILTIN));
		delay(500);
	}
}

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define __FUNCTIONNAME__ (strlen(__PRETTY_FUNCTION__) == 0 ? "UNKNOWN" : __PRETTY_FUNCTION__)
#define Error_Handler(s) ErrorHandler(__FILENAME__, __FUNCTIONNAME__ , __LINE__ , s)


#endif // _KEYBOARD_CORE_H