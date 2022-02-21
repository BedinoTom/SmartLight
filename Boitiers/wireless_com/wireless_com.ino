#include <SoftwareSerial.h>

SoftwareSerial HC12_1(3, 2); // HC-12 TX Pin, HC-12 RX Pin
SoftwareSerial HC12_2(5, 4); // HC-12 TX Pin, HC-12 RX Pin

void setup() {
  Serial.begin(9600);            
  HC12_1.begin(9600);
  HC12_2.begin(9600);         
}

void loop() {
  while (HC12_2.available()) {
    Serial.write(HC12_2.read());
  }
  while (Serial.available()) { 
    HC12_1.write(Serial.read());
  }
}
