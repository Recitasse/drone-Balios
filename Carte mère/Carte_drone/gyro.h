#include <MPU6050_light.h>
#include "function.h"
#include <Arduino.h>
MPU6050 mpu(Wire);

regul Vx_r;
regul Vy_r;

class GYRO_ACCEL
{
private:
  byte status;
  etats drone_etats;
  MPU6050 mpu;
  float V_angleZ;
  float Vx_temp[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  float Vy_temp[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  float vx_m = 0;
  float vy_m = 0;

public:
  GYRO_ACCEL() : mpu(Wire) { }

  void gyro_begin()
  {
    Wire.begin();
    Serial.println("Initialisation MPU6050");
    Serial.println("NE PAS TOUCHER LE DRONE !");
    this->status = mpu.begin();
    while (status != 0) { }
    Serial.println("Gyroscope et accéléromètre prêts !.");
    delay(1000);
    mpu.calcOffsets();
    delay(1000);
    this->V_angleZ = 0;
  }

  void speed_mean()
  {

    // Ajout d'un intégrateur pour avoir la vitesse qui converge vers 0
    // NE s'applique que si la variation détecter est nulle (ou très petite)
    
    for(int i=9; i>0; i--)
    {
      this->Vx_temp[i] = Vx_temp[i-1];
    }
    this->Vx_temp[0] = mpu.getAccX();
    if(abs(mpu.getAccX()) > 0.012)
    {
      this->Vx_temp[0] = mpu.getAccX();
    }
    else
    {
      this->Vx_temp[0] = 0;
    }

    for(int i=9; i>0; i--)
    {
      this->Vy_temp[i] = Vy_temp[i-1];
    }
    if(abs(mpu.getAccY()) > 0.012)
    {
      this->Vy_temp[0] = mpu.getAccY();
    }
    else
    {
      this->Vy_temp[0] = 0;
    }

    this->vx_m = moy(Vx_temp, 3);
    this->vy_m = moy(Vy_temp, 3);
  }

  float moy(float* vec, int n)
  {
    float sum =0;
    for(int i=0; i<n; i++)
    {
      sum += vec[i];
    }
    return sum/n;
  }

  etats gyro_etats(float dt)
  {
    mpu.update();
    speed_mean();
    float acc = sqrt(pow(vx_m,2)+pow(vy_m,2));
    this->drone_etats.vx = vx_m;
    this->drone_etats.vy = vy_m;
    this->drone_etats.AngleX = mpu.getAngleX();
    this->drone_etats.AngleY = mpu.getAngleY();
    this->drone_etats.AngleZ = mpu.getAngleZ();
    this->V_angleZ = mpu.getGyroZ();

    /*if(vx_m == 0 && abs(drone_etats.vx) > 0)
    {
      Vx_r.erreur = -drone_etats.vx;
      Vx_r.integral += Vx_r.erreur;
      Vx_r.erreurm1 = Vx_r.erreur - Vx_r.erreurm1;
      this->drone_etats.vx = (0.2*Vx_r.erreur + 0.*Vx_r.integral + 100*Vx_r.derive);
      Vx_r.erreurm1 = Vx_r.erreur;
    }

    if(vy_m == 0 && abs(drone_etats.vy) > 0)
    {
      Vy_r.erreur = -drone_etats.vy;
      Vy_r.integral += Vy_r.erreur;
      Vy_r.erreurm1 = Vy_r.erreur - Vy_r.erreurm1;
      this->drone_etats.vy = (0.2*Vy_r.erreur + 0.*Vy_r.integral + 100*Vy_r.derive);
      Vy_r.erreurm1 = Vy_r.erreur;
    }*/
    
    return drone_etats;
  }


  void afficher_gyro()
  {
    Serial.println("Vx : "+String(drone_etats.vx)+", Vy : " + String(drone_etats.vy) + ", AngleX : " + String(drone_etats.AngleX) + ", AngleY : " + String(drone_etats.AngleY) + ", AngleZ : "+String(drone_etats.AngleZ));
  }

  void get_data_reg(float* states)
  {
    float com[4] = {drone_etats.vx, drone_etats.vy, V_angleZ, drone_etats.AngleZ};
    for(int i=0; i<4; i++)
    {
      states[i] = com[i];
    }
  }

};
