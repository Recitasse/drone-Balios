#include <math.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <TinyGPS++.h>
#include "function.h"
#include <MPU6050.h>

int16_t gx, gy, gz, ax, ay, az;
float gyro_z,gyro_y,gyro_x;
float ax_out, ay_out, az_out; 
float time, dtMPU, timePrev;


MPU6050 mpu;
StaticJsonDocument<200> joy;

int echo_sonar = 4; // declare and initialize echo_sonar variable
int trig_sonar = 3; // sonar pin

//float dist_mes = 0;
//float dist_mes_pre = 0;
float prof;


SoftwareSerial SONAR(echo_sonar, trig_sonar);
SoftwareSerial GPS(6, 7);
TinyGPSPlus gps;

// Pour la manette
unsigned long previousMillis = 0;   // stores the last time the sensors were read
const unsigned long interval = 2; // interval at which to read the sensors (in ms)

unsigned long previousMillis_bis = 0;   // stores the last time the sensors were read
const unsigned long interval_bis = 2000; // interval at which to read the sensors (in ms)

int ini_manette = 0;

void setup() {

  SONAR.begin(9600);
  GPS.begin(9600);
  Serial.begin(500000);

  pinMode(trig_sonar,OUTPUT);
  pinMode(echo_sonar,INPUT);
  Wire.begin(); // initialize the I2C interface
 
}

// Pour avoir les angles

/*void gyroscope(float* etat)
{
  timePrev = time;                        // the previous time is stored before the actual time read
  time = millis();                        // actual time read
  dtMPU = (time - timePrev) / 1000; //divide by 1000 in order to obtain seconds
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz); 

  gyro_z += (gz-33)/131*dtMPU;
  gyro_y += (gy-30)/131*dtMPU;
  gyro_x += (gx-100)/131*dtMPU;

  az_out = ((az)/16384-1)*9.81*dtMPU;
  ax_out = (ax-2320.0)/16384.0*dtMPU;
  ay_out = (ay-300.0)/16384.0*dtMPU;

  
  etat[0] = ax_out;
  etat[1] = ay_out;
  etat[2] = az_out;
  etat[3] = gyro_x;
  etat[4] = gyro_y;
  etat[5] = gyro_z;

}*/

// ===================== Pour avoir la position ==============================
void Position(float* Pos)
{
  if (GPS.available() > 0)
  {
    // get the byte data from the GPS
    byte gpsData = GPS.read();
    gps.encode(gpsData);
  }
  if (gps.location.isValid()) 
  {
    Pos[0] = gps.location.lat();
    Pos[1] = gps.location.lng();
    Pos[2] = gps.altitude.meters();
  }
}

void loop() {
  float inputs[6] = {0,0,0,0,0,0};
  float Prop[4] = {0,0,0,0};
  float Pos[3] = {0,0,0};
  float etat[6] = {0,0,0,0,0,0};

  Position(Pos);
  //gyroscope(etat);
  

  if (millis() - previousMillis_bis >= interval_bis) 
  {
    previousMillis_bis = millis();
    //Serial.println(prof = dist_calc(3, 4, 20));
    Position(Pos);
    //Serial.println(Pos[0]);
  }

  // ================================== Lecture du joystick ================================
  if (millis() - previousMillis >= interval) 
  {
    previousMillis = millis();
    if (Serial.available() > 0)
    {
      String DATA_entr = Serial.readStringUntil('\n');  //Un json se fini par un \n
      if(ini_manette == 0)
      {
        int i_temp = joystick_lec(DATA_entr, inputs, Prop, joy, 1);
        if(i_temp == 1)
        {
          ini_manette = 1;
          Serial.println("MANETTE_VALIDE");
        }
      }
      else if(ini_manette == 1)
      {
        joystick_lec(DATA_entr, inputs, Prop, joy, 0);
      }
    }
  }
}
