#include <Arduino.h>

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

// LEcture des données du joystick
void joystick_lec(float* etats, float* Prop, int autom)
{
  float X = etats[1];
  float Y = etats[2];
  float Psi = etats[0];
  
  // =======================================
  
  float Log[6][4] = {
          {0,1,1,0},
          {1,1,0,0},
          {0,1,0,1},
          {1,0,0,1},
          {0,0,1,1},
          {1,0,1,0}
        };
  float Comm[3] = {signe(X), signe(Y), signe(Psi)};
  

  if(autom == 1)
  {
    // --------------- Pour l'angle psi ------------------
    if(Comm[2] == 1)
    {
      for(int i=0; i<4; i++)
      {
        Prop[i] += abs(Psi)*Log[5][i];
      }
    }
    else if(Comm[2] == -1)
    {
      for(int i=0; i<4; i++)
      {
        Prop[i] += abs(Psi)*Log[2][i];
      }
    }
    
    if(Psi > 0)
    {
      Prop[1] = 0.0;
      Prop[3] = 0.0;
    }
    else
    {
      Prop[0] = 0.0;
      Prop[2] = 0.0;
    }
    
    if(Comm[0] == 1)
    {
      for(int i=0; i<4; i++)
      {
        Prop[i] += abs(X)*Log[3][i];
      }
    }
    else if(Comm[0] == -1)
    {
      for(int i=0; i<4; i++)
      {
        Prop[i] += abs(X)*Log[0][i];
      }
    }
  
    if(Comm[1] == 1)
    {
      for(int i=0; i<4; i++)
      {
        Prop[i] += abs(Y)*Log[4][i];
      }
    }
    else if(Comm[1] == -1)
    {
      for(int i=0; i<4; i++)
      {
        Prop[i] += abs(Y)*Log[1][i];
      }
  
    }
  }
}
