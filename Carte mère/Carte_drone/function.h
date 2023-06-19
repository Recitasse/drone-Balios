#ifndef MYHEADER_H
#define MYHEADER_H
#include <Arduino.h>

void joystick_lec(int* etats, float* Prop, int aff, int autom);
bool check_sum(String message, int virgule, int max_length, int min_length, char deb, char fin);

typedef struct {
  float vx;
  float vy;
  float AngleX;
  float AngleY;
  float AngleZ;
} etats;

typedef struct {
  int start_time = 0;
  int end_time = 0;
  float sx = 0;
  float sx_old = 0;
  float sy = 0;
  float sy_old = 0;
} capteur;


#endif
