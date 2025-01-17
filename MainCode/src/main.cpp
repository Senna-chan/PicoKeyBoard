#include "main.h"

bool GetBit(byte thebyte, int position)
{
	return (1 == ((thebyte >> position) & 1));
}

void checkBattery() 
{
	batteryvoltage = analogReadVoltage(BATPIN) * 2; // Cutting voltage in half with voltage divider to get a range of 1.5 to 2.1 volt. > 3,3 volt on ADC will kill ADC
	batteryvoltage = round(batteryvoltage * 10);
	batteryvoltage = batteryvoltage / 10; // Getting one decimal after the comma i hope
}

void handleEncoderInt() 
{ 
	encoderInterupted = true; 
}

#pragma region massStorage region

#if MASS_ENABLED

int32_t msc_read_cb(uint32_t lba, void* buffer, uint32_t bufsize)
{
	// Note: SPIFLash Bock API: readBlocks/writeBlocks/syncBlocks
	// already include 4K sector caching internally. We don't need to cache it, yahhhh!!
	return flash.readBlocks(lba, (uint8_t*)buffer, bufsize / 512) ? bufsize : -1;
}

// Callback invoked when received WRITE10 command.
// Process data in buffer to disk's storage and
// return number of written bytes (must be multiple of block size)
int32_t msc_write_cb(uint32_t lba, uint8_t* buffer, uint32_t bufsize)
{
	// Note: SPIFLash Bock API: readBlocks/writeBlocks/syncBlocks
	// already include 4K sector caching internally. We don't need to cache it, yahhhh!!
	return flash.writeBlocks(lba, buffer, bufsize / 512) ? bufsize : -1;
}

// Callback invoked when WRITE10 command is completed (status received and accepted by host).
// used to flush any pending cache.
void msc_flush_cb(void)
{
	// sync with flash
	flash.syncBlocks();

	// clear file system's cache to force refresh
	fatfs.cacheClear();
}

void initMassStorage() 
{

	// Set disk vendor id, product id and revision
	// with string up to 8, 16, 4 characters respectively
	usb_msc.setID("AdvKeyboard", "Internal Flash", "1.0");

	// Set callback
	usb_msc.setReadWriteCallback(msc_read_cb,
		msc_write_cb,
		msc_flush_cb);

	// Set disk size, block size should be 512 regardless of spi flash page size
	usb_msc.setCapacity(flash.size() / 512, 512);

	// MSC is ready for read/write
	usb_msc.setUnitReady(true);

	if (!usb_msc.begin())
	{
		Error_Handler("Failed to start MassStorage");
	}

	isFormatted = fatfs.begin(&flash);
	if (!isFormatted)
	{
		Error_Handler("FS Not formatted. Please run setup");
	}
}

#else
void initMassStorage() 
{

}
#endif

#pragma endregion

#if HID_ENABLED

// Report ID
enum
{
	RID_KEYBOARD = 1,
	RID_MOUSE,
	RID_CONSUMER_CONTROL, // Media, volume etc ..
};

// HID report descriptor using TinyUSB's template
uint8_t const desc_hid_report[] =
{
  TUD_HID_REPORT_DESC_KEYBOARD(HID_REPORT_ID(RID_KEYBOARD)),
  TUD_HID_REPORT_DESC_MOUSE(HID_REPORT_ID(RID_MOUSE)),
  TUD_HID_REPORT_DESC_CONSUMER(HID_REPORT_ID(RID_CONSUMER_CONTROL))
};

// USB HID object. For ESP32 these values cannot be changed after this declaration
// desc report, desc len, protocol, interval, use out endpoint
Adafruit_USBD_HID usb_hid(desc_hid_report, sizeof(desc_hid_report), HID_ITF_PROTOCOL_NONE, 2, false);

bool setupHID()
{
	usb_hid.setBootProtocol(HID_ITF_PROTOCOL_MOUSE | HID_ITF_PROTOCOL_KEYBOARD);
	usb_hid.setPollInterval(2);
	usb_hid.setReportDescriptor(desc_hid_report, sizeof(desc_hid_report));
	usb_hid.setStringDescriptor("TinyUSB MouseKeyboard");

	if (!usb_hid.begin())
	{
		Error_Handler("Failed to start USB HID");
	}
	TinyUSBDevice.detach();
	delay(100);
	TinyUSBDevice.attach();
#if KEYBOARD_ENABLED
	USBKeyboard.begin(RID_KEYBOARD, RID_CONSUMER_CONTROL, &usb_hid);
	USBKeyboard.onLED(ledCB);
	USBKeyboard.setKeyboardMode(RAW_HID);
#endif
#if MOUSE_ENABLED
	USBMouse.begin(RID_MOUSE, &usb_hid);
#endif

	Serial.println(F("HID Initialized"));
	return true;
}
#endif


bool secondsTick(struct repeating_timer* t)
{
	(void)t;
	seconds++;
	secondTicked = true;
	return true;
}


#pragma region HIDActions
void processPressedKey(byte key) 
{
	if (key == 0xF0) 
	{
		functionKeyPressed = true;
		releaseAllKeyboardKeys();
	}
	if (key >= 0xF1 && key <= 0xF9) 
	{
		int func = key - 0xF1;
		pressMacro(func);
	}
	if (functionKeyPressed) 
	{
		switch (key)
		{
			case KEY_UP:
				writeKeyboardKey(KEY_PAGE_UP);
			break;

			case KEY_DOWN:
				writeKeyboardKey(KEY_PAGE_DOWN);
			break;

			case KEY_LEFT:
				writeKeyboardKey(KEY_HOME);
			break;

			case KEY_RIGHT:
				writeKeyboardKey(KEY_END);
			break;

			case KEY_F1:
				writeConsumerKey(MEDIA_VOLUME_MUTE);
			break;

			case KEY_F2:
				writeConsumerKey(MEDIA_VOLUME_DOWN);
			break;

			case KEY_F3:
				writeConsumerKey(MEDIA_VOLUME_UP);
			break;

			case KEY_F5:
				writeConsumerKey(CONSUMER_BRIGHTNESS_DOWN);
			break;

			case KEY_F6:
				writeConsumerKey(CONSUMER_BRIGHTNESS_UP);
			break;

			case KEY_F10:
				writeConsumerKey(MEDIA_PLAY_PAUSE);
			break;

			case KEY_F11:
				writeConsumerKey(MEDIA_PREV);
			break;

			case KEY_F12:
				writeConsumerKey(MEDIA_NEXT);
			break;

			default:

			break;
		}
		return;
	}
	// From here on we know it is not a special key so we can just press it
	pressKeyboardKey(key);
}
void processReleasedKey(uint8_t key) 
{
	if (key == 0xF0) 
	{
		functionKeyPressed = false;
	}
	//if (key >= 0xF1 && key <= 0xF9) {
	//	int func = key - 0xF1;
	//}
	releaseKeyboardKey(key);
}

void checkKeys()
{
	if (matrix.getKeys())
	{
		for (int i = 0; i < LIST_MAX; i++)   // Scan the whole key list.
		{
			if (matrix.key[i].stateChanged)   // Only find keys that have changed state.
			{
				switch (matrix.key[i].kstate)  // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
				{ 
					case PRESSED:
						KeyboardDebugf("Pressed %s\r\n", KeyboardKeycode_string_table[(uint8_t)matrix.key[i].kcode]);
						#if HID_ENABLED || BT_ENABLED
						processPressedKey(matrix.key[i].kcode);
						#endif
					break;

					case RELEASED:
						KeyboardDebugf("Released %s\r\n", KeyboardKeycode_string_table[(uint8_t)matrix.key[i].kcode]);
						#if HID_ENABLED || BT_ENABLED
							processReleasedKey(matrix.key[i].kcode);
						#endif
					break;

					case HOLD:
						KeyboardDebugf("Holding %s\r\n", KeyboardKeycode_string_table[(uint8_t)matrix.key[i].kcode]);
					break;

					case IDLE:

					break;
				}
			}
		}
	}
}

void doMouseStuff()
{
#if MOUSE_ENABLED
	if (!ps2_mouse.isConnected())
	{
		return;
	}
	MouseData data = ps2_mouse.readData();
	leftMouseButton = GetBit(data.status, 0);
	rightMouseButton = GetBit(data.status, 1);
#if DEBUGMOUSE
	Serial.print(F("status:"));
	printBits(&Serial, data.status, false);
	Serial.print(F("\tX:"));
	Serial.print(data.position.x);
	Serial.print(F("\tY:"));
	Serial.println(data.position.y);
#endif
#if (HID_ENABLED || BT_ENABLED)
	if (!functionKeyPressed) 
	{
		leftMouseButton ? pressMouse(MOUSE_LEFT) : releaseMouse(MOUSE_LEFT);
		rightMouseButton ? pressMouse(MOUSE_RIGHT) : releaseMouse(MOUSE_RIGHT);
	}
	else
	{
		if (leftMouseButton || rightMouseButton) 
		{
			pressMouse(MOUSE_MIDDLE);
		}
		else 
		{
			releaseMouse(MOUSE_MIDDLE);
		}
	}
	if (data.position.x != 0 || data.position.y != 0) 
	{
		mouseResetSend = false;
		if (!functionKeyPressed)
		{
			moveMouse(round(data.position.x * currentConnectionConfig.mouseaccel[0]), round(data.position.y * currentConnectionConfig.mouseaccel[1] * -1));
		}
		else
		{
			if (abs(data.position.x) > abs(data.position.y))
			{
				moveScrollWheel(data.position.x > 0 ? 1 : -1, 0);
			}
			else
			{
				moveScrollWheel(0, data.position.y > 0 ? 1 : -1);
			}
		}

	}
	else if (mouseResetSend == false) 
	{
		moveMouse(0, 0);
		moveScrollWheel(0, 0);
		mouseResetSend = true;
	}
#endif
#endif
}

void ledCB(bool numlock, bool capslock, bool scrolllock, void* cbData) 
{
	(void)cbData;

	if (numlock != numState) 
	{
		// rowChip.digitalWrite(NUM_LED, numlock);
		numState = numlock;
	}
	if (capslock != capsState) 
	{
		// rowChip.digitalWrite(CAPS_LED, capslock);
		capsState = capslock;
	}

	if (scrolllock != scrollState) 
	{
		// rowChip.digitalWrite(SCROLL_LED, scrolllock);
		scrollState = scrolllock;
	}
}
#pragma endregion

void setup() 
{
	uint32_t initMillis;
	Serial.begin(115200);
	Serial1.begin(115200);
#if DEBUG
	while (!Serial);
	delay(200);
	Serial.println("DEBUG MODE ACTIVE. Prepare for a lot of output");
#endif
	pinMode(INIT_LED, OUTPUT);
	//pinMode(BATPIN, INPUT_ANALOG);
	batteryvoltage = analogReadVoltage(BATPIN) * 2; // First Sample
	delay(300);
	Serial.println(F("Starting custom keyboard"));
	Serial.println(F("Initializing Wire"));
	setupWire1();
#if DEBUG
	scanI2C(&Wire, &Serial);
#endif
	setupSPI1();
	initVars();

	flash.begin();
#if OLED_ENABLED
	Serial.println(F("Initializing Oled"));
	main_oled.begin();
	main_oled.setTextColor(WHITE);
	main_oled.display();
	delay(1000);
	main_oled.clearDisplay();
	main_oled.println(F("Oled Initialized"));
	main_oled.display();
	delay(1000);
	main_oled.clearDisplay();
	main_oled.display();
	//fullupdateoled();
	Serial.println(F("Oled Initialized"));
	delay(10);
#endif

	if (ITimer1.attachInterruptInterval(1000 * 1000, secondsTick))
	{
		Serial.print(F("Starting ITimer1 OK, millis() = ")); Serial.println(millis());
	}
	else
	{
		Serial.println(F("Can't set ITimer1. Select another freq. or timer"));
	}

	delay(10);
	Serial.println(F("keyboard wire things initialized"));
	delay(10);


#if MOUSE_ENABLED
	Serial.println("Initializing PS2 mouse");
	initMillis = millis();
	pinMode(CLOCK_PIN, OUTPUT);
	delay(1000);
	ps2_mouse.initialize();
	if (!ps2_mouse.isConnected())
	{
		Serial.println("Mouse not connected");
		while (true) yield();
	}
	MouseData data;
	do {
		data = ps2_mouse.readData();
		delay(10);
	} while (data.status == 0xFF);
	Serial.printf("Initialized PS2 mouse. Took %d millis\r\n", millis() - initMillis);
	doMouseStuffAction = TimedAction(20, &doMouseStuff);
#endif // MOUSE_ENABLED

	checkBatteryAction = TimedAction(1000 * 5, &checkBattery);

#if BT_ENABLED
	Serial.println(F("Initializing BT Chip"));
	delay(10);
	BLUETOOTH_SERIAL.begin(115200);
	//if (settings.bluetoothAutoConnect == 0)
	//{
		bt->reconnect();
	//}
	//else {
	//BluetoothAddress bt_address = settings.bt_addressess[settings.bluetoothAutoConnect];
	//Serial.print(F("Connecting to host "));
	//Serial.print(bt_address.name);
	//Serial.print(F(" with address "));
	//Serial.println(bt_address.address);
	//bt->reconnect(bt_address.address);
	//}
	BTKeyboard.onLED(ledCB);
	BTKeyboard.begin(bt);
	BTMouse.begin(bt);
	Serial.println(F("BT Chip Initialized"));
	delay(10);
#endif
#if KEYBOARD_ENABLED
	Serial.println(F("Initializing Matrix"));
	delay(50);
	if (!rowChip.begin())
	{
		Error_Handler();
	}
	rowChip.enableHardwareAddress();
	if (!colChip.begin())
	{
		Error_Handler();
	}
	colChip.enableHardwareAddress();
	matrix.init((KeyboardKeycode*)&keys, &rowChip, &colChip, ROWS, COLS);

	matrix.setDebounceTime(1);

	rowChip.pinMode(CAPS_LED, OUTPUT);
	rowChip.pinMode(NUM_LED, OUTPUT);
	rowChip.pinMode(SCROLL_LED, OUTPUT);

	rowChip.digitalWrite(NUM_LED, HIGH);
	rowChip.digitalWrite(CAPS_LED, LOW);
	rowChip.digitalWrite(SCROLL_LED, HIGH);

	delay(10);
#endif
#if ENCODER_ENABLED
	Serial.println(F("Initializing Encoder"));
	delay(10);
	pinMode(ENC_INT, INPUT_PULLUP);
	attachInterrupt(ENC_INT, handleEncoderInt, FALLING);
	if (!encoder->begin(i2cEncoderLibV2::FLOAT_DATA | i2cEncoderLibV2::WRAP_ENABLE | i2cEncoderLibV2::DIRE_RIGHT | i2cEncoderLibV2::IPUP_DISABLE | i2cEncoderLibV2::RMOD_X1 | i2cEncoderLibV2::STD_ENCODER))
	{
		Serial.println("Encoder not found. Check wiring!");
		main_oled.clearDisplay();
		main_oled.println(F("encoder not found"));
		main_oled.display();
		while (1);
	}
	else
	{
#if DEBUG
		Serial.println(F("Found the encoder"));
#endif
	}
	encoder->writeCounter(0.0f); /* Reset the counter value */
	encoder->writeMax(30.0f); /* Set the maximum threshold*/
	encoder->writeMin(0.0f); /* Set the minimum threshold */
	encoder->writeStep(1.0f); /* Set the step to 1*/
	encoder->writeInterruptConfig(0xff); /* Enable all the interrupt */
	encoder->writeAntibouncingPeriod(50);  /* Set an anti-bouncing of 50ms */
	encoder->writeDoublePushPeriod(50);  /*Set a period for the double push of 50ms */
	delay(10);
	Serial.println(F("Encoder initialized"));
#endif // ENCODER_ENABLED

#if HID_ENABLED
	Serial.println(F("Initializing HID"));
	delay(100);
	setupHID();
	delay(10);
#endif
#if MASS_ENABLED
	Serial.println(F("Initializing MassStorage"));
	initMassStorage();
	Serial.println(F("Initialized MassStorage"));
#endif
	fulloledupdate();


	char key = matrix.getKey();
	if (key != 0x00) // For special conditions
	{
		switch (key)
		{
		case KEY_B:
			operateMode = BLUETOOTH;
			Serial.println(F("Forced mode to bluetooth"));
			break;
		case KEY_C:
			operateMode = CHARGING;
			Serial.println(F("Forced mode to charging"));
			break;
		case KEY_U:
			operateMode = CABLE;
			Serial.println(F("Forced mode to cable(HID)"));
			break;
		default:
			break;
		}
	}

#if HID_ENABLED || MASS_ENABLED
	initMillis = millis();
	Serial.println("Waiting for USB");
	while (!TinyUSBDevice.mounted() && millis() - initMillis < 1000)
	{
		delay(1);
	}
	if (TinyUSBDevice.mounted())
	{
		Serial.printf("USB Mounted in %u millis\r\n", millis() - initMillis);
	}
	else
	{
		Serial.println("USB not mounted");
	}
#endif

	Serial.println(F("Initializing Done, Keyboard is ready"));

}

void secondsOnTick() {
	if (seconds - menuActivationTime > menuReturnSeconds && menuActive) {
#if DEBUG
		Serial.println(F("Timer of menu ran out"));
#endif
		menuActive = false;
		fulloledupdate();
	}
	secondTicked = false;
}


void CompositeSerialAction() {

}

void loop() {
	if (secondTicked) {
		secondsOnTick();
	}

	checkBatteryAction.check();
#if BT_ENABLED
	if (bt->loop())
	{
		String btEvent = bt->getEvent();
		if (btEvent.startsWith("CONNECT"))
		{
			bluetoothConnected = true;
		}
		else if (btEvent.startsWith("DISCONNECT"))
		{
			bluetoothConnected = false;
		}
	}
#endif
#if HID_ENABLED || MASS_ENABLED
	if (TinyUSBDevice.suspended())
	{
		Serial.println("WAKEUP!");
		TinyUSBDevice.remoteWakeup();
	}
#endif
	if (operateMode != CHARGING) 
	{
#if MOUSE_ENABLED
		doMouseStuffAction.check();
#endif
#if ENCODER_ENABLED
		if (encoderInterupted) 
		{
			handleEncoder();
			if (lastEncPos != currentEncPos)
			{

				if (settingsActive) 
				{
					if (encoder->increased())
					{
						if (settingsindex != 1)
						{
							settingsindex++;
						}
					}
					else if (encoder->decreased())
					{
						if (settingsindex != 0)
						{
							settingsindex--;
						}
					}
				}
				else if (menuActive) 
				{
					if (encoder->increased())
					{
						if (menuindex != 0)
						{
							menuindex++;
						}
					}
					else if (encoder->decreased())
					{
						if (menuindex != 0)
						{
							menuindex--;
						}
					}
				}
				else 
				{
					if (encoder->increased())
					{
						if (funcindex != 9)
						{
							funcindex++;
						}
					}
					else if (encoder->decreased())
					{
						if (funcindex != 0)
						{
							funcindex--;
						}
					}
				}
			}
			if (encoder->buttonDoublePressed())
			{
				funcType = settings.functypes[funcindex];
				fulloledupdate();
			}
			if (encoder->buttonPressed()) 
			{
				if (!menuActive) 
				{
					Serial.println("ACTIVATE MENU");
					menuindex = 0;
					menuActive = true;
					menuActivationTime = seconds;
					fulloledupdate();
				}
				else 
				{
					menuActivationTime = seconds;// Refresh of seconds
					if (menuindex == 0) 
					{
						settingsActive = true;
						fulloledupdate();
					}
				}
			}
		}
#endif
#if MATRIX_ENABLED
		checkKeys();
#endif
	}
}
