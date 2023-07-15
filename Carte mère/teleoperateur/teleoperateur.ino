#include <Arduino.h>
#include <math.h>
#include "function.h"
#include "hc12_m.h"
#define RX 3 //Connect to the TX pin of the HC-12
#define TX 2 //Connect to the RX pin of the HC-12
#define RGB_R 6
#define RGB_G 5
#define RGB_B 11
#define ZARDOZ 12
int proximite;
bool data_r;

HC12_m hc(RX, TX);

void setup() {
  Serial.begin(115200);
  hc.begin_hc12(19200);

  pinMode(RGB_R, OUTPUT);
  pinMode(RGB_B, OUTPUT);
  pinMode(RGB_G, OUTPUT);
  pinMode(ZARDOZ, OUTPUT);
}

void loop() {
  
  hc.pc2c1();
  hc.communication();
  proximite = hc.prox();
  data_r = hc.reception();

  if(proximite >= 5)
  {
    analogWrite(RGB_R, 0);
    analogWrite(RGB_B, 0);
    analogWrite(RGB_G, 255);
  }  
  else if(proximite < 5 && proximite >= 2)
  {
    analogWrite(RGB_R, 255);
    analogWrite(RGB_B, 128);
    analogWrite(RGB_G, 25);
  }  
  else if(proximite < 2 && proximite > 1)
  {
    analogWrite(RGB_R, 255);
    analogWrite(RGB_B, 127);
    analogWrite(RGB_G, 0);
  }  
  else if(proximite <= 1)
  {
    analogWrite(RGB_R, 255);
    analogWrite(RGB_B, 0);
    analogWrite(RGB_G, 0);
  }  

  if(data_r)
  {
    digitalWrite(ZARDOZ, HIGH);
    digitalWrite(ZARDOZ, LOW);
  }
  
  
}
