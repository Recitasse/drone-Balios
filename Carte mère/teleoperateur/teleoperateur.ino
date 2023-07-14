#include <Arduino.h>
#include <math.h>
#include "function.h"
#include "hc12_m.h"
#define RX 3 //Connect to the TX pin of the HC-12
#define TX 2 //Connect to the RX pin of the HC-12
#define RGB_R 6
#define RGB_G 5
#define RGB_B 11
#define BLUE_PIN 12

HC12_m hc(RX, TX);

void setup() {
  Serial.begin(115200);
  hc.begin_hc12(19200);
}

void loop() {
  
  hc.pc2c1();
  hc.communication();
  
}
