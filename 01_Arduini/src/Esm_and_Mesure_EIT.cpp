#include<Arduino.h>
const int TOTAL_ELECTRODES = 32;
const int MEASURE_PIN = A0;     
const int NUM_SAMPLES = 20;    

//------------Only Use when Known Unless Arduino gone a break----------------------
const float R1 = 10000.0; 
const float R2 = 4700.0;  
const float DIVIDER_RATIO = (R1 + R2) / R2; 


const int signal1_Pins[] = {2, 3, 4, 5, 6};   
const int signal2_Pins[] = {7, 8, 9, 10, 11}; 

void setup() {
  Serial.begin(9600);
  for(int i=0; i<5; i++){
    pinMode(signal1_Pins[i], OUTPUT);
    pinMode(signal2_Pins[i], OUTPUT);
  }
  Serial.print("Code Made By Soumasish Chakraborty --2025");
  Serial.println("--- STARTING ELECTRODE SCAN ---");
  Serial.println("Fixed_ID, Moving_ID, Raw_ADC, Voltage_V");
}

void loop() {

  for (int i = 0; i < TOTAL_ELECTRODES; i++) {
    
    int fixedVal = i;
    setPins(signal1_Pins, fixedVal); 

    for (int j = 0; j < TOTAL_ELECTRODES; j++) {
    int movingVal = j;
      
    
      setPins(signal2_Pins, movingVal);
      
     
      delay(50); 

      float voltage = readVoltage();
      Serial.print(fixedVal);
      Serial.print(", ");
      Serial.print(movingVal);
      Serial.print(", ");
      Serial.println(voltage, 4); 
      movingVal = (movingVal + 1) % TOTAL_ELECTRODES;
      
 
      delay(50); 
    }
  }

  Serial.println("--- CYCLE COMPLETE ---");
  delay(5000);
}
float readVoltage() {
  long sum = 0;

  for(int k=0; k < NUM_SAMPLES; k++) {
    sum += analogRead(MEASURE_PIN);
    delay(2); 
  }
  
  float averageRaw = sum / (float)NUM_SAMPLES;

  float arduinoVoltage = averageRaw * (5.0 / 1023.0);

  float realVoltage = arduinoVoltage;
  //RealVoltage Mesurement formula arduino_Voltage substarct potential (Importent)
  return realVoltage;
}


void setPins(const int pins[], int value) {
  for (int i = 0; i < 5; i++) {
    int bitState = (value >> i) & 1; 
    digitalWrite(pins[i], bitState);
  }
}
//Code Made By Soumasish Chakraborty --2025
