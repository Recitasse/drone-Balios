#include "function.h"
#include <Arduino.h>

class HC12
{
  private:
    int TX;
    int RX;
    String DATA_IN;
    unsigned long previousMillis_in = 0;
    unsigned long previousMillis_out = 0;
    unsigned long interval_in = 2;
    unsigned long interval_out = 250;
    float dir[3];
    bool transmission = true;
    bool check_sum_cond = false;
    
    struct commande_template {
      float X;
      float Y;
      float Psi;
      int mode;
      float Prop[4] = {1000.0, 1000.0, 1500.0, 1500.0};
    } commande;
    
  public:
    HC12(unsigned long interval_in, unsigned long interval_out) {
      this->interval_in = interval_in;
      this->interval_out = interval_out;
    }

  void communication()
  {
    // Reception à C2 ======================================
    unsigned long currentMillis_in = millis();
    if (currentMillis_in - previousMillis_in >= interval_in)
    {
      
      this->previousMillis_in = millis();
      if (Serial2.available()) 
      {
        char c = Serial2.read();
        if(c == 'S')
        {
          int it = 1;
          this->DATA_IN = "S";
          while(c != 'E' && it <18)
          {
            c = Serial2.read();
            this->DATA_IN += c;
            it += 1;
          }
        }
      }
      
      if(check_sum(DATA_IN, 5, 18, 11, 'S', 'E') && verif_integrite(DATA_IN))
      {
        float data[4];
        int index[5];
        int k = 0;
        for(int i=0; i<=DATA_IN.length(); i++)
        {
          if(DATA_IN[i] == ',')
          {
            index[k] = i+1;
            k++;
          }
        }

        data[0] = atoi(DATA_IN.substring(index[0], index[1]).c_str());
        data[1] = atoi(DATA_IN.substring(index[1], index[2]).c_str());
        data[2] = atoi(DATA_IN.substring(index[2], index[3]).c_str());
        data[3] = atoi(DATA_IN.substring(index[3], index[4]).c_str());
          
        this->commande.X = data[1];
        this->commande.Y = data[2];
        this->commande.Psi = 2*(data[3]-100)/256*(data[0]-228)/128;

        this->dir[0] = commande.Psi;
        this->dir[1] = commande.X;
        this->dir[2] = commande.Y;

        /*Serial.print(dir[0]);
        Serial.print("\t");
        Serial.print(dir[1]);
        Serial.print("\t");
        Serial.println(dir[2]);*/
      }
    }
  }

  void envoyer(String DATA_OUT)
  {
    // Envoie à C1 ==========================================
    unsigned long currentMillis_out = millis();
    if (currentMillis_out - previousMillis_out >= interval_out)
    {
      
      this->previousMillis_out = millis();
      if (Serial2.available()) 
      {
        char decomp[DATA_OUT.length()+1];
        DATA_OUT.toCharArray(decomp, sizeof(decomp));
        Serial2.write(decomp, sizeof(decomp));
      }
    }
  }

  float* get_propulsion()
  {
    return commande.Prop;
  }

  void afficher_prop()
  {
    for(int i=0; i<4; i++)
    {
      Serial.print(commande.Prop[i]);
      Serial.print(", \t");
    }
    Serial.print("\n");
  }

  void get_commande(float* commande)
  {
    commande[0] = dir[0];
    commande[1] = dir[1];
    commande[2] = dir[2];
  }
};
