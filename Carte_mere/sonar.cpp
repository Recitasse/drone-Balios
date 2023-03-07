#include <math.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

float dist_calc(int trig, int echo, float temp){
  float duration,distance;
  // trigger 40kHz pulse for ranging
  float v = 331.1 +(0.606 * temp);
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  // convert from duration for pulse to reach detector (microseconds) to range (in cm)
  duration = pulseIn(echo,HIGH); // duration for pulse to reach detector (in microseconds)
  distance = (v*(duration/2.0))/1000000.0; // 100.0*(speed of sound*duration/2)/microsec conversion
  
  if(distance >= 6.83 || distance ==0 || distance <=0.2)
  {
    return;
  }
  else
  {
    return distance;
  }
}
