#include "Wire.h"
#include <Melopero_AMG8833.h>
#define DS1307_I2C_ADDRESS 0x68 // the I2C address of Tiny RTC
#include <SoftwareSerial.h>

#define RX 10
#define TX 11

Melopero_AMG8833 sensor;
SoftwareSerial BlueT(RX,TX);
byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
float matrix_temp[64];
bool is_empty_matrice=true;

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
Serial.println();
//Serial.print("Day of week:");
}
void setup() {
Wire.begin();
Serial.begin(9600);
BlueT.begin(9600);
setDateDs1307(); //Set current time;
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
}


void loop()
{
delay(500);
//getDateDs1307();//get the time data from tiny RTC

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

  Serial.println(diff);

  if(diff > 30)
  {
    BlueT.println("person*a");
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
  
}
