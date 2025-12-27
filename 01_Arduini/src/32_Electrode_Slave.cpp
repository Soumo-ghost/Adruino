#include <Wire.h>
#include<Arduino.h>
const int signal3_Pins[] = {2, 3, 4, 5, 6};  
const int signal4_Pins[] = {7, 8, 9, 10, 11}; 

const int MY_ADDR = 9; 

void setup() {
  Wire.begin(MY_ADDR); 
  Wire.onReceive(receiveEvent); 
  
  for(int i=0; i<5; i++){
    pinMode(signal3_Pins[i], OUTPUT);
    pinMode(signal4_Pins[i], OUTPUT);
  }
}

void loop() {
  delay(1000);
}
void receiveEvent(int howMany) {
  if (howMany >= 2) {
    int val3 = Wire.read(); 
    int val4 = Wire.read(); 
    
    setPins(signal3_Pins, val3);
    setPins(signal4_Pins, val4);
  }
}

void setPins(const int pins[], int value) {
  for (int i = 0; i < 5; i++) {
    int bitState = (value >> i) & 1; 
    digitalWrite(pins[i], bitState);
  }
}
//Code Made By Soumasish Chakraborty --2025