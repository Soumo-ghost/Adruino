#include<Arduino.h>
byte pin0=0;
byte pin1=1;
byte pin2=2;
byte pin3=3;
byte pin4=4;

void setup()
{
  pinMode(pin0, OUTPUT);
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
}
// Riyaj incoming
void loop(){
for (int i = 0; i < 32; ++i) {
   
    digitalWrite(pin0, i & 1); 
    digitalWrite(pin1, (i >> 1) & 1);
    digitalWrite(pin2, (i >> 2) & 1);
    digitalWrite(pin3, (i >> 3) & 1); 
	digitalWrite(pin4, (i >> 4) & 1); 
  delay(1000);
}
}
