#ifndef LED_H_
#define LED_H_

/*
 * Blinks the given led
 * Blinks led on for "time"
 * Then blocks for "off"
 * Repeating "repeat" times
 */
void blinkLed(int time = 50, int repeat = 1, int off = 0, int led = LED_BUILTIN) {
  bool activeLow = true;
  if (led != LED_BUILTIN) {
    activeLow = false;
  }
  while(repeat > 0) {
    // led off
    activeLow ? digitalWrite(led, HIGH) : digitalWrite(led, LOW);
    // led on
    activeLow ? digitalWrite(led, LOW) : digitalWrite(led, HIGH);
    // wait, led on
    delay(time);
    // led off
    activeLow ? digitalWrite(led, HIGH) : digitalWrite(led, LOW);
    // wait, led off
    delay(off);
    repeat--;
  }
}

#endif
