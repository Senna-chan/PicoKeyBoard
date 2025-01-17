/*
 Name:		KeyboardBase.h
 Created:	1/4/2024 2:39:15 PM
 Author:	Senna
 Editor:	http://www.visualmicro.com
*/

#ifndef _KeyboardBase_h
#define _KeyboardBase_h

#include <Arduino.h>
#include <Print.h>

#include "KeyboardCodes.h"
#include "ConsumerKeyCodes.h"

typedef struct
{
    uint8_t reportID = 1;
    uint8_t modifiers;
    uint8_t reserved;
    uint8_t keys[6];
} __packed KeyReport;

enum KeyboardMode {
    ASCII_TO_HID,
    RAW_HID
};


typedef void(*LedCallbackFcn)(bool numlock, bool capslock, bool scrolllock, void* cbData);

class KeyboardBase : public Print
{
private:
protected:
    uint8_t leds;
    bool adjustForHostCapsLock;
    KeyboardMode mode;
    uint8_t getKeyCode(uint8_t k, uint8_t* modifiersP);
    /**
     * Used to notify implementation class that a LEDcallback has been attached.
     * If onLED has not been called before begin then do this
     */
    virtual void LEDcallbackAttached() = 0;
public:
    KeyReport keyReport;
    void setAdjustForHostCapsLock(bool state) {
        adjustForHostCapsLock = state;
    }
    virtual size_t write(uint8_t k);
    size_t press(uint8_t k);
    size_t release(uint8_t k);
    void releaseAll(void);
    void setKeyboardMode(KeyboardMode newmode);
    uint8_t getLeds();

	virtual void sendReport(KeyReport keys) = 0;
    virtual void sendConsumerReport(uint16_t key) = 0;



    void onLED(LedCallbackFcn fcn, void* cbData = nullptr);
    // Public due to function ptr callback
    LedCallbackFcn ledCB;
    void* ledCBdata;
};

#endif

