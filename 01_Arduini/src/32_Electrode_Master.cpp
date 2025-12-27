#include<Arduino.h>
#include <Wire.h>

const int signal1_Pins[] = {2, 3, 4, 5, 6};  
const int signal2_Pins[] = {7, 8, 9, 10, 11}; 

const int SLAVE_ADDR = 9; 
const int TOTAL_ELECTRODES = 32;

void setup() {
  Wire.begin(); 
  Serial.begin(9600);

  for(int i=0; i<5; i++){
    pinMode(signal1_Pins[i], OUTPUT);
    pinMode(signal2_Pins[i], OUTPUT);
  }
}

void loop() {
  for (int i = 0; i < TOTAL_ELECTRODES; i++) {
    
    int val1 = i;
    int val2 = (i + 1) % TOTAL_ELECTRODES; 
    setPins(signal1_Pins, val1);
    setPins(signal2_Pins, val2);
    Serial.print("Code Made By Soumasish Chakraborty --2025");
    Serial.print("Master (1&2): "); 
    Serial.print(val1); Serial.print("-"); Serial.println(val2);
    int startIdx = (val2 + 1) % TOTAL_ELECTRODES;
    int val3 = startIdx;
    int val4 = (val3 + 1) % TOTAL_ELECTRODES;
    while (val4 != val1) {
      transmitToSlave(val3, val4);
      val3 = (val3 + 1) % TOTAL_ELECTRODES;
      val4 = (val3 + 1) % TOTAL_ELECTRODES;
      //Code Made By Soumasish Chakraborty --2025
      delay(100); 
    }
  }
}

void setPins(const int pins[], int value) {
  for (int i = 0; i < 5; i++) {
    int bitState = (value >> i) & 1; 
    digitalWrite(pins[i], bitState);
  }
}

void transmitToSlave(int v3, int v4) {
  Wire.beginTransmission(SLAVE_ADDR);
  Wire.write(v3); 
  Wire.write(v4); 
  Wire.endTransmission();
}
//Code Made By Soumasish Chakraborty --2025