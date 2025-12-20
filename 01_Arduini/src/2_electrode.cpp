#include<Arduino.h>
// --- PIN DEFINITIONS ---
// Signal 1 (The Fixed "Pivot") - Pins 2-6
const int signal1_Pins[] = {2, 3, 4, 5, 6};  

// Signal 2 (The Moving "Scanner") - Pins 7-11
const int signal2_Pins[] = {7, 8, 9, 10, 11}; 

const int TOTAL_ELECTRODES = 32;

void setup() {
  Serial.begin(9600); // Open Serial Monitor to see the sequence

  // Set all 10 pins to Output
  for(int i=0; i<5; i++){
    pinMode(signal1_Pins[i], OUTPUT);
    pinMode(signal2_Pins[i], OUTPUT);
  }
}

void loop() {
  // --- OUTER LOOP (Signal 1: The Fixed Pivot) ---
  // This loop sets Signal 1 and holds it there
  for (int i = 0; i < TOTAL_ELECTRODES; i++) {
    
    int fixedVal = i;
    
    // Write Signal 1 (This stays constant for the duration of the inner loop)
    setPins(signal1_Pins, fixedVal);

    Serial.print("--- NEW PIVOT: "); Serial.print(fixedVal); Serial.println(" ---");

    // --- INNER LOOP (Signal 2: The Scanner) ---
    // Start Signal 2 at the position immediately following Signal 1
    // We use circular math: (i + 1) % 32
    int movingVal = (fixedVal + 1) % TOTAL_ELECTRODES;

    // Keep moving Signal 2 until it wraps all the way around and hits Signal 1 again
    while (movingVal != fixedVal) {
      
      // Write Signal 2
      setPins(signal2_Pins, movingVal);

      // Debug output
      Serial.print("S1 (Fixed): "); Serial.print(fixedVal);
      Serial.print(" | S2 (Moving): "); Serial.println(movingVal);

      // Delay for measurement/switching
      delay(1000); 

      // Increment Signal 2 and wrap around 31->0 if needed
      movingVal = (movingVal + 1) % TOTAL_ELECTRODES;
    }
    
    // Optional: Small delay before Signal 1 moves to the next pivot
    delay(500);
  }
}

// --- HELPER FUNCTION: Decimal to 5-Bit Binary ---
void setPins(const int pins[], int value) {
  for (int i = 0; i < 5; i++) {
    int bitState = (value >> i) & 1; 
    digitalWrite(pins[i], bitState);
  }
}