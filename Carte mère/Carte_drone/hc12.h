#include "function.h"
#include <SoftwareSerial.h>
#include <Arduino.h>

class HC12
{
  private:
    int TX;
    int RX;
    int baud_rate;
    String DATA_IN;
    unsigned long previousMillis_in = 0;
    unsigned long previousMillis_out = 0;
    unsigned long interval_in;
    unsigned long interval_out;
    bool transmission = true;
    bool check_sum_cond = false;
    
    struct commande_template {
      short int X;
      short int Y;
      int Psi;
      int mode;
      float Prop[4] = {1500.0, 1500.0, 1500.0, 1500.0};
    } commande;
    
    SoftwareSerial hc12_module;
    
  public:
    HC12(int RX, int TX, unsigned long interval) : hc12_module(RX, TX) {
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

    float* c12c2()
    {
      float data[4];
      unsigned long currentMillis_in = millis();

      // Tout les interval de temps
      if (currentMillis_in - previousMillis_in >= interval_in)
      {
        this->previousMillis_in = currentMillis_in;

        // Si le module est accessible
        if(hc12_module.available())
        {
          char c = hc12_module.read();
          if(c == 'S')
          {
            int it = 1;
            this->DATA_IN = "S";
            while(c != 'E' && it <18)
            {
              c = hc12_module.read();
              this->DATA_IN += c;
              it += 1;
            }
          }
        }
        // On vérifie la validité des informations reçues
        if(check_sum(DATA_IN, 5, 18, 11, 'S', 'E'))
        {
          int index[5];
          int k = 0;
          for(int i=0; i<=DATA_IN.length(); i++)
          {
            if(DATA_IN[i] == ',')
            {
              index[k] = i+1;
              k += 1;
            }
          }
          for(int i=0; i<5-1; i++)
          {
            data[i] = atof(DATA_IN.substring(index[i], index[i+1]-1).c_str());
            if(data[i] > 356 || data[i] < -2)
            {
              this->transmission = false;
            }
          }
          
          if(data[0] < 100)
          {
            this->transmission = false;
          }
          else if(data[3] < 100)
          {
            this->transmission = false;
          }
          else if(data[1] < -2 || data[1] > 2)
          {
            this->transmission = false;
          }
          
          else if(data[2] < -2 || data[2] > 2)
          {
            this->transmission = false;
          }
          this->check_sum_cond = true;
        }

        // Si les données sont valides alors : 
        if(transmission == true && check_sum_cond == true);
        {
          this->commande.X = data[1];
          this->commande.Y = data[2];
          this->commande.Psi = (data[3]-100)/256*(data[0]-228)/128;

          int dir[3] = {commande.Psi, commande.X, commande.Y};
          joystick_lec(dir, commande.Prop, 0, 1); // le 1 est le mode de commande, à ajouter.

          // Ajout des seuils
          for(int i=0; i<4; i++)
          {
            commande.Prop[i] = ((commande.Prop[i]*1000/3)+1000-800)/8;
            if(commande.Prop[i]<1500)
            {
              commande.Prop[i] = 1500;
            }
            else if(commande.Prop[i]>2000)
            {
              commande.Prop[i] = 2000;
            }
            commande.Prop[i] = int(commande.Prop[i]);
          }

          // On se prépare au prochain input
          return commande.Prop;
          this->DATA_IN = "";
          this->check_sum_cond = false;
          this->transmission = true;
          for(int i=0; i<4; i++)
          {
            this->commande.Prop[i] = 1500.0;
          }
        }
      }
      else
      {
        this->DATA_IN = "";
        this->check_sum_cond = false;
        this->transmission = true;
      }
    }

    void afficher_input()
    {
      Serial.println(DATA_IN);
    }
  
    void afficher_commande()
    {
      for(int i=0; i<4; i++)
      {
        Serial.print(commande.Prop[i]);
        Serial.print(", \t");
      }
      Serial.print("\n");
    }


    void c22c1(String DATA_OUT)
    {
      unsigned long currentMillis_out = millis();

      // Tout les interval de temps
      if (currentMillis_out - previousMillis_out >= interval_out)
      {
        this->previousMillis_out = currentMillis_out;
        if(hc12_module.available())
        {
          char decomp[DATA_OUT.length()+1];
          DATA_OUT.toCharArray(decomp, sizeof(decomp));
          hc12_module.write(decomp, sizeof(decomp));
        }
      }
    }
    
};
