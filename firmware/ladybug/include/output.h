#ifndef OUTPUT_H_
#define OUTPUT_H_

#include "led.h"

// Trigger Pins
#define TRG0_RING D0
#define TRG0_TIP  D1

/**
 * Triggers outputs for "triggerDuration" + 100ms.
 * The "half-press" trigger will be closed on its own for minimum 50ms
 * before "full-press" trigger is closed.
 *
 * If "fast" is true, all led blinks and delays will be skipped
 *
 * @param triggerDuration ms to hold "full-press" trigger closed
 * @param preshootDuration ms to hold "half-press" trigger closed (useful for slow autofocus,
 * exposure, etc)
 * @param fast skip extra led blinks and other delays for minimal latency
 *
 */
void triggerOutput(int triggerDuration = 500, int preshootDuration = 0, bool fast = false) {
  // Trigger Pins
  // #define TRG0_RING   D0
  // #define TRG0_TIP    D1

  // pull trigger 0 ring low
  if (Serial) {
    Serial.println("SET TRG0_RING (D0) OUTPUT LOW");
  }
  if (!fast) {
    blinkLed(100, 4);
  }
  if (!fast) {
    blinkLed(400);
  }
  pinMode(TRG0_RING, OUTPUT);
  digitalWrite(TRG0_RING, LOW);

  // We can take advantage of the "time" paramater to blinkLed()
  // to wait preshootDuration before continuing without inducing any real latency
  blinkLed(preshootDuration);

  // pull trigger 0 tip low
  if (Serial) {
    Serial.println("SET TRG0_TIP (D1) OUTPUT LOW");
  }
  pinMode(TRG0_TIP, OUTPUT);
  digitalWrite(TRG0_TIP, LOW);
  if (!fast) {
    blinkLed(50, 2, 50);
    blinkLed((triggerDuration - 200));
  } else {
    blinkLed(triggerDuration);
  }

  // release both
  if (Serial) {
    Serial.println("SET TRG0_RING (D0) INPUT FLOAT");
  }
  pinMode(TRG0_RING, INPUT);
  if (Serial) {
    Serial.println("SET TRG0_TIP (D1) INPUT FLOAT");
  }
  pinMode(TRG0_TIP, INPUT);
}

#endif
