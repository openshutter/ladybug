// Includes
#include "include/led.h"
#include "include/setup.h"
#include "include/output.h"

// the setup function runs once when you press reset or power the board
void setup() {
  // Setup outputs
  initSetupOutputs();
  // Setup BLE
  initSetupBle();

  // Wait for serial port to show up before continuing
  Serial.begin(115200);
  while ( !Serial ) {
    blinkLed(200, 2);
    delay(400);
  }
  Serial.println("===============");
  Serial.println("= Openshutter =");
  Serial.println("= Ladybug     =");
  Serial.println("= v0.0.1      =");
  Serial.println("===============");
}

// the loop function runs over and over again forever
void loop() {
  // do a normal trigger
  triggerOutput();
  delay(5000);
}
