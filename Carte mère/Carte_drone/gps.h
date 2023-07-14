#include <TinyGPS.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
/*
  while(serialgps.available()) 
  {
    int c = serialgps.read(); 
    if(gps.encode(c)) 
    {
      float latitude, longitude;
      gps.f_get_position(&latitude, &longitude);
      Serial.print("Latitud/Longitud: "); 
      Serial.print(latitude,5); 
      Serial.print(", "); 
      Serial.println(longitude,5);
      gps.stats(&chars, &sentences, &failed_checksum);
    }
  }
  */
