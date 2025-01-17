// 
// 
// 

#include "Variables.h"
#include "Adafruit_SSD1306.h"
#include <Adafruit_MCP23X08.h>
#include "Config.h"
#include <SPI.h>


Adafruit_SSD1306 oled12		(128, 32, &SPI, OLED_DC, OLED_RESET, OLED_CS);
Adafruit_SSD1306 oled34		(128, 32, &SPI, OLED_DC, OLED_RESET, OLED_CS);
Adafruit_SSD1306 oled56		(128, 32, &SPI, OLED_DC, OLED_RESET, OLED_CS);
Adafruit_SSD1306 oled78		(128, 32, &SPI, OLED_DC, OLED_RESET, OLED_CS);
Adafruit_SSD1306 oled9		(128, 32, &SPI, OLED_DC, OLED_RESET, OLED_CS);

Adafruit_SSD1306 main_oled	(128, 64, &SPI, OLED_DC, OLED_RESET, OLED_CS);

KeyReport keyMacros[9][macroKeyDepth];
KeyReport curKeyReport;
unsigned long seconds = 0;
bool menuActive = false;
bool settingsActive = false;
unsigned long menuActivationTime = seconds;
uint8_t funcindex = 0;
uint8_t settingsindex = 0;
ConnectionConfig currentConnectionConfig = settings.connectionconfigs[0];

const char* MenuScreens[][2]{
	{"Return to","actions"},
	{"Settings",""},
	{"Connect to","bluetooth host"}
};

const char* SettingsScreens[][2]{
	{"Return To","Main menu"},
	{"Connection","Configs"},
	{"Mouse","Acceleration"}
};

static void setupMiscDisplay(Adafruit_SSD1306* display)
{
	display->begin();
	display->clearDisplay();
	display->display();
}

void initVars()
{
	Serial.println("Setting up some vars");
	Settings settings;
	setupMiscDisplay(&oled12);
	setupMiscDisplay(&oled34);
	setupMiscDisplay(&oled56);
	setupMiscDisplay(&oled78);
	setupMiscDisplay(&oled9);
	delay(1000);
	Serial.println("Vars setted up");
}