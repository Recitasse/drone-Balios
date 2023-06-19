#include <MPU6050_light.h>
#include "function.h"
#include <Arduino.h>
MPU6050 mpu(Wire);

class GYRO_ACCEL
{
private:
  byte status;
  etats drone_etats;
  MPU6050 mpu;

public:
  GYRO_ACCEL() : mpu(Wire) { }

  void gyro_begin()
  {
    Wire.begin();
    this->status = mpu.begin();
    while (status != 0) { }
    delay(1000);
    mpu.calcOffsets();
    delay(1000);
  }

  etats gyro_etats(float dt)
  {
    mpu.update();
    this->drone_etats.vx = mpu.getAccX() * dt;
    this->drone_etats.vy = mpu.getAccY() * dt;
    this->drone_etats.AngleX = mpu.getAngleX();
    this->drone_etats.AngleY = mpu.getAngleY();
    this->drone_etats.AngleZ = mpu.getAngleZ();
    return drone_etats;
  }

  etats gyro_filtre(capteur& vx, capteur& vy, capteur& gx, capteur& gy, capteur& gz, float dt)
  {
    gyro_etats(dt);
    capteur capteurs[5] = {vx, vy, gx, gy, gz};
    float wc[5] = {0.1, 0.1, 0.1, 0.1, 0.1}; 
    for(int i=0; i<5; i++)
    {
      capteurs[i].sy = (dt * (capteurs[i].sx + capteurs[i].sx_old) - capteurs[i].sy_old * (dt - 2 * wc[i])) / (dt + 2 * wc[i]);
      capteurs[i].sx_old = capteurs[i].sx;
      capteurs[i].sy_old = capteurs[i].sy;
    }
    for(int i=0; i<5; i++)
    {
      this->drone_etats.vx += capteurs[0].sy;
      this->drone_etats.vy += capteurs[1].sy;
      this->drone_etats.AngleX = capteurs[2].sy;
      this->drone_etats.AngleY = capteurs[3].sy;
      this->drone_etats.AngleZ = capteurs[4].sy;
    }
    return drone_etats;
  }

  void afficher_gyro()
  {
    Serial.println("Vx : "+String(drone_etats.vx)+", Vy : " + String(drone_etats.vy) + ", AngleX : " + String(drone_etats.AngleX) + ", AngleY : " + String(drone_etats.AngleY) + ", AngleZ : "+String(drone_etats.AngleZ));
  }

};
