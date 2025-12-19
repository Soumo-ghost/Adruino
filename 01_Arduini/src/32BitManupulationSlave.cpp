#include <Wire.h>
#include<Arduino.h>
// Define 5-bit Pin Arrays for Local Signals (3 and 4)
// Note: We reuse pins 2-11 on the second board
const int signal3_Pins[] = {2, 3, 4, 5, 6};   // LSB to MSB
const int signal4_Pins[] = {7, 8, 9, 10, 11}; 

const int MY_ADDR = 9; // Must match Master's target

void setup() {
  Wire.begin(MY_ADDR); // Join I2C bus as Slave #9
  Wire.onReceive(receiveEvent); // Register event handler
  
  // Set pins to output
  for(int i=0; i<5; i++){
    pinMode(signal3_Pins[i], OUTPUT);
    pinMode(signal4_Pins[i], OUTPUT);
  }
}

void loop() {
  // Empty loop! Slave reacts purely to interrupts from Master.
  delay(1000);
}

// This function runs automatically when Master sends data
void receiveEvent(int howMany) {
  if (howMany >= 2) {
    int val3 = Wire.read(); // Receive Signal 3
    int val4 = Wire.read(); // Receive Signal 4
    
    // Update Pins immediately
    setPins(signal3_Pins, val3);
    setPins(signal4_Pins, val4);
  }
}

// Helper function to write binary
void setPins(const int pins[], int value) {
  for (int i = 0; i < 5; i++) {
    int bitState = (value >> i) & 1; 
    digitalWrite(pins[i], bitState);
  }
}