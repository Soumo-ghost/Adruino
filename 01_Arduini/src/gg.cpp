#include<Arduino.h>
const int analogPin = A0;

void setup() {
  Serial.begin(9600);

  // STEP A: Set the reference to EXTERNAL (the 3.3V we wired to AREF)
  // This must happen before any analogRead() calls!
  analogReference(EXTERNAL); 

  // STEP B: Perform a "dummy read" to let the ADC stabilize
  analogRead(analogPin);
  delay(10);
}

void loop() {
  // Take 64 samples for high precision (Oversampling)
  unsigned long total = 0;
  for(int i = 0; i < 64; i++) {
    total += analogRead(analogPin);
  }
  
  float averageRaw = total / 64.0;
  
  // Math: (Average Raw Value * Reference Voltage) / ADC Resolution
  float voltage = (averageRaw * 3.3) / 1023.0;

  Serial.print("Precise Voltage: ");
  Serial.println(voltage, 4); 
  delay(200);
}