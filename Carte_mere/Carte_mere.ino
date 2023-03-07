#include <math.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include "function.h"
#include <Wire.h>
#include <MPU6050.h>


int16_t gx, gy, gz;
float gx_error, gy_error, gz_error;
float gz_raw, gy_raw,gx_raw;
float gyro_z,gyro_y,gyro_x;
MPU6050 mpu;

float elapsedTime, time, timePrev;

int echo_sonar = 4; // declare and initialize echo_sonar variable
int trig_sonar = 3; // sonar pin
float dist_mes = 0;
float dist_mes_pre = 0;
float prof;
float* angle;

SoftwareSerial SONAR(echo_sonar, trig_sonar);
SoftwareSerial GPS(6, 7);

TinyGPSPlus gps;

void setup() {

  //SONAR.begin(9600);
  GPS.begin(9600);
  Serial.begin(500000);

  mpu.initialize();
  mpu.setRate(100); // Fréquence en Hertz

  time = millis();                        //Start counting time in milliseconds

  pinMode(trig_sonar,OUTPUT);
  pinMode(echo_sonar,INPUT);
  
}

// Pour avoir les angles

/*void gyroscope(float* angle)
{
    timePrev = time;                        // the previous time is stored before the actual time read
    time = millis();                        // actual time read
    elapsedTime = (time - timePrev) / 1000; //divide by 1000 in order to obtain seconds
    mpu.getRotation(&gx, &gy, &gz);

    gx_raw = (gx/150 - 3)*90/75;            //Conserver les valeurs du paramétrage et correction
    gyro_x = gyro_x  + gx_raw*elapsedTime;

    gy_raw = (gy/150)*90/78;            //Conserver les valeurs du paramétrage et correction
    gyro_y = gyro_y  + gy_raw*elapsedTime;

    gz_raw = (gz/150-1)*90/85;            //Conserver les valeurs du paramétrage et correction
    gyro_z = gyro_z  + gz_raw*elapsedTime;

    angle[0] = gyro_x;
    angle[1] = gyro_y;
    angle[2] = gyro_z;
    delay(200);
}*/

// ===================== Pour avoir la position ==============================
void Position()
{

  while (GPS.available() > 0){
    // get the byte data from the GPS
    byte gpsData = GPS.read();
    gps.encode(gpsData);
  }
  if (gps.location.isValid()) {
    Serial.print("Latitude : ");
    Serial.print(gps.location.lat(), 6);
    Serial.print(" ; Longitude : ");
    Serial.print(gps.location.lng(), 6);
    Serial.print(" ; Altitude : ");
    Serial.print(gps.altitude.meters(), 6);
    Serial.print(" Prof : ");
  }
}
void loop() {
  float inputs[6];
  

  //JSON_SENSOR(dist_calc(3, 4, 20));

  // ================================== Lecture du joystick ================================

  Position();
  prof = dist_calc(3, 4, 20);
  mpu.getRotation(&gx, &gy, &gz);
  Serial.println(gx);
  
/*
  while (Serial.available() > 0)
  {

    String DATA_entr = Serial.readStringUntil('\n');  //Un json se fini par un \n
    //Serial.println(DATA_entr);
    
    joystick_lec(DATA_entr, inputs);

    float Log[6][4] = {
        {0,1,1,0},
        {1,1,0,0},
        {0,1,0,1},
        {1,0,0,1},
        {0,0,1,1},
        {1,0,1,0}
      };
      float Prop[4] = {0,0,0,0};
      float Comm[3] = {signe(inputs[1]), signe(inputs[2]), signe(inputs[0])};

      if(inputs[4] != 1)
      {
        if(Comm[0] == 1)
        {
          for(int i=0; i<4; i++)
          {
            Prop[i] += abs(inputs[1])*Log[3][i];
          }
        }
        else if(Comm[0] == -1)
        {
          for(int i=0; i<4; i++)
          {
            Prop[i] += abs(inputs[1])*Log[0][i];
          }
        }
      
        if(Comm[1] == 1)
        {
          for(int i=0; i<4; i++)
          {
            Prop[i] += abs(inputs[2])*Log[4][i];
          }
        }
        else if(Comm[1] == -1)
        {
          for(int i=0; i<4; i++)
          {
            Prop[i] += abs(inputs[2])*Log[1][i];
          }
      
        }
  
        if(Comm[2] == 1)
        {
          for(int i=0; i<4; i++)
          {
            Prop[i] += abs(inputs[0])*Log[5][i];
          }
        }
        else if(Comm[2] == -1)
        {
          for(int i=0; i<4; i++)
          {
            Prop[i] += abs(inputs[0])*Log[2][i];
          }
      
        }
      
  
      }
   }*/

}
