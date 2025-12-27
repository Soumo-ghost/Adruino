#include <Wire.h>
#include <Arduino.h>
const int SLAVE_ADDRESS = 9;
const int LED_PINS[] = {9, 10, 11}; 


const int SLAVE_PATTERNS[] = {0, 1, 2, 3, 0};


void receiveEvent(int byteCount) {
  if (Wire.available()) {
    int step = Wire.read(); 

    if (step >= 0 && step < sizeof(SLAVE_PATTERNS) / sizeof(SLAVE_PATTERNS[0])) {
      int patternValue = SLAVE_PATTERNS[step];
      
     
      digitalWrite(LED_PINS[0], (patternValue & 0b001)); 
      digitalWrite(LED_PINS[1], (patternValue & 0b010)); 
      digitalWrite(LED_PINS[2], (patternValue & 0b100));
    }
  }
}

void setup() {
  for (int i = 0; i < 3; i++) {
    pinMode(LED_PINS[i], OUTPUT);
    digitalWrite(LED_PINS[i], LOW); 
  }
  
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
  
}

void loop() {
  
}
//Code Made By Soumasish Chakraborty --2025