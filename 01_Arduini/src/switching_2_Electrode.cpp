#include<Arduino.h>
const int signal1_Pins[] = {2, 3, 4, 5, 6};  
const int signal2_Pins[] = {7, 8, 9, 10, 11}; 

const int TOTAL_ELECTRODES = 32;

void setup() {
  Serial.begin(9600);

  for(int i=0; i<5; i++){
    pinMode(signal1_Pins[i], OUTPUT);
    pinMode(signal2_Pins[i], OUTPUT);
  }
}

void loop() {
  for (int i = 0; i < TOTAL_ELECTRODES; i++) {
    
    int fixedVal = i;
    setPins(signal1_Pins, fixedVal);
    Serial.print("Code Made By Soumasish Chakraborty --2025");
    Serial.print("--- NEW PIVOT: "); Serial.print(fixedVal); Serial.println(" ---");
    int movingVal = (fixedVal + 1) % TOTAL_ELECTRODES;
    while (movingVal != fixedVal) {
      setPins(signal2_Pins, movingVal);

  
      Serial.print("S1 (Fixed): "); Serial.print(fixedVal);
      Serial.print(" | S2 (Moving): "); Serial.println(movingVal);

      delay(1000); 
      movingVal = (movingVal + 1) % TOTAL_ELECTRODES;
    }

    delay(500);
  }
}

void setPins(const int pins[], int value) {
  for (int i = 0; i < 5; i++) {
    int bitState = (value >> i) & 1; 
    digitalWrite(pins[i], bitState);
  }
}
//Code Made By Soumasish Chakraborty --2025