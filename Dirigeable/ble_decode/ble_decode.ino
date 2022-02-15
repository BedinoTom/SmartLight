#include <SoftwareSerial.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

char buf[500];
int i=0,valid=0;

void loop() {
  while(BlueT.available())
  {
    if(i>=499)
     {
        break;
     }
     char c = char(BlueT.read());
     if(c == ';')
     {
      valid++;
     }
     //Serial.write(c);
     buf[i] = c;
     i++;
  }

  if(valid == 1)
  {
    buf[i] = '\0';
    valid=0;
    i=0;

    if(strcmp(buf,"dir=brake;") == 0)
    {
      
    }
    else if(strcmp(buf,"dir=up;") == 0)
    {
      
    }
    else if(strcmp(buf,"dir=down;") == 0)
    {
      
    }
    else if(strcmp(buf,"dir=left;") == 0)
    {
      
    }
    else if(strcmp(buf,"dir=right;") == 0)
    {
      
    }
    else if(strcmp(buf,"dir=climb;") == 0)
    {
      
    }

   sprintf(buf,"");
  }
  
  while(Serial.available())
  {
    BlueT.write(char(Serial.read()));
  }
}
