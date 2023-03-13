#ifndef MYHEADER_H
#define MYHEADER_H
#include <Arduino.h>

void joystick_lec(String json, float* inputs, float* Prop, StaticJsonDocument<200>& joy, int aff);

#endif
