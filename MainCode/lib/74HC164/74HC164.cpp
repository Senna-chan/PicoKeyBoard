#include "74HC164.h"

void ShiftRegister_74HC164::init(uint8_t pin_DSA, uint8_t pin_DSB, uint8_t pin_clock, uint8_t pin_reset, ShiftRegister_74HC164 *parent) 
{
    _pin_DSA = pin_DSA;
    _pin_DSB = pin_DSB;
    _pin_clock = pin_clock;
    _pin_reset = pin_reset;
    if(parent != nullptr){
        this->parent = parent;
        parent->child = this;
    }
}

void ShiftRegister_74HC164::set(uint16_t bit, uint8_t value)
{
    
}


void ShiftRegister_74HC164::set(uint16_t bit, uint8_t value) {
    
}

void ShiftRegister_74HC164::write_data() {
    
}

void ShiftRegister_74HC164::shift(uint8_t value, uint16_t amount) {
    
}

void ShiftRegister_74HC164::clear_data() {
    
}

void ShiftRegister_74HC164::write_high() {
    digitalWrite(_pin_DSA, HIGH);
    digitalWrite(_pin_DSB, HIGH);
}

void ShiftRegister_74HC164::write_low() {
    digitalWrite(_pin_DSA, LOW);
    digitalWrite(_pin_DSB, LOW);
}

void ShiftRegister_74HC164::do_clock_pulse() {
    digitalWrite(_pin_clock, HIGH);
    digitalWrite(_pin_clock, LOW);
}