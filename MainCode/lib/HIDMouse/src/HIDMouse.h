// HIDMouse.h

#ifndef _HIDMOUSE_h
#define _HIDMOUSE_h

#include <Adafruit_TinyUSB.h>
#include <MouseBase.h>

class MouseClass : public MouseBase
{
private:
    uint8_t report_ID;
    Adafruit_USBD_HID* hid;
protected:
public:
    void begin(uint8_t report_ID, Adafruit_USBD_HID *hid_instance);
    void end(void);
    virtual void sendMouseReport(MouseReport report) override;
};

extern MouseClass USBMouse;
#endif
