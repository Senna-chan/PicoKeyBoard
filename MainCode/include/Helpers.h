// Helpers.h

#ifndef _HELPERS_h
#define _HELPERS_h
#include <Arduino.h>

#define analogReadVoltage(pin) analogRead(pin) * (3.3 / 4095)
#define between(value, min, max) ((value) < (max) && (value) > (min))
#define outside(value, min, max) ((value) > (max) || (value) < (min))
#define VERBOSECASELN(label) case label: Serial.println(#label); break;
#define VERBOSECASE(label) case label: Serial.print(#label); break;

bool handleEncoder();
uint8_t* read1bitBMP(char *fname, int* _w, int* _h);

#endif

