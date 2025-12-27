#include<Arduino.h>
const int analogPin = A0;
//It Check Analog Value But Has Some Problem Update Leter
void setup() {
  Serial.begin(9600);
  analogReference(EXTERNAL); 
  analogRead(analogPin);
  delay(10);
}

void loop() {
  unsigned long total = 0;
  for(int i = 0; i < 64; i++) {
    total += analogRead(analogPin);
  }
  
  float averageRaw = total / 64.0;
  
  float voltage = (averageRaw * 3.3) / 1023.0;

  Serial.print("Precise Voltage: ");
  Serial.println(voltage, 4); 
  delay(200);
}
//Code Made By Soumasish Chakraborty --2025