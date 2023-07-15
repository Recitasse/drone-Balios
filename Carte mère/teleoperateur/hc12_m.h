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
    String DATA_OUT = DATA_IN;
    String DATA_FROM;
    unsigned long previousMillis_in = 0;
    unsigned long previousMillis_out = 0;
    unsigned long previousMillis_from = 0;
    unsigned long interval_in = 2;
    unsigned long interval_out = 10;
    unsigned long interval_from = 25;

    bool OUT = true;
    bool FROM = true;

    SoftwareSerial hc12_module;

  public:
    HC12_m(int RX, int TX) : hc12_module(RX, TX) {
      this->TX = TX;
      this->RX = RX;
    }

    void begin_hc12(int baud_rate)
    {
      this->baud_rate = baud_rate;
      hc12_module.begin(baud_rate);
    }

    // ---------------------------------------------------

    void communication()
    {
      // Recepetion data_from
      unsigned long currentMillis_from = millis();
      if (currentMillis_from - previousMillis_from >= interval_from)
      {
        this->previousMillis_from = millis();
        if (hc12_module.available())
        {
          char c = hc12_module.read();
          if (c == 'V')
          {
            int it = 1;
            this->DATA_FROM = "V";
            while (c != 'F' && it <= 45)
            {
              c = hc12_module.read();
              this->DATA_FROM += c;
              it += 1;
            }
          }
        }
        //Serial.println(DATA_FROM);
        if(check_sum_out(DATA_FROM, 7, 45, 18, 'F'))
        {
          this->DATA_FROM = DATA_FROM;
          this->FROM = true;
          Serial.println(DATA_FROM);
        }
        else
        {
          this->DATA_FROM ="";
          this->FROM = false;
        }
        hc12_module.flush();
      }

      // ================ Envoie du in =========================
      unsigned long currentMillis_out = millis();
      if (currentMillis_out - previousMillis_out >= interval_out)
      {
        this->previousMillis_out = millis();
        hc12_module.print(DATA_IN);
      }
    }

    bool reception()
    {
      return FROM;
    }

    int prox()
    {
      if(FROM)
      {
        int deb = DATA_FROM.indexOf(",");
        int fin = DATA_FROM.indexOf(",", deb + 1);
        return atoi(DATA_FROM.substring(deb + 1, fin).c_str());
      }
      return -1;
    }

    void pc2c1()
    {
      if (millis() - previousMillis_in >= interval_in)
      {
        this->previousMillis_in = millis();
        if (Serial.available())
        {
          char c = Serial.read();
          if (c == 'S' || c == 'A' || c == 'C')
          {
            int it = 1;
            this->DATA_IN = c;
            while (c != 'E' && it <= 18)
            {
              c = Serial.read();
              this->DATA_IN += c;
              it += 1;
            }
          }
        }
        //Serial.println(DATA_IN);
        // On vérifie la validité des informations reçues
        if (check_sum(DATA_IN, 5, 20, 11, 'E'))
        {
          this->DATA_IN = DATA_IN;
        }
        else
        {
          this->DATA_IN = "";
        }
      }
      // TEMPORAIRE ======================================
    }
    // -------------------------------------------

};
#endif // HC12_H
