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
#include <SoftwareSerial.h>
#include <TinyGPS.h>

#define ECHO_SONAR 5 // Pin echo du sonar
#define TRIG_SONAR 6 // Pin trigger du sonar 
#define ESC_TL_PWM 7 // Pin pour les ESC
#define ESC_TR_PWM 8 // Pin pour les ESC
#define ESC_BL_PWM 9 // Pin pour les ESC
#define ESC_BR_PWM 10 // Pin pour les ESC
#define DHTPIN 4
#define ARRET 45 // bouton d'arret
#define MANUEL 41 // led verte
#define AUTO 43 // led jaune

TinyGPS gps;

// ====================== Initialisation des classes et struct ========================


SONAR sonar(TRIG_SONAR, ECHO_SONAR, 20);
HUMIDITE_TEMP hum_temp(DHTPIN);
HC12 hc(2, 1500);
GYRO_ACCEL gyro;
MOTEURS moteurs(ESC_TL_PWM, ESC_TR_PWM, ESC_BL_PWM, ESC_BR_PWM);

capteur sonar_data, humidite_data, temp_data;
capteur gyro_data_vx, gyro_data_vy, gyro_data_gx, gyro_data_gy, gyro_data_gz, gyro_data_vgz;

unsigned int gyro_start = millis();
unsigned int gyro_end;
float* Prop;
etats data_gyro;
float Commande[5];
float states[4];


void setup() {
  Serial.begin(115200);
  Serial1.begin(9600);
  Serial2.begin(19200);
  hum_temp.hum_temp_begin();
  sonar.sonar_begin();
  gyro.gyro_begin();
  moteurs.MOTEUR_INIT();
  pinMode(ARRET, OUTPUT);
  pinMode(MANUEL, OUTPUT);
  pinMode(AUTO, OUTPUT);
}


void loop() {

  hc.communication();
  hc.get_commande(Commande);
 
  sonar_data.start_time = micros();
  sonar.filtre_distance(0.1, sonar_data);
  sonar_data.end_time = micros();
  
  humidite_data.start_time = micros();
  hum_temp.mesurer_humidite_temp(humidite_data, temp_data);
  humidite_data.end_time = micros();

  String gps_lat = "";
  String gps_long = "";
  while (Serial1.available()) 
  {
    int c = Serial1.read(); 
    if(gps.encode(c)) 
    {
      float latitude, longitude;
      gps.f_get_position(&latitude, &longitude);
      gps_long = String(longitude, 6);
      gps_lat = String(latitude, 6);
    }
  }
  
  gyro_end = millis();
  data_gyro = gyro.gyro_etats(gyro_end-gyro_start);
  gyro_start = millis();
  gyro.get_data_reg(states);

  String prof = "2.36";
  gps_lat = "47.127411";
  gps_long = "1.127411";
  String DATA_OUT = "V,"+String(int(sonar_data.sy))+","+String(int(humidite_data.sy))+","+String(int(temp_data.sy))+","+gps_lat+","+gps_long+","+prof+",F";
  hc.envoyer(DATA_OUT);

  moteurs.PID(states, Commande);
}
