#include <vector>


int count=0;
int timer=0;

void setup() {

  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2), stateChange, FALLING);
  timer=millis(); 
}

void loop() {
  if((millis()-timer)>100)
  {
    process();
    timer=millis();
  }
}

void stateChange()  //Interrupt function
{  
  Serial.println("State");
  count++;  
}

void process()   //Timer handler
{
  if(count>1)  
//1000ms interrupt number greater than 1 is considered detected a moving object //(this value can be adjusted according to the actual situation, equivalent to //adjust the detection threshold of the speed of a moving object)
       {
                   Serial.println("Detect");
                   count=0;   //Count zero
       }
        else
        {
            count=0; 
        }
//In 1000ms, interrupts does not reach set threshold value is considered not detect //moving objects, interrupt the count number is cleared to zero.  
} 
