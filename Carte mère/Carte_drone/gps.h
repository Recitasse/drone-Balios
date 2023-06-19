#include <TinyGPS++.h>
#include <Arduino.h>

class GPS {
private:
    int baud_rate;
    float latitude;
    float longitude;
    String GPS_DATA = ",";
    TinyGPSPlus gps;

public:
    GPS() {}

    void begin_gps(int baud_rate) {
      this->baud_rate = baud_rate;
      Serial1.begin(9600);
      String baude = "$PMTK251," + String(baud_rate);
      Serial1.println(baude);
      Serial1.begin(baud_rate);
    }

    void raw_values()
    {
      String raw_data;
      while (Serial1.available()) {
          char c = Serial1.read();
          raw_data += c;
      }
    }

    String position_gps() {
        while (Serial1.available()) {
            byte gpsData = Serial1.read();
            gps.encode(gpsData);
        }
        if (gps.location.isValid()) {
            this->latitude = gps.location.lat();
            this->longitude = gps.location.lng();
            this->GPS_DATA = String(latitude, 6) + "," + String(longitude, 6);
        }
        return GPS_DATA;
    }

    void afficher_gps() {
        position_gps();
        Serial.println("Latitude : " + String(latitude, 6) + ", longitude : "+String(longitude, 6));
    }
};
