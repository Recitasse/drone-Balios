#ifndef MYHEADER_H
#define MYHEADER_H
#include <Arduino.h>

float signe(float x);
void explode(String str, String delimiteur, String *parts, int part);
void joystick_lec(String json, float* inputs);
float dist_calc(int trig, int echo, float temp);

void JSON_SENSOR(float dist, float latitude, float longitude, float altitud);

#endif
