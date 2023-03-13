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
  String com = "communicationA";
  char decomp[com.length()+1];
  com.toCharArray(decomp, sizeof(decomp));

  HC12.write(decomp, sizeof(decomp));
  
  if (HC12.available()) 
  {
    String receivedString = "";
    while (HC12.available()) 
    {
      char recep = HC12.read();
      receivedString +=recep;
    }
    if(receivedString == "communicationB")
    {
       Serial.println(1);
    }
    else
    {
      Serial.println(0);
    }
  }
  delay(2000);
}
