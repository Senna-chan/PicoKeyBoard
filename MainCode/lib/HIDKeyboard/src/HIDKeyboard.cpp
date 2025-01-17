#include "HIDKeyboard.h"

static void hid_report_callback(uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize)
{
	(void)report_id;
	(void)bufsize;

	// LED indicator is output report with only 1 byte length
	if (report_type != HID_REPORT_TYPE_OUTPUT) return;

	// The LED bit map is as follows: (also defined by KEYBOARD_LED_* )
	// Kana (4) | Compose (3) | ScrollLock (2) | CapsLock (1) | Numlock (0)
	uint8_t ledIndicator = buffer[0];
	USBKeyboard.ledCB(ledIndicator &= KEYBOARD_LED_NUMLOCK, ledIndicator &= KEYBOARD_LED_CAPSLOCK, ledIndicator &= KEYBOARD_LED_SCROLLLOCK, USBKeyboard.ledCBdata);
}

void KeyboardClass::LEDcallbackAttached()
{
	hid->setReportCallback(NULL, hid_report_callback);
}

void KeyboardClass::begin(uint8_t keyboard_report_ID, uint8_t consumer_report_ID, Adafruit_USBD_HID* hid_instance)
{
	this->keyboard_report_ID = keyboard_report_ID;
	this->consumer_report_ID = consumer_report_ID;
	this->hid = hid_instance;
}

void KeyboardClass::sendReport(KeyReport keys)
{
	hid->keyboardReport(keyboard_report_ID, keys.modifiers, keys.keys);
}

void KeyboardClass::sendConsumerReport(uint16_t key) 
{
	hid->sendReport16(consumer_report_ID, key);
}

KeyboardClass USBKeyboard;
