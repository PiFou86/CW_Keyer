#include <Arduino.h>

#include "Keyer.h"


Keyer *keyer = nullptr;
void setup() {
  keyer = new Keyer();


  pinMode(11, OUTPUT);


  //pinMode(2, INPUT_PULLUP)

  tone(11, 750, 100000); // Example tone to test the setup
  //delay(100000); // Wait for a second to hear the tone
}

void loop() {
  keyer->loop();
}
