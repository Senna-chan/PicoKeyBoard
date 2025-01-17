//
//
//

#include "HIDMouse.h"

void MouseClass::begin(uint8_t report_ID, Adafruit_USBD_HID* hid_instance)
{
    this->report_ID = report_ID;
    this->hid = hid_instance;
}

void MouseClass::end(void)
{

}

void MouseClass::sendMouseReport(MouseReport report)
{
    _buttons = report.buttons;
    if (!hid->mouseReport(report_ID, report.buttons, report.x, report.y, report.scroll, report.pan))
    {
        Serial.println("Failed to send mouse report");
    }
}



MouseClass USBMouse;
