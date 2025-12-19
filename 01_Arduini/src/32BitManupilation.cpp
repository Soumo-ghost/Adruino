#include<Arduino.h>
#include <Wire.h>

// Pins 2-6 for Bit 0-4
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
  // --- OUTER LOOP (Signal 1 & 2) ---
  // We go from 0 to 31.
  for (int i = 0; i < TOTAL_ELECTRODES; i++) {
    
    int val1 = i;
    
    // CIRCULAR LOGIC: If val1 is 31, val2 wraps to 0
    int val2 = (i + 1) % TOTAL_ELECTRODES; 

    // Update Master's pins
    setPins(signal1_Pins, val1);
    setPins(signal2_Pins, val2);

    Serial.print("Master (1&2): "); 
    Serial.print(val1); Serial.print("-"); Serial.println(val2);

    // --- INNER LOOP (Signal 3 & 4) ---
    // Start scanning immediately after val2
    int startIdx = (val2 + 1) % TOTAL_ELECTRODES;
    
    // We use a temporary iterator 'k' to generate the circular scan
    // We stop when the NEXT signal 4 would overlap with signal 1
    
    int val3 = startIdx;
    int val4 = (val3 + 1) % TOTAL_ELECTRODES;

    // Run the loop as long as Signal 4 hasn't caught up to Signal 1
    while (val4 != val1) {
      
      // Send to Slave
      transmitToSlave(val3, val4);
      
      // Move to next pair using CIRCULAR logic
      val3 = (val3 + 1) % TOTAL_ELECTRODES;
      val4 = (val3 + 1) % TOTAL_ELECTRODES;
      
      delay(100); // Speed of switching
    }
  }
}

// --- Helper Functions ---

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