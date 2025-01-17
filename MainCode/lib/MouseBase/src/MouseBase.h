/*
 Name:		MouseBase.h
 Created:	1/11/2024 5:44:50 PM
 Author:	Senna
 Editor:	http://www.visualmicro.com
*/

#ifndef _MouseBase_h
#define _MouseBase_h

#include <Arduino.h>

typedef struct
{
    uint8_t buttons;
    int8_t x;
    int8_t y;
    int8_t scroll;
    int8_t pan;
} MouseReport;

typedef enum
{
    MOUSE_LEFT = 1,
    MOUSE_RIGHT = 2,
    MOUSE_MIDDLE = 4,
    MOUSE_X = 8,
    MOUSE_Y = 16,
    MOUSE_ALL = (MOUSE_LEFT | MOUSE_RIGHT | MOUSE_MIDDLE | MOUSE_X | MOUSE_Y)
} MouseButtons;

class MouseBase
{
private:
protected:
    uint8_t _buttons;
    void buttons(uint8_t b);
public:
    void click(uint8_t b);
    void move(int8_t x, int8_t y, int8_t scroll = 0, int8_t pan = 0);
    void press(uint8_t b);
    void release(uint8_t b);
    void releaseAll();
    bool isPressed(uint8_t b);
    virtual void sendMouseReport(MouseReport report) = 0;
};

#endif

