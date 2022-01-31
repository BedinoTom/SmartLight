#include <SoftwareSerial.h>

#define RX 3
#define TX 2

SoftwareSerial BlueT(RX,TX);

//Moteur
#define A 23
#define B 24
#define C 25
#define AVANT 26
#define ARRIERE 27

const int enable_A=10;
const int in_1_A=7;
const int in_2_A=6;

const int enable_B=9;
const int in_1_B=4;
const int in_2_B=5;

const int enable_C=11;
const int in_1_C=12;
const int in_2_C=13;

void setup() {
 Serial.begin(9600);
pinMode(enable_A,OUTPUT);
pinMode(in_1_A,OUTPUT);
pinMode(in_2_A,OUTPUT);

pinMode(enable_B,OUTPUT);
pinMode(in_1_B,OUTPUT);
pinMode(in_2_B,OUTPUT);

pinMode(enable_C,OUTPUT);
pinMode(in_1_C,OUTPUT);
pinMode(in_2_C,OUTPUT);

forward();
//power_all(255);
}

void loop() {

}


void direction_motor(int n,int s)
{
  if(n==A)
  {
    if(s==AVANT)
    {
      digitalWrite(in_1_A,HIGH);
    digitalWrite(in_2_A,LOW);
    }
    else
    {
      digitalWrite(in_2_A,HIGH);
  digitalWrite(in_1_A,LOW);
    }
  }
  else if(n==C)
  {
    if(s==AVANT)
    {
      digitalWrite(in_1_C,HIGH);
    digitalWrite(in_2_C,LOW);
    }
    else
    {
      digitalWrite(in_2_C,HIGH);
  digitalWrite(in_1_C,LOW);
    }
  }
  else
  {
    if(s==AVANT)
    {
      digitalWrite(in_1_B,HIGH);
    digitalWrite(in_2_B,LOW);
    }
    else
    {
      digitalWrite(in_2_B,HIGH);
  digitalWrite(in_1_B,LOW);
    }
  }
}

void forward()
{
  direction_motor(A,AVANT);
  direction_motor(B,AVANT);
  direction_motor(C,AVANT);
}

void other_forward()
{
  direction_motor(A,ARRIERE);
  direction_motor(B,ARRIERE);
  direction_motor(C,ARRIERE);
}

void power_motor(int n,int pwm)
{
  if(n==A)
  {
    analogWrite(enable_A,pwm);
  }
  else if(n==C)
  {
    analogWrite(enable_C,pwm);
  }
  else
  {
    analogWrite(enable_B,pwm);
  }
}

void power_all(int pwm)
{
  power_motor(A,pwm);
  power_motor(B,pwm);
  power_motor(C,pwm);
}
