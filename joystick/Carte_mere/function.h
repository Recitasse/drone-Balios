#ifndef MYHEADER_H
#define MYHEADER_H
#include <Arduino.h>

float signe(float x);
void explode(String str, String delimiteur, String *parts, int part);
int joystick_lec(String json, float* inputs, float* Prop, StaticJsonDocument<200>& joy, int aff);
float dist_calc(int trig, int echo, float temp);

void JSON_SENSOR(float dist, float latitude, float longitude, float altitud, float vx, float vy, float vz, float gx, float gy, float gz);
void JSON_INPUT(float vx, float vy, float vz, float gx, float gy, float gz);

#endif
