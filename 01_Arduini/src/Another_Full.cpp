#include<Arduino.h>
// --- CONFIGURATION ---
const int TOTAL_ELECTRODES = 32;
const int MEASURE_PIN = A0;      // Analog pin for voltage
const int NUM_SAMPLES = 20;      // How many readings to average per step

// Voltage Divider: Disabled for 5V usage (Ratio = 1.0)
const float DIVIDER_RATIO = 1.0; 

// --- PIN DEFINITIONS ---
const int signal1_Pins[] = {2, 3, 4, 5, 6};   // Signal 1 (Fixed / Source)
const int signal2_Pins[] = {7, 8, 9, 10, 11}; // Signal 2 (Scanning / Sink)

void setup() {
  Serial.begin(9600);
  
  // Set Control Pins to Output
  for(int i=0; i<5; i++){
    pinMode(signal1_Pins[i], OUTPUT);
    pinMode(signal2_Pins[i], OUTPUT);
  }
  
  Serial.println("--- STARTING ELECTRODE SCAN ---");
  Serial.println("Fixed_ID, Moving_ID, Voltage_V");
}

void loop() {
  // --- OUTER LOOP: Signal 1 (The Pivot) ---
  for (int i = 0; i < TOTAL_ELECTRODES; i++) {
    
    int fixedVal = i;
    setPins(signal1_Pins, fixedVal); // Set Pivot

    // --- INNER LOOP: Signal 2 (The Scanner) ---
    // Start j at 0 to INCLUDE self-measurement (fixedVal == movingVal)
    for (int j = 0; j < TOTAL_ELECTRODES; j++) {
      
      // Calculate movingVal relative to fixedVal
      // j=0 -> Self measurement
      // j=1 -> Next neighbor, etc.
      int movingVal = (fixedVal + j) % TOTAL_ELECTRODES;
      
      // 1. SWITCH: Set the Scanning Electrode
      setPins(signal2_Pins, movingVal);
      
      // 2. SETTLE: Wait for relays/switches to stabilize
      delay(50); 
      
      // 3. MEASURE: Read the Analog Pin
      float voltage = readVoltage();
      
      // 4. OUTPUT: CSV Format
      Serial.print(fixedVal);
      Serial.print(", ");
      Serial.print(movingVal);
      Serial.print(", ");
      Serial.println(voltage, 4); 

      delay(20); 
    }
  }
  
  Serial.println("--- CYCLE COMPLETE ---");
  delay(5000);
}

// --- HELPER: Read and Calculate Voltage ---
float readVoltage() {
  long sum = 0;
  
  for(int k=0; k < NUM_SAMPLES; k++) {
    sum += analogRead(MEASURE_PIN);
    delay(2);
  }
  
  float averageRaw = sum / (float)NUM_SAMPLES;
  
  // Convert 0-1023 to 0-5V
  float arduinoVoltage = averageRaw * (5.0 / 1023.0);
  
  // No divider math needed for 5V system (Ratio is 1.0)
  return arduinoVoltage;
}

// --- HELPER: Set Digital Pins ---
void setPins(const int pins[], int value) {
  for (int i = 0; i < 5; i++) {
    int bitState = (value >> i) & 1; 
    digitalWrite(pins[i], bitState);
  }
}