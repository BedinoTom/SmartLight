#include <Wire.h> 

void setup() 
{ 
  Serial.begin(9600);
  pinMode(2,OUTPUT); 
} 

void loop() 
{ 
  Serial.println("UP");
 digitalWrite(2,HIGH);
 delay(2);
 Serial.println("DOWN");
 digitalWrite(2,LOW);
 delay(2);
} 
