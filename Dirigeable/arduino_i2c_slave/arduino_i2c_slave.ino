void setup() 
{ 
  Serial.begin(9600);
  pinMode(2,OUTPUT);
  pinMode(3,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(3), receive, CHANGE);
} 

void loop() 
{ 
 digitalWrite(2,HIGH);
 delay(2);
 digitalWrite(2,LOW);
 delay(2);
} 

void receive()
{
  Serial.println("Interrupt");
}

