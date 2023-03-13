// See SoftwareSerial example 
// https://www.arduino.cc/en/tutorial/SoftwareSerialExample

#include <SoftwareSerial.h>
#define RX 2 //Connect to the TX pin of the HC-12
#define TX 3 //Connect to the RX pin of the HC-12
SoftwareSerial HC12(RX, TX);

void setup() {
  Serial.begin(9600);
  HC12.begin(9600);

}

void loop() { // run over and over
  String com = "SONAR";
  char decomp[com.length()+1];
  com.toCharArray(decomp, sizeof(decomp));

  HC12.write(decomp, sizeof(decomp));

    while (HC12.available()) 
    {
      char buffer[10];
      HC12.readBytesUntil('\n', buffer, 10); 
      float value = atof(buffer); 
      if(value > 0.2 && value < 5.0)
      {
        Serial.println("DONE");
      }
      else
      {
        Serial.println("NON");
      }
    }
    delay(2000);
}
