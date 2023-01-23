// Includes
#include "include/led.h"
#include "include/output.h"
#include "include/setup.h"

// the setup function runs once when you press reset or power the board
void setup() {
  // Setup outputs
  initSetupOutputs();
  // Setup BLE
  initSetupBle();

  // Wait for serial port to show up before continuing
  Serial.begin(115200);
  while (!Serial) {
    blinkLed();
    delay(100);
  }
  Serial.println("===============");
  Serial.println("= Openshutter =");
  Serial.println("= Ladybug     =");
  Serial.println("= v0.0.1      =");
  Serial.println("===============");
}

// the loop function runs over and over again forever
void loop() {
  breatheLed(2000, 1, 2000);
}
