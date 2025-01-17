#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include <Arduino.h>
#include <Adafruit_TinyUSB.h>
#include <KeyboardBase.h>

class KeyboardClass : public KeyboardBase
{
 private:
    uint8_t keyboard_report_ID;
    uint8_t consumer_report_ID;
    Adafruit_USBD_HID* hid;
protected:
    void LEDcallbackAttached() override;
public:
    void begin(uint8_t keyboard_report_ID,uint8_t consumer_report_ID, Adafruit_USBD_HID* hid_instance);

    void sendReport(KeyReport report) override;
    void sendConsumerReport(uint16_t key) override;

};

extern KeyboardClass USBKeyboard;

#endif
