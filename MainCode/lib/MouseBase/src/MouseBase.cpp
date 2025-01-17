/*
 Name:		MouseBase.cpp
 Created:	1/11/2024 5:44:50 PM
 Author:	Senna
 Editor:	http://www.visualmicro.com
*/

#include "MouseBase.h"

void MouseBase::click(uint8_t b)
{
    _buttons = b;
    move(0, 0);
    _buttons = 0;
    move(0, 0);
}

void MouseBase::move(int8_t x, int8_t y, int8_t scroll, int8_t pan)
{
    MouseReport report =
    {
        .buttons = _buttons,
        .x = x,
        .y = y,
        .scroll = scroll,
        .pan = pan
    };
    sendMouseReport(report);
}


void MouseBase::buttons(uint8_t b)
{
    if (b != _buttons) {
        _buttons = b;
        move(0, 0);
    }
}

void MouseBase::press(uint8_t b)
{
    buttons(_buttons | b);
}

void MouseBase::release(uint8_t b)
{
    buttons(_buttons & ~b);
}

void MouseBase::releaseAll()
{
    buttons(0);
}

bool MouseBase::isPressed(uint8_t b)
{
    if ((b & _buttons) > 0) {
        return true;
    }
    return false;
}



