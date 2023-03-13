#include <math.h>
#include <ArduinoJson.h>
#include "function.h"

StaticJsonDocument<200> joy;

float time;
unsigned long previousMillis = 0;   // stores the last time the sensors were read
const unsigned long interval = 2; // interval at which to read the sensors (in ms)

int ini_manette = 0;

void setup() {

  Serial.begin(500000);
 
}

void loop() {
  float inputs[6] = {0,0,0,0,0,0};
  float Prop[4] = {0,0,0,0};
  

  // ================================== Lecture du joystick ================================
  if (millis() - previousMillis >= interval) 
  {
    previousMillis = millis();
    if (Serial.available() > 0)
    {
      String DATA_entr = Serial.readStringUntil('\n');  //Un json se fini par un \n
      joystick_lec(DATA_entr, inputs, Prop, joy, 1);
    }
  }
}
