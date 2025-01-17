/*
 Name:		BTMouse.cpp
 Created:	1/11/2024 5:44:36 PM
 Author:	Senna
 Editor:	http://www.visualmicro.com
*/

#include "BTMouse.h"

void BTMouse_::begin(BPLib* bluetoothLib)
{
    this->bluetooth = bluetoothLib;
}

void BTMouse_::end(void)
{

}

void BTMouse_::sendMouseReport(MouseReport report)
{
    _buttons = report.buttons;
    bluetooth->mouseReport.wheel = report.scroll;
    bluetooth->mouseReport.x = report.x;
    bluetooth->mouseReport.y = report.y;
    bluetooth->mouseReport.buttons = report.buttons;
    bluetooth->writeMouseReport();
}



BTMouse_ BTMouse;