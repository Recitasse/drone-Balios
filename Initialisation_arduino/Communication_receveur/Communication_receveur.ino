// See SoftwareSerial example 
// https://www.arduino.cc/en/tutorial/SoftwareSerialExample
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#define RX 2 //Connect to the TX pin of the HC-12
#define TX 3 //Connect to the RX pin of the HC-12
#define RX_GPS 6
#define TX_GPS 7
#define ECHO_SONAR 5 // Pin echo du sonar
#define TRIG_SONAR 4 // Pin trigger du sonar 

SoftwareSerial HC12(RX, TX);
SoftwareSerial SONAR(ECHO_SONAR, TRIG_SONAR);

SoftwareSerial GPS(RX_GPS, TX_GPS);
TinyGPSPlus gps;

float prof;

void setup() {
  Serial.begin(9600);
  HC12.begin(9600);
  GPS.begin(9600);
  pinMode(TRIG_SONAR,OUTPUT);
  pinMode(ECHO_SONAR,INPUT);
}

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
  else
  {
    Pos[0] = 0.00;
    Pos[1] = 0.00;
    Pos[2] = 0.00;
  }
}

float dist_calc(int trig, int echo, float temp){
  float duration,distance;

  float v = 331.1 +(0.606 * temp);
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  
  duration = pulseIn(echo,HIGH); 
  distance = (v*(duration/2.0))/1000000.0; 
  
  if(distance > 5 || distance <0.2)
  {
    return 0;
  }
  else
  {
    return distance;
  }
}

void loop() { // run over and over
  float Pos[3] = {0,0,0};
  
  if (HC12.available()) {
    String receivedString = "";
    while (HC12.available()) {
      char recep = HC12.read();
      receivedString +=recep;
    }
    // Pour tester la communication
    if(receivedString == "communicationA")
    {
      String com = "communicationB";
      char decomp[com.length()+1];
      com.toCharArray(decomp, sizeof(decomp));

      HC12.write(decomp, sizeof(decomp));
    }
    // Pour tester le sonar
    else if(receivedString == "SONAR")
    {
      prof = dist_calc(TRIG_SONAR, ECHO_SONAR, 20);
      char buffer[20];
      dtostrf(prof, 3, 2, buffer); // format float value as string with 2 decimal places
      HC12.write(buffer); // send string over HC-12 module
      Serial.println(prof);
    }
    // Pour tester le gps
    else if(receivedString == "GPS")
    {
      Serial.println("oui");
    }
    else
    {
      Serial.println("non");
    }
  }
  delay(2000);
}
