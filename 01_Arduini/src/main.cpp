#include <Wire.h>
#include <Arduino.h>

const int SLAVE_ADDRESS = 9;
const int LED_PINS[] = {9, 10, 11}; 
const int NUM_STEPS = 5;
const int MASTER_PATTERNS[] = {0, 1, 2, 3, 7};
int currentStep = 0;

void updateMasterLEDs(int patternValue) {
  digitalWrite(LED_PINS[0], (patternValue & 0b001)); 
  digitalWrite(LED_PINS[1], (patternValue & 0b010)); 
  digitalWrite(LED_PINS[2], (patternValue & 0b100)); 
}

void sendCommandToSlave(int step) {
  Wire.beginTransmission(SLAVE_ADDRESS);
  Wire.write(step); 
  Wire.endTransmission();
}

void printPattern(int pattern) {
  Serial.print((pattern & 0b100) ? "1" : "0");
  Serial.print((pattern & 0b010) ? "1" : "0");
  Serial.print((pattern & 0b001) ? "1" : "0");
}

void setup() {
  for (int i = 0; i < 3; i++) {
    pinMode(LED_PINS[i], OUTPUT);
  }
  Wire.begin();
  Serial.begin(9600);
  Serial.println("Master Ready. LEDs: 9, 10, 11");
}

void loop() {
  int masterPattern = MASTER_PATTERNS[currentStep];
  
 
  updateMasterLEDs(masterPattern);

 
  sendCommandToSlave(currentStep);


  Serial.print("Step ");
  Serial.print(currentStep);
  Serial.print(" | Master: ");
  printPattern(masterPattern);
  Serial.print(" | Slave Pattern Index: ");
  Serial.println(currentStep); 

  delay(1000);

  
  currentStep = (currentStep + 1) % NUM_STEPS;
}