#include <Arduino.h>

class ShiftRegister_74HC164 {
 private:
    uint8_t _pin_DSA;
    uint8_t _pin_DSB;
    uint8_t _pin_clock;
    uint8_t _pin_reset;

    void write_high();
    void write_low();
    void do_clock_pulse();
    uint8_t data[8];
 protected:
    ShiftRegister_74HC164* child;
    ShiftRegister_74HC164* parent;
    uint8_t children = 0;
    uint8_t parents = 0;
 public:
    void init(uint8_t pin_DSA, uint8_t pin_DSB, uint8_t pin_clock, uint8_t pin_reset, ShiftRegister_74HC164* parent = NULL);
    void set(uint16_t bit, uint8_t value);
    void write_data();
    void shift(uint8_t value = LOW, uint16_t amount = 1);
    void clear_data();
};