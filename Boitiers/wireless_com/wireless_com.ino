#include <SoftwareSerial.h>

//SoftwareSerial HC12(2, 3); // HC-12 TX Pin, HC-12 RX Pin

void setup() {
  Serial.begin(9600);            
  Serial1.begin(9600);   
  pinMode(2,OUTPUT);        
}

void loop() {
  while (Serial1.available()) {
    Serial.write(Serial1.read());
          digitalWrite(2,HIGH);
  }
  while (Serial.available()) { 
    char c = Serial.read();
    Serial1.write(c);
  }
}
