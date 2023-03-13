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
int joystick_lec(String json, float* inputs, float* Prop, StaticJsonDocument<200>& joy, int aff)
{
  
  
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


  // On calcul désormais les poussées

  float Log[6][4] = {
          {0,1,1,0},
          {1,1,0,0},
          {0,1,0,1},
          {1,0,0,1},
          {0,0,1,1},
          {1,0,1,0}
        };
  float Comm[3] = {signe(inputs[1]), signe(inputs[2]), signe(inputs[0])};

  if(inputs[4] != 1)
  {
    if(Comm[0] == 1)
    {
      for(int i=0; i<4; i++)
      {
        Prop[i] += abs(inputs[1])*Log[3][i];
      }
    }
    else if(Comm[0] == -1)
    {
      for(int i=0; i<4; i++)
      {
        Prop[i] += abs(inputs[1])*Log[0][i];
      }
    }
  
    if(Comm[1] == 1)
    {
      for(int i=0; i<4; i++)
      {
        Prop[i] += abs(inputs[2])*Log[4][i];
      }
    }
    else if(Comm[1] == -1)
    {
      for(int i=0; i<4; i++)
      {
        Prop[i] += abs(inputs[2])*Log[1][i];
      }
  
    }

    if(Comm[2] == 1)
    {
      for(int i=0; i<4; i++)
      {
        Prop[i] += abs(inputs[0])*Log[5][i];
      }
    }
    else if(Comm[2] == -1)
    {
      for(int i=0; i<4; i++)
      {
        Prop[i] += abs(inputs[0])*Log[2][i];
      }
  
    }
  

  }

  if(aff == 1 && (Prop[0] != 0 || Prop[1] != 0 || Prop[2] != 0 || Prop[3] != 0))
  {
      return 1;
  }
  else
  {
    return 0;
  }

}
