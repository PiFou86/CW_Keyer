#include <Arduino.h>

#include "Keyer.h"


Keyer *keyer = nullptr;
void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; 
  }
  keyer = new Keyer();
}

void loop() {
  keyer->loop();
}
