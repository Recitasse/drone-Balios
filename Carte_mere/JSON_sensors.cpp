#include <ArduinoJson.h>
#include <Arduino.h>

void JSON_SENSOR(float dist, float latitude, float longitude, float altitud)
{
  StaticJsonDocument<600> sensors;
  sensors["SONAR"]["D"] = dist;

  String DATA_SENSORS;
  serializeJson(sensors, DATA_SENSORS);

  Serial.println(DATA_SENSORS);
}
