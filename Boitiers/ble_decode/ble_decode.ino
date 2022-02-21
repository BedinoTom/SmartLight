#include <SoftwareSerial.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RX 10
#define TX 11

void getValueFromKeyMap(char *_map, char* key, char*buf);

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

  if(valid == 2)
  {
    char values[50],arg1[50];
    getValueFromKeyMap(buf,"cmd",values);
    getValueFromKeyMap(buf,"arg1",arg1);
    Serial.println(arg1);
    if(strcmp(values,"light")==0)
    {
      if(strcmp(arg1,"true")==0)
      {
        BlueT.println("light=on;");
      }
      else
      {
        BlueT.println("light=off;");
      }
    }
    sprintf(buf,"");
    valid=0;
    i=0;
  }
  
  while(Serial.available())
  {
    BlueT.write(char(Serial.read()));
  }
}

void getValueFromKeyMap(char *_map, char* key, char*buf)
{
  String _str = String(_map);
  String m_key = String(key);
  String temp="";
  int offset_search=0, offset_find=0;
  while((offset_find=_str.indexOf(";",offset_search)) != -1){
        temp=_str.substring(offset_search,offset_find);
        int offset_equal=temp.indexOf("=");
        String _key=temp.substring(0,offset_equal);
        String _value=temp.substring(offset_equal+1);
        if(_key==m_key)
        {
          //return _value.c_str();
          memcpy(buf,_value.c_str(),_value.length());
          buf[_value.length()]='\0';
         return;
        }

        offset_search=offset_find+1;
        if(offset_search>=_str.length())
        {
          break;
        }
  }
  memcpy(buf,'\0',1);
}
