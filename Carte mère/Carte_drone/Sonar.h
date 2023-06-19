#include <Arduino.h>
#include "function.h"

class SONAR {
  private:
    int TRIG_SONAR;
    int ECHO_SONAR;
    float distance;
    float temp;

  public:
    SONAR(int TRIG_SONAR, int ECHO_SONAR, float temp)
    {
      this->TRIG_SONAR = TRIG_SONAR;
      this->ECHO_SONAR = ECHO_SONAR;
      this->temp = temp;
      this->distance = 0;
    }

    void sonar_begin()
    {
      pinMode(TRIG_SONAR, OUTPUT);
      pinMode(ECHO_SONAR, INPUT);
    }

    float mesurer_sonar()
    {
      float k_sonar = (331.5+0.607*temp)/2000000.0;
      digitalWrite(TRIG_SONAR, LOW);
      delayMicroseconds(2);
      digitalWrite(TRIG_SONAR, HIGH);
      delayMicroseconds(10);
      digitalWrite(TRIG_SONAR, LOW);
    
      unsigned long duration = pulseIn(ECHO_SONAR, HIGH, 30000);// 30ms 
      float distance = duration*k_sonar; // convert duration to distance in cm

      if(duration == 0){return -1;}
      else
      {
        this->distance = distance;
        return distance;
      }
    }

    void lire_distance()
    {
      Serial.println("Profondeur : " + String(distance));
    }

    float filtre_distance(float wc, capteur& sonar_data) 
    {
      float dt_sonar = sonar_data.end_time - sonar_data.start_time;
      sonar_data.sx = mesurer_sonar();
  
      if (sonar_data.sx < 0.26) {
        sonar_data.sx = sonar_data.sx_old;
      }
  
      sonar_data.sy = (dt_sonar * (sonar_data.sx + sonar_data.sx_old) - sonar_data.sy_old * (dt_sonar - 2 * wc)) / (dt_sonar + 2 * wc);
      sonar_data.sx_old = sonar_data.sx;
      sonar_data.sy_old = sonar_data.sy;
  
      return sonar_data.sy;
    }
};
