#include "DHT.h"
#include "function.h"
#include <Arduino.h>

class HUMIDITE_TEMP
{
  private:
    int signal_pin;
    float humidite;
    float temperature;
    int delais_mes = 10000;
    DHT capteur_humidite_temperature;

  public:
    HUMIDITE_TEMP(int signal_pin) : signal_pin(signal_pin), capteur_humidite_temperature(signal_pin, DHT11)
    {
      this->humidite = 0;
      this->temperature = 0;
    }

    void hum_temp_begin(){capteur_humidite_temperature.begin();}

    void HUMIDITE_TEMP_DELAIS(int delais_mes){this->delais_mes = delais_mes;}

    float mesurer_humidite_temp(capteur& humidite_data, capteur& temp_data)
    {
      this->temperature = capteur_humidite_temperature.readTemperature();
      this->humidite = capteur_humidite_temperature.readHumidity();
      humidite_data.sy = humidite;
      temp_data.sy = temperature;
    }

    float filtre_humidite_temp(float wc, capteur& humidite_data, capteur& temp_data) 
    {
      mesurer_humidite_temp(humidite_data, temp_data);
      float dt_humid = humidite_data.end_time - humidite_data.start_time;
      humidite_data.sx = humidite;
  
      if (humidite_data.sx < 0 || humidite_data.sx > 100) {
        humidite_data.sx = humidite_data.sx_old;
      }
  
      humidite_data.sy = (dt_humid * (humidite_data.sx + humidite_data.sx_old) - humidite_data.sy_old * (dt_humid - 2 * wc)) / (dt_humid + 2 * wc);
      humidite_data.sx_old = humidite_data.sx;
      humidite_data.sy_old = humidite_data.sy;
      
      temp_data.sx = temperature;
  
      if (temp_data.sx < 0 || temp_data.sx > 100) {
        temp_data.sx = temp_data.sx_old;
      }
  
      temp_data.sy = (dt_humid * (temp_data.sx + temp_data.sx_old) - temp_data.sy_old * (dt_humid - 2 * wc)) / (dt_humid + 2 * wc);
      temp_data.sx_old = temp_data.sx;
      temp_data.sy_old = temp_data.sy;
  
    }

    void afficher_humidite_temp()
    {
      Serial.print("Humidité : ");
      Serial.print(humidite);
      Serial.print("%, température : ");
      Serial.print(temperature);
      Serial.println(" °C.");
    }
};
