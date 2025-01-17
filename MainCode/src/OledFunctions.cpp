// 
// 
// 

#include <Arduino.h>
#include "OledFunctions.h"
#include "Config.h"
#include "Variables.h"
#include "Helpers.h"
#include "CustomIcons.h"
#include <Adafruit_SSD1306.h>
#include "KeyboardHelpers.h"
#include "SettingsHelper.h"
#include <i2cEncoderLibV2.h>

void fulloledupdate()
{
	main_oled.clearDisplay();
	redrawhud();
	drawmenu();
	drawfunctype();
	main_oled.display();
}

// TODO: Remove magic values
void redrawhud()
{
	main_oled.fillRect(0, 0, 128, 20, BLACK);
	if (operateMode == BLUETOOTH) {
		if(bluetoothConnected)
		{
			main_oled.drawBitmap(0, 0, bluetooth_connected, 16, 16, WHITE);
		}
		else {
			main_oled.drawBitmap(0, 0, bluetooth, 16, 16, WHITE);
		}
	}
	else if (operateMode == CABLE) {
		//if (TinyUSBDevice.ready())
		//{
			main_oled.drawBitmap(0, 0, usb, 16, 16, WHITE);
		//}
	}
	else if (operateMode == CHARGING) {
		main_oled.drawBitmap(0, 0, charging, 16, 16, WHITE);
	}

	if(sdInitialized)
	{
		main_oled.drawBitmap(60, 2, sd_card, sd_card_width, sd_card_height, WHITE);
	}
	else
	{
		main_oled.drawBitmap(60, 0, no_sd_card, no_sd_card_width, no_sd_card_height, WHITE);
	}

	if (batteryvoltage > 4) {
		main_oled.drawBitmap(108, 0, battery_full, 16, 16, WHITE);
	}
	else if (between(batteryvoltage, 3.75, 4)) {
		main_oled.drawBitmap(108, 0, battery_almost_full, 16, 16, WHITE);
	}
	else if (between(batteryvoltage, 3.3, 3.75)) {
		main_oled.drawBitmap(108, 0, battery_half, 16, 16, WHITE);
	}
	else if (between(batteryvoltage, 3, 3.3)) {
		main_oled.drawBitmap(108, 0, battery_almost_empty, 16, 16, WHITE);
	}
	else if (batteryvoltage < 3) {
		main_oled.drawBitmap(108, 0, battery_empty, 16, 16, WHITE);
	}
	main_oled.setCursor(80, 4);
	main_oled.print(batteryvoltage);
}

void drawmenu()
{
	clearNonHudArea();
	if (menuActive) 
	{
		main_oled.setTextSize(2);
		main_oled.drawStringCenter(0, 20, MenuScreens[menuindex][0], WHITE);
		main_oled.drawStringCenter(0, 30, MenuScreens[menuindex][1], WHITE);
		main_oled.setTextSize(1);
	}
	else if (settingsActive)
	{
		main_oled.drawStringCenter(64, 20, SettingsScreens[settingsindex][0], WHITE);
		main_oled.drawStringCenter(64, 30, SettingsScreens[settingsindex][1], WHITE);
	}
	else 
	{
		drawfunctype();
	}
}

void drawMenuAction()
{
	
}

void drawSettingsAction()
{
	if (!settingsActive)
	{
		return; // Can not happen but still
	}
	if(settingsindex == 0)
	{
		saveSettings();
		settingsActive = false;
		menuActive = true;
	}
	else if(settingsindex == 1) // Create connection config
	{
		saveConnectionConfig(createConnectionConfig());
	}
	
}

float encoderScreen(const char* line1, int32_t min, int32_t max, int32_t change, int decimal = 0)
{
	return encoderScreen(line1, "", min, max, change, decimal);
}

float encoderScreen(const char* line1, const char* line2, int32_t min, int32_t max, int32_t change, int decimal = 0)
{
	encoder->writeMin(min);
	encoder->writeMax(max);
	encoder->writeStep(change);
	encoder->writeCounter(min);

	clearNonHudArea();

	main_oled.drawStringCenter(64, 20, line1, WHITE);
	main_oled.drawStringCenter(64, 30, line2, WHITE);
	main_oled.drawStringCenter(64, 40, "0", WHITE);
	main_oled.display();
	String encValue = "";
	while(true)
	{
		if (encoder->updateStatus()) {
			if (decimal == 0) {
				encValue = String(encoder->readCounterInt());
			} else {
				encValue = String(encoder->readCounterInt() / decimal);
			}
			main_oled.drawStringCenter(64, 40, encValue.c_str(), WHITE);
			if(encoder->buttonPressed())
			{
				if(yesnoScreen(true, "Is this number good?", encValue.begin()))
				{
					break;
				}
			}
		}
	}

	encoder->writeMin((int32_t)0);
	encoder->writeMax((int32_t)30);
	encoder->writeStep((int32_t)1);
	encoder->writeCounter((int32_t)0);
	if (decimal == 0) 
	{
		return encoder->readCounterInt();
	}
	else 
	{
		return encoder->readCounterInt() / decimal;
	}
}

void drawfunctype()
{
	clearNonHudArea();
	if (oldFuncType == funcType)
	{
		return;
	}
	if (funcType == "fnkeys") {
		main_oled.setTextSize(5);
		main_oled.setCursor(32, 16);
		main_oled.print("FN");
		main_oled.setTextSize(1);
		return;
	}
	oldFuncType = funcType;
	if (!sdInitialized) return; // We need the SD card from here on
	char *fname = NULL;
	int w, h;
	String path = "modes/" + funcType + "/";
	path.toLowerCase();
	Serial.println(fname);
	if(!fatfs.exists(fname))
	{
		Serial.println("No logo found");
		main_oled.setTextSize(3);
		main_oled.drawStringCenter(48, 24, funcType.c_str(), WHITE);
		main_oled.setTextSize(1);
		return;
	}

	uint8_t* mainLogo = read1bitBMP((path+"logo.bmp").begin(), &w, &h);
	main_oled.drawBitmap(48, 24, mainLogo, w, h, WHITE);

	oled12.drawBitmap(10, 10, read1bitBMP((path + "1.bmp").begin(), &w, &h), w, h, WHITE);
	oled12.drawBitmap(40, 10, read1bitBMP((path + "2.bmp").begin(), &w, &h), w, h, WHITE);
	oled34.drawBitmap(10, 10, read1bitBMP((path + "3.bmp").begin(), &w, &h), w, h, WHITE);
	oled34.drawBitmap(40, 10, read1bitBMP((path + "4.bmp").begin(), &w, &h), w, h, WHITE);
	oled56.drawBitmap(10, 10, read1bitBMP((path + "5.bmp").begin(), &w, &h), w, h, WHITE);
	oled56.drawBitmap(40, 10, read1bitBMP((path + "6.bmp").begin(), &w, &h), w, h, WHITE);
	oled78.drawBitmap(10, 10, read1bitBMP((path + "7.bmp").begin(), &w, &h), w, h, WHITE);
	oled78.drawBitmap(40, 10, read1bitBMP((path + "8.bmp").begin(), &w, &h), w, h, WHITE);
	oled9 .drawBitmap(10, 10, read1bitBMP((path + "9.bmp").begin(), &w, &h), w, h, WHITE);
}



void clearNonHudArea()
{
	main_oled.fillRect(32, 32, 128, 48, BLACK);
}


bool yesnoScreen(bool defaultval, const char* line1, const char* line2)
{
	bool returnval = defaultval;
	int yesnoYPos = 44;
	clearNonHudArea();
	if (defaultval)
	{
		main_oled.drawBitmap(32, yesnoYPos, yes_inv, yes_width, yes_height, WHITE);
		main_oled.drawBitmap(72, yesnoYPos, no, yes_width, yes_height, WHITE);
	}
	else
	{
		main_oled.drawBitmap(32, yesnoYPos, yes, yes_width, yes_height, WHITE);
		main_oled.drawBitmap(72, yesnoYPos, no_inv, yes_width, yes_height, WHITE);
	}
	main_oled.drawStringCenter(64, 20, line1, WHITE);
	main_oled.drawStringCenter(64, 30, line2, WHITE);
	main_oled.display();
	while (true) {
		handleEncoder();
		if (encoder->increased() && returnval)
		{
			main_oled.fillRect(32, yesnoYPos, yes_width, yes_height, BLACK); // Clear yes no part
			main_oled.fillRect(72, yesnoYPos, yes_width, yes_height, BLACK); // Clear yes no part
			returnval = false;
			main_oled.drawBitmap(32, yesnoYPos, yes, yes_width, yes_height, WHITE);
			main_oled.drawBitmap(72, yesnoYPos, no_inv, yes_width, yes_height, WHITE);
			main_oled.display();
		}
		else if (encoder->decreased() && !returnval)
		{
			main_oled.fillRect(32, yesnoYPos, yes_width, yes_height, BLACK); // Clear yes no part
			main_oled.fillRect(72, yesnoYPos, yes_width, yes_height, BLACK); // Clear yes no part
			returnval = true;
			main_oled.drawBitmap(32, yesnoYPos, yes_inv, yes_width, yes_height, WHITE);
			main_oled.drawBitmap(72, yesnoYPos, no, yes_width, yes_height, WHITE);
			main_oled.display();
		}
		if (encoder->buttonPressed()) break;
	}
	return returnval;
}

int drawMultilineMenu(char* lines[], size_t lineAmount)
{
	size_t begin = 0;
	size_t current = 0;
	while (true) {
		if (handleEncoder()) {
			if (encoder->increased() && current != lineAmount) current++;
			if (encoder->decreased() && current != 0) current--;
			main_oled.setCursor(0, 16);
			for (size_t i = begin; i < min(4u, lineAmount); i++) {
				if (i == current) {
					main_oled.printf("--> %i. %s\r\n", i, lines[i]);
				}
				else {
					main_oled.printf("%04i. %s\r\n", i, lines[i]);
				}
			}
		}
	}
	return current;
}

String inputScreen(uint8_t maxLength, const char* line)
{
	return inputScreen(maxLength, line, 10, 30, "");
}
String inputScreen(uint8_t maxLength, const char* line, const char* regex)
{
	return inputScreen(maxLength, line, 10, 30, regex);
}

String inputScreen(uint8_t maxLength, const char* line, uint16_t startx, uint16_t starty)
{
	return inputScreen(maxLength, line, startx, starty, "");
}

String inputScreen(uint8_t maxLength, const char* line, uint16_t startx, uint16_t starty, const char* regex)
{
	uint64_t prevBlinkMillis = millis();
	bool blinkVisible = false;
	while (true) {
		clearNonHudArea();
		main_oled.drawStringCenter(64, 20, line, WHITE);

		char value[50];
		char c = 0;
		//if (maxLength > 24) {
		//	main_oled.setCursor(startx - ((maxLength / 2) * 3 * main_oled.textsize), starty);
		//}
		//else {
		//	main_oled.setCursor(startx - (maxLength * 3 * main_oled.textsize), starty);
		//}
		main_oled.display();
		size_t valueIndex = 0;
		while (true) 
		{
			handleEncoder();
			if (encoder->buttonPressed() || valueIndex == maxLength)
			{
				break;
			}
			c = getAsciiFromKeyboard();
			if (c != 0) {
				Serial.print(c); Serial.print(" ");
				if (c == KEY_DELETE) // backspace
				{
					value[valueIndex] = '\0'; // Removes last character
					valueIndex--;
					main_oled.setCursor(main_oled.getCursorX() - 6, main_oled.getCursorY()); // Resets cursor to prev position
					main_oled.fillRect(main_oled.getCursorX(), main_oled.getCursorY(), 6, 7, BLACK); // Clears char
					main_oled.drawFastHLine(0, main_oled.getCursorY() + 8, 128, BLACK); // Clear underline
					main_oled.drawFastHLine(main_oled.getCursorX(), main_oled.getCursorY() + 8, 6, WHITE);
					main_oled.display();
					continue;
				}
				else if (c == KEY_ENTER)
				{
					break;
				}
				char compareBuf[2] = {c, '\0'};
				if (!strpbrk(compareBuf, regex))
				{
					continue; // Illegal char
				}
				value[valueIndex] = c;
				valueIndex++;

				main_oled.print(c);
				main_oled.drawFastHLine(0, main_oled.getCursorY() + 8, 128, BLACK); // Clear underline
				main_oled.drawFastHLine(main_oled.getCursorX(), main_oled.getCursorY() + 8, 6, WHITE);
				main_oled.display();
				#if DEBUG
					Serial.print(getShiftPressed());
					Serial.print(" value:"); Serial.print(value);
					Serial.print(" length: "); Serial.println(valueIndex);
				#endif
			}
			if(millis() - prevBlinkMillis > cursorBlinkTimeout)
			{
				auto oledx = main_oled.getCursorX();
				auto oledy = main_oled.getCursorY();
				if (blinkVisible) main_oled.setTextColor(BLACK);
				else main_oled.setTextColor(WHITE);
				main_oled.print("_");
				main_oled.setCursor(oledx, oledy);
			}
		}
		if (yesnoScreen(true, "Is this input good?", value))
		{
			return String(value);
		}
	}
}
