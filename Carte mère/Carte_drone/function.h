#ifndef MYHEADER_H
#define MYHEADER_H
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <TinyGPS.h>

float signe(float x);
void joystick_lec(float* etats, float* Prop, int autom);
bool check_sum(String message, int virgule, int max_length, int min_length, char deb, char fin);
void redim(float fac_psi, float fac_vx, float fac_vy, float* &Commande);
String get_coord(SoftwareSerial serialgps, TinyGPS gps);
bool verif_integrite(String message);

typedef struct {
  float vx = 0;
  float vy = 0;
  float AngleX;
  float AngleY;
  float AngleZ;
  float Vgz;
} etats;

typedef struct {
  int start_time = 0;
  int end_time = 0;
  float sx = 0;
  float sx_old = 0;
  float sy = 0;
  float sy_old = 0;
} capteur;

typedef struct {
  float commande;
  float erreur = 0;
  float erreurm1 = 0;
  float integral = 0;
  float derive = 0;
} regul;

#endif
