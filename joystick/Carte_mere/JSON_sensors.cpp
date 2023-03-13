#include <ArduinoJson.h>
#include <Arduino.h>

void JSON_SENSOR(float dist, float latitude, float longitude, float altitud, float vx, float vy, float vz, float gx, float gy, float gz)
{
  StaticJsonDocument<200> sensors_output;
  sensors_output["BATHYMETRIE"]["PROFONDEUR"] = dist;
  sensors_output["BATHYMETRIE"]["LONGITUDE"] = longitude;
  sensors_output["BATHYMETRIE"]["LATITUDE"] = latitude;
  sensors_output["BATHYMETRIE"]["ALTITUDE"] = altitud;

  String DATA_SENSORS;
  serializeJson(sensors_output, DATA_SENSORS);
  Serial.println(DATA_SENSORS);
}

void JSON_INPUT(float vx, float vy, float vz, float gx, float gy, float gz)
{
  StaticJsonDocument<300> sensors_input;
  sensors_input["ETAT"]["VITESSE_X"] = vx;
  sensors_input["ETAT"]["VITESSE_Y"] = vy;
  sensors_input["ETAT"]["VITESSE_Z"] = vz;
  sensors_input["ETAT"]["GYRRO_X"] = gx;
  sensors_input["ETAT"]["GYRRO_Y"] = gy;
  sensors_input["ETAT"]["GYRRO_Z"] = gz;

  String DATA_INPUTS;
  serializeJson(sensors_input, DATA_INPUTS);
  Serial.println(DATA_INPUTS);
}
