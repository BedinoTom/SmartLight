#include "Wire.h"
#include <Melopero_AMG8833.h>
#define DS1307_I2C_ADDRESS 0x68 // the I2C address of Tiny RTC
#include <SoftwareSerial.h>

#define RX 10
#define TX 11
#define RX_WIRELESS 7
#define TX_WIRELESS 8
#define LED_PIN 4
#define TIME_DETECT_STAY_ON 4

Melopero_AMG8833 sensor;
SoftwareSerial BlueT(RX,TX);
SoftwareSerial Wireless(RX_WIRELESS,TX_WIRELESS);
byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
float matrix_temp[64];
bool is_empty_matrice=true,is_collide=false,led_state=false,last_led_state=true,detect_state=false,last_detect_state=true, standby_collide=false;
int count_doppler=0,timer_doppler=0,timer_collide=0;
String buf;
int valid=0;

void getValueFromKeyMap(String _map, char* key, char*buf);

void setup() {
Wire.begin();
Serial.begin(9600);
BlueT.begin(9600);
Wireless.begin(9600);
//setDateDs1307(); //Set current time;
sensor.initI2C();
Serial.print("Resetting sensor ... ");  
int statusCode = sensor.resetFlagsAndSettings();
Serial.println(sensor.getErrorDescription(statusCode));

Serial.print("Setting FPS ... ");
statusCode = sensor.setFPSMode(FPS_MODE::FPS_10);
Serial.println(sensor.getErrorDescription(statusCode));

for(int i=0;i<8;i++)
{
  for(int j=0;j<8;j++)
  {
    matrix_temp[i + j*8] = 0.0f;
  }
}

attachInterrupt(digitalPinToInterrupt(2), stateChange_doppler, FALLING);
timer_doppler=millis(); 

pinMode(LED_PIN,OUTPUT);
digitalWrite(LED_PIN,HIGH);
}


void loop()
{
//delay(200);
getDateDs1307();//get the time data from tiny RTC

  //Serial.print("Updating thermistor temperature ... ");
  int statusCode = sensor.updateThermistorTemperature();
  //Serial.println(sensor.getErrorDescription(statusCode));

  //Serial.print("Updating pixel matrix ... ");
  statusCode = sensor.updatePixelMatrix();
  //Serial.println(sensor.getErrorDescription(statusCode));

  //Serial.print("Thermistor temp: ");
  //Serial.print(sensor.thermistorTemperature);
  //Serial.println("°C");

  //Serial.println("Temperature Matrix: ");
  float diff=0;
  if(!is_empty_matrice)
  {
    for (int x = 0; x < 8; x++){
      for (int y = 0; y < 8; y++){
        diff = diff + abs(sensor.pixelMatrix[y][x] - matrix_temp[y*8 + x]);
      }
    }
  }

 // Serial.print("Diff Temp : ");
  //Serial.println(diff);

  if(diff > 30)
  {
    is_collide=true;
  }

  for (int x = 0; x < 8; x++){
      for (int y = 0; y < 8; y++){
        matrix_temp[y*8 + x] = sensor.pixelMatrix[y][x];
      }
    }

  if(is_empty_matrice)
  {
    is_empty_matrice=false;
  }

  //Serial.print("Light : ");
  //Serial.println(analogRead(A0));

 if(((second+60*minute)-timer_doppler)>1)
  {
     if(count_doppler>1)  
     {
        is_collide=true;
        count_doppler=0;   //Count zero
    }
    else
    {
        count_doppler=0; 
    }
    timer_doppler=second+60*minute;
  }

  if(is_collide && detect_state && !standby_collide)
  {
    BlueT.println("collide=on;");
    Serial.println("COLLIDE");
    Wireless.println("collide");
    timer_collide=second+60*minute;
    digitalWrite(LED_PIN,LOW);
    is_collide=false;
    standby_collide=true;
  }
  
  if(((second+60*minute) - timer_collide)>TIME_DETECT_STAY_ON && standby_collide && detect_state)
  {
    Serial.println("OFF");
    BlueT.println("collide=off;");
    Wireless.println("collide");
    digitalWrite(LED_PIN,HIGH);
    standby_collide=false;
  }

  BlueT.listen();
  while(BlueT.available())
  {
    buf = BlueT.readString();
     valid++;
  }

  if(valid > 0)
  {
    Serial.println(buf);
    char values[50],arg1[50];
    getValueFromKeyMap(buf,"cmd",values);
    getValueFromKeyMap(buf,"arg1",arg1);
    Serial.println(arg1);
    if(strcmp(values,"light")==0)
    {
      if(strcmp(arg1,"true")==0)
      {
        led_state=true;
      }
      else
      {
        led_state=false;
      }
    }
    else if(strcmp(values,"detect")==0)
    {
      if(strcmp(arg1,"true")==0)
      {
        detect_state=true;
      }
      else
      {
        detect_state=false;
      }
    }
    valid=0;
  }

if(led_state != last_led_state)
{
  if(led_state)
  {
    digitalWrite(LED_PIN,LOW);
    BlueT.println("light=on;");
  }
  else
  {
    digitalWrite(LED_PIN,HIGH);
    BlueT.println("light=off;");
  }

  last_led_state = led_state;
}

if(detect_state != last_detect_state)
{
  if(detect_state)
  {
    BlueT.println("detect=on;");
  }
  else
  {
    Serial.println("ok");
    BlueT.println("detect=off;");
  }

  last_detect_state = detect_state;
}
}

void stateChange_doppler()  //Interrupt function
{  
  //Serial.println("State");
  count_doppler++;  
}


// Convert normal decimal numbers to binary coded decimal
byte decToBcd(byte val)
{
return ( (val/10*16) + (val%10) );
}
// Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val)
{
return ( (val/16*10) + (val%16) );
}
// Function to set the currnt time, change the second&minute&hour to the right time
void setDateDs1307()
{

second =45;
minute = 16;
hour = 10;
dayOfWeek = 3;
dayOfMonth =5;
month =1;
year= 21;
Wire.beginTransmission(DS1307_I2C_ADDRESS);
Wire.write(decToBcd(0));
Wire.write(decToBcd(second)); // 0 to bit 7 starts the clock
Wire.write(decToBcd(minute));
Wire.write(decToBcd(hour)); // If you want 12 hour am/pm you need to set
// bit 6 (also need to change readDateDs1307)
Wire.write(decToBcd(dayOfWeek));
Wire.write(decToBcd(dayOfMonth));
Wire.write(decToBcd(month));
Wire.write(decToBcd(year));
Wire.endTransmission();
}
// Function to gets the date and time from the ds1307 and prints result
void getDateDs1307()
{
// Reset the register pointer
Wire.beginTransmission(DS1307_I2C_ADDRESS);
Wire.write(decToBcd(0));
Wire.endTransmission();
Wire.requestFrom(DS1307_I2C_ADDRESS, 7);
second = bcdToDec(Wire.read() & 0x7f);
minute = bcdToDec(Wire.read());
hour = bcdToDec(Wire.read() & 0x3f); // Need to change this if 12 hour am/pm
dayOfWeek = bcdToDec(Wire.read());
dayOfMonth = bcdToDec(Wire.read());
month = bcdToDec(Wire.read());
year = bcdToDec(Wire.read());
/*Serial.print("Date : ");
Serial.print(hour, DEC);
Serial.print(":");
Serial.print(minute, DEC);
Serial.print(":");
Serial.print(second, DEC);
Serial.print(" ");
Serial.print(month, DEC);
Serial.print("/");
Serial.print(dayOfMonth, DEC);
Serial.print("/");
Serial.print(year,DEC);
Serial.print(" ");
Serial.println();*/
//Serial.print("Day of week:");
}

void getValueFromKeyMap(String _map, char* key, char*buf)
{
  String _str = _map;
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
