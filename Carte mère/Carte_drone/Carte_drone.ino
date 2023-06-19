#include <Arduino.h>
#include <math.h>
#include "Wire.h"
#include "function.h"
#include "Sonar.h"
#include "dht.h"
#include "gps.h"
#include "gyro.h"
#include "hc12.h"
#include "moteurs.h"

#define ECHO_SONAR 2 // Pin echo du sonar
#define TRIG_SONAR 3 // Pin trigger du sonar 
#define HC12_RX 5 // Pin rx DU hc12
#define HC12_TX 6 // Pin tx du HC12
#define ESC_TL_PWM 7 // Pin pour les ESC
#define ESC_TR_PWM 8 // Pin pour les ESC
#define ESC_BL_PWM 9 // Pin pour les ESC
#define ESC_BR_PWM 10 // Pin pour les ESC
#define DHTPIN 4


// ====================== Initialisation des classes et struct ========================

SONAR sonar(TRIG_SONAR, ECHO_SONAR, 20);
HUMIDITE_TEMP hum_temp(DHTPIN);
GPS gps;
HC12 hc(HC12_RX, HC12_TX, 20);
GYRO_ACCEL gyro;
MOTEURS moteurs(ESC_TL_PWM, ESC_TR_PWM, ESC_BL_PWM, ESC_BR_PWM);

capteur sonar_data, humidite_data, temp_data;
capteur gyro_data_vx, gyro_data_vy, gyro_data_gx, gyro_data_gy, gyro_data_gz;

unsigned int gyro_start = millis();
unsigned int gyro_end;

void setup() {
  Serial.begin(115200);
  hum_temp.hum_temp_begin();
  gps.begin_gps(9600);
  hc.begin_hc12(19200);
  sonar.sonar_begin();
  gyro.gyro_begin();
  moteurs.MOTEUR_INIT();
  
}

void loop() {

  etats test;
  float* Prop = hc.c12c2();

  sonar_data.start_time = micros();
  sonar.filtre_distance(0.1, sonar_data);
  sonar_data.end_time = micros();
  
  humidite_data.start_time = micros();
  hum_temp.mesurer_humidite_temp(humidite_data, temp_data);
  humidite_data.end_time = micros();

  String GPS_DATA = gps.position_gps();
  
  gyro_end = millis();
  test = gyro.gyro_etats(gyro_end-gyro_start);
  gyro_start = millis();

  String DATA_OUT = "V,"+String(sonar_data.sy)+","+String(humidite_data.sy)+","+String(temp_data.sy)+","+GPS_DATA+",F";
  Serial.println(DATA_OUT);

  moteurs.propulse(Prop);


}
