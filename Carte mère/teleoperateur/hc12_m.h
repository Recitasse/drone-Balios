#ifndef HC12_H
#define HC12_H
#include "function.h"
#include <SoftwareSerial.h>
#include <Arduino.h>

class HC12_m
{
  private:
    int TX;
    int RX;
    int baud_rate;
    String DATA_IN;
    String DATA_OUT;
    unsigned long previousMillis_in = 0;
    unsigned long previousMillis_out = 0;
    unsigned long interval_in;
    unsigned long interval_out;
    
    SoftwareSerial hc12_module;
    
  public:
    HC12_m(int RX, int TX, unsigned long interval) : hc12_module(RX, TX) {
      this->TX = TX;
      this->RX = RX;
      this->interval_in = interval_in;
      this->interval_out = interval_out;
    }

    void begin_hc12(int baud_rate)
    {
      this->baud_rate = baud_rate;
      hc12_module.begin(baud_rate);
    }

    void pc2c1()
    {
      unsigned long currentMillis_in = millis();

      // Tout les interval de temps
      if (currentMillis_in - previousMillis_in >= interval_in)
      {
        this->previousMillis_in = currentMillis_in;

        // Si le module est accessible
        if(Serial.available())
        {
          char c = Serial.read();
          if(c == 'S')
          {
            int it = 1;
            this->DATA_IN = "S";
            while(c != 'E' && it <18)
            {
              c = Serial.read();
              this->DATA_IN += c;
              it += 1;
            }
          }
        }
        // On vérifie la validité des informations reçues
        if(check_sum(DATA_IN, 5, 18, 11, 'S', 'E'))
        {
          this->DATA_IN = DATA_IN;
          Serial.println(DATA_IN);
        }
      }
      else
      {
        this->DATA_IN = "";
      }
      
      if(hc12_module.available())
      {
        char decomp[DATA_IN.length()+1];
        DATA_IN.toCharArray(decomp, sizeof(decomp));
        hc12_module.write(decomp, sizeof(decomp));
      }
    }
  
    void c12c2()
    {
      // Tout les interval de temps
      if(hc12_module.available())
      {
        char decomp[DATA_IN.length()+1];
        DATA_IN.toCharArray(decomp, sizeof(decomp));
        hc12_module.write(decomp, sizeof(decomp));
      }
    }

    bool c22c1()
    {
      if(hc12_module.available())
      {
        char c = hc12_module.read();
        if(c == 'V')
        {
          int it = 1;
          this->DATA_OUT = "V";
          while(c != 'F' && it <18)
          {
            c = hc12_module.read();
            this->DATA_OUT += c;
            it += 1;
          }
        }
        return true;
      }
      else
      {
        DATA_OUT = "";
        return false;
      }
    }

    void c12pc()
    {
      // Tout les interval de temps
      if(Serial.available())
      {
        char decomp[DATA_OUT.length()+1];
        DATA_OUT.toCharArray(decomp, sizeof(decomp));
        Serial.write(decomp, sizeof(decomp));
      }
    }
    
};
#endif // HC12_H
