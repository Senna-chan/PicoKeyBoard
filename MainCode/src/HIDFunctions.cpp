//
//
//

#include <Arduino.h>
#include "Config.h"

#include <Adafruit_TinyUSB.h>

#include <HIDKeyboard.h>
#include <HIDMouse.h>

#include <BTKeyboard.h>
#include <BTMouse.h>

#include "Variables.h"

#include "HIDFunctions.h"


static KeyboardBase* getKeyboard();
static MouseBase* getMouse();

/**
 * \brief Release EVERYTHING and resets mouse
 */
void releaseAllKeyboardMouse()
{
    releaseAllKeyboardKeys();
    moveMouse(0, 0, 0, 0);
    releaseMouseAll();
}

void pressMouse(uint8_t button)
{
    MouseBase* mouse = getMouse();
    if(!mouse) return;
    if (!mouse->isPressed(button))
    {
        mouse->press(button);
    }
}

void releaseMouse(uint8_t button)
{
    MouseBase* mouse = getMouse();
    if(!mouse) return;
    if (!mouse->isPressed(button))
    {
        mouse->release(button);
    }
}

void releaseMouseAll()
{
    MouseBase* mouse = getMouse();
    if(!mouse) return;
    mouse->releaseAll();
}

void moveMouseRel(int8_t x, int8_t y)
{
    moveMouse(x, y);
}

void moveMouse(int8_t x, int8_t y, int8_t wheelx, int8_t wheely)
{
    moveMouse(x, y);
    moveScrollWheel(wheelx, wheely);
}

void moveMouse(int8_t x, int8_t y)
{
    MouseBase* mouse = getMouse();
    if(!mouse) return;
    mouse->move(x, y);
}

void moveScrollWheel(int8_t scroll, int8_t pan)
{
    MouseBase* mouse = getMouse();
    if(!mouse) return;
    mouse->move(0, 0, scroll, pan);
}

void printKeyboardString(String string)
{
    KeyboardBase* keyboard = getKeyboard();
    if (!keyboard) return;
    keyboard->print(string);
}

void pressKeyboardKey(uint8_t key)
{
    KeyboardBase* keyboard = getKeyboard();
    if (!keyboard) return;
    keyboard->press(key);
}
void releaseKeyboardKey(uint8_t key)
{
    KeyboardBase* keyboard = getKeyboard();
    if (!keyboard) return;
    keyboard->release(key);
}

void releaseAllKeyboardKeys()
{
    KeyboardBase* keyboard = getKeyboard();
    if (!keyboard) return;
    keyboard->releaseAll();
}

void writeKeyboardKey(uint8_t key)
{
    KeyboardBase* keyboard = getKeyboard();
    if (!keyboard) return;
    keyboard->write(key);
}
void pressConsumerKey(uint16_t key)
{
    KeyboardBase* keyboard = getKeyboard();
    if (!keyboard) return;
    keyboard->sendConsumerReport(key);
}
void releaseConsumerKey()
{
    KeyboardBase* keyboard = getKeyboard();
    if (!keyboard) return;
    keyboard->sendConsumerReport(0);
}
void writeConsumerKey(uint16_t key)
{
    KeyboardBase* keyboard = getKeyboard();
    if (!keyboard) return;
    keyboard->sendConsumerReport(key);
    keyboard->sendConsumerReport(0);
}

void writeKeyReport(KeyReport report)
{
    if (report.modifiers == 0xFF) // MediaKeyboard key
    {
        writeConsumerKey(makeWord(report.keys[0], report.keys[1]));
    }
    else
    {
        KeyboardBase* keyboard = getKeyboard();
        if (!keyboard) return;
        keyboard->sendReport(report);
    }
}

static KeyboardBase* getKeyboard()
{
#if !(KEYBOARD_ENABLED)
    return NULL;
#endif
    if (operateMode == BLUETOOTH)
    {
#if BT_ENABLED
        return &BTKeyboard;
#endif
    }
    else if (operateMode == CABLE)
    {
#if HID_ENABLED
        return &USBKeyboard;
#endif
    }
    return NULL;
}

static MouseBase* getMouse()
{
#if !(MOUSE_ENABLED)
    return NULL;
#endif
    if (operateMode == BLUETOOTH)
    {
#if BT_ENABLED
        return &BTMouse;
#endif
    }
    else if (operateMode == CABLE)
    {
#if HID_ENABLED
        return &USBMouse;
#endif
    }
    return NULL;
}