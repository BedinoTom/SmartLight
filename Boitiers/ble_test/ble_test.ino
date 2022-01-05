#include <SoftwareSerial.h>

#define RX 10
#define TX 11

SoftwareSerial BlueT(RX,TX);

void setup() {
 Serial.begin(9600);
 delay(500);
 Serial.println("Pret pour commande AT");
 BlueT.begin(9600);
 delay(500);
 Serial.println("BLE OK");
}

void loop() {
  while(BlueT.available())
  {
    Serial.write(char(BlueT.read()));  
  }
  
  while(Serial.available())
  {
    BlueT.write(char(Serial.read()));
  }
}
