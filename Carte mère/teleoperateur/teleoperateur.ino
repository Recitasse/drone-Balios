#include "function.h"
#include "hc12_m.h"
#define RX 2 //Connect to the TX pin of the HC-12
#define TX 3 //Connect to the RX pin of the HC-12
#define RED_PIN 4;
#define GREEN_PIN 7;
#define YELLOW_PIN 8;
#define BLUE_PIN 12;

HC12_m hc(RX, TX, 5);
COLOR couleur(RED_PIN, GREEN_PIN, YELLOW_PIN, BLUE_PIN);

void setup() {
  Serial.begin(115200);
  hc.begin_hc12(19200);
  couleur.COLOR_INIT();
}

void loop() {
  hc.pc2c1();
  delay(10);

  hc.c12c2();
  couleur.radio_data(hc.c22c1());
  hc.c12pc();

}
