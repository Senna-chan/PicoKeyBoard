#include "BTKeyboard.h"

static void ledCallback(uint8_t leds, void* cbData) {
    KeyboardBTClass* btkb = (KeyboardBTClass*)cbData;
    btkb->ledCB(leds & 0b001, leds & 0b010, leds & 0b010, btkb->ledCBdata);
}

void KeyboardBTClass::LEDcallbackAttached()
{
    bluetooth->addLEDCallback(ledCallback, this);
}

void KeyboardBTClass::begin(BPLib* bluetoothLib) {
    bluetooth = bluetoothLib;
}

void KeyboardBTClass::end(void) {

}

void KeyboardBTClass::sendReport(KeyReport keys) {
    bluetooth->keyReport.modifiers = keys.modifiers;
    bluetooth->keyReport.keys[0] = keys.keys[0];
    bluetooth->keyReport.keys[1] = keys.keys[1];
    bluetooth->keyReport.keys[2] = keys.keys[2];
    bluetooth->keyReport.keys[3] = keys.keys[3];
    bluetooth->keyReport.keys[4] = keys.keys[4];
    bluetooth->keyReport.keys[5] = keys.keys[5];
    bluetooth->writeKeyReport();
}

void KeyboardBTClass::sendConsumerReport(uint16_t key) {
    bluetooth->writeConsumer(key);
}

KeyboardBTClass BTKeyboard;
