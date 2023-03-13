#include <Arduino.h>
#include <ArduinoJson.h>

// Fonction signe
float signe(float x) {
  if (x > 0) {
    return 1;
  } else if (x < 0) {
    return -1;
  } else {
    return 1;
  }
}

// FOnction explode php
void explode(String str, String delimiteur, String *parts, int part) {
  int it = 0;
  int fin = 0;
  int IndDelimiteur = str.indexOf(delimiteur);

  while(IndDelimiteur != -1 && it < part-1)
  {
    parts[it] = str.substring(fin, IndDelimiteur);
    fin = IndDelimiteur +1;
    IndDelimiteur = str.indexOf(delimiteur, fin);
    it++;
  }
  parts[it] = str.substring(fin);
}

// LEcture des données du joystick
void joystick_lec(String json, float* inputs)
{
  
  StaticJsonDocument<200> joy;
  DeserializationError error = deserializeJson(joy, json);

  if (error) {
    return;
  }

  inputs[3] = joy["REGLAGE"]["MODE"];
  inputs[4] = joy["REGLAGE"]["AUTO"];
  inputs[5] = joy["REGLAGE"]["INVERSE"];

  inputs[0] = joy["POSITION"]["PSI"];
  inputs[1] = joy["POSITION"]["X"];
  inputs[2] = joy["POSITION"]["Y"];

  inputs[0] *= inputs[5];
  inputs[1] *= inputs[3]*inputs[5];
  inputs[2] *= inputs[3]*inputs[5];
}
