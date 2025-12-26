#include<Arduino.h>
// --- CONFIGURATION ---
const int TOTAL_ELECTRODES = 32;
const int MEASURE_PIN = A0;      // Analog pin for voltage
const int NUM_SAMPLES = 20;      // How many readings to average per step

// Voltage Divider Calibration (If measuring > 5V)
// Example: If measuring 12V, use R1=10k, R2=4.7k. 
// Divider Ratio = (R1 + R2) / R2
const float R1 = 10000.0; // 10k Ohm
const float R2 = 4700.0;  // 4.7k Ohm
const float DIVIDER_RATIO = (R1 + R2) / R2; 

// --- PIN DEFINITIONS ---
const int signal1_Pins[] = {2, 3, 4, 5, 6};   // Signal 1 (Fixed)
const int signal2_Pins[] = {7, 8, 9, 10, 11}; // Signal 2 (Scanning)

void setup() {
  Serial.begin(9600);
  
  // Set Control Pins to Output
  for(int i=0; i<5; i++){
    pinMode(signal1_Pins[i], OUTPUT);
    pinMode(signal2_Pins[i], OUTPUT);
  }
  
  Serial.println("--- STARTING ELECTRODE SCAN ---");
  Serial.println("Fixed_ID, Moving_ID, Raw_ADC, Voltage_V");
}

void loop() {
  // --- OUTER LOOP: Signal 1 (The Pivot) ---
  for (int i = 0; i < TOTAL_ELECTRODES; i++) {
    
    int fixedVal = i;
    setPins(signal1_Pins, fixedVal); // Set Pivot

    // --- INNER LOOP: Signal 2 (The Scanner) ---
    // Start scanning from the electrode right after the fixed one
    

    // Scan until we wrap around and hit the fixed electrode again
    for (int j = 0; j < TOTAL_ELECTRODES; j++) {
    int movingVal = j;
      
      // 1. SWITCH: Set the Scanning Electrode
      setPins(signal2_Pins, movingVal);
      
      // 2. SETTLE: Wait for relays/switches to stabilize
      delay(50); 
      
      // 3. MEASURE: Read the Analog Pin (with averaging)
      float voltage = readVoltage();
      
      // 4. OUTPUT: Print data in CSV format (easy to copy to Excel)
      Serial.print(fixedVal);
      Serial.print(", ");
      Serial.print(movingVal);
      Serial.print(", ");
      Serial.println(voltage, 4); // Print with 4 decimal places

      // 5. NEXT: Move to the next electrode in the circle
      movingVal = (movingVal + 1) % TOTAL_ELECTRODES;
      
      // Short delay between measurements
      delay(50); 
    }
  }
  
  // End of full cycle - Pause for 5 seconds before restarting
  Serial.println("--- CYCLE COMPLETE ---");
  delay(5000);
}

// --- HELPER: Read and Calculate Voltage ---
float readVoltage() {
  long sum = 0;
  
  // Take multiple samples to smooth out noise
  for(int k=0; k < NUM_SAMPLES; k++) {
    sum += analogRead(MEASURE_PIN);
    delay(2); // Short delay between samples
  }
  
  float averageRaw = sum / (float)NUM_SAMPLES;
  
  // Convert 0-1023 to 0-5V
  float arduinoVoltage = averageRaw * (5.0 / 1023.0);
  
  // Convert 0-5V to Real Boosted Voltage (using Divider Ratio)
  float realVoltage = arduinoVoltage;
  
  return realVoltage;
}

// --- HELPER: Set Digital Pins ---
void setPins(const int pins[], int value) {
  for (int i = 0; i < 5; i++) {
    int bitState = (value >> i) & 1; 
    digitalWrite(pins[i], bitState);
  }
}
