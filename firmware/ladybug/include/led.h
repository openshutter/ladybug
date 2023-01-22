#ifndef LED_H_
#define LED_H_

/**
 * Blinks the given led
 *
 * @param time        on time per repeat
 * @param repeat      number of times to repeat
 * @param off         off time between repeat
 * @param led         which led pin to use
 * @param activeLow   led pin active low instead of high (common anode)
 */
void blinkLed (
    int  time      = 100,
    int  repeat    = 1,
    int  off       = 0,
    int  led       = LED_BUILTIN,
    bool activeLow = true ) {
  pinMode ( led, OUTPUT );
  // Set a default off time of 50 if they specified repeat but not dwell
  if ( repeat > 1 && off == 0 ) {
    off = 50;
  }

  while ( repeat > 0 ) {
    // led off
    activeLow ? digitalWrite ( led, HIGH ) : digitalWrite ( led, LOW );
    // led on
    activeLow ? digitalWrite ( led, LOW ) : digitalWrite ( led, HIGH );
    // wait with led on
    delay ( time );
    // led off
    activeLow ? digitalWrite ( led, HIGH ) : digitalWrite ( led, LOW );
    // wait with led off
    delay ( off );
    repeat--;
  }
}

/**
 * Breathes the given led
 *
 * @param time        on time per repeat
 * @param repeat      number of times to repeat
 * @param off         off time between repeat
 * @param led         which led pin to use
 * @param activeLow   led pin active low instead of high (common anode)
 */
void breatheLed (
    int  time      = 1000,
    int  repeat    = 1,
    int  off       = 0,
    int  led       = LED_BUILTIN,
    bool activeLow = true ) {
  pinMode ( led, OUTPUT );
  float stepDuration = ( ( time / 2 ) / 255 );
  while ( repeat > 0 ) {
    if ( activeLow ) {
      for ( int i = 255; i > 0; i-- ) {
        analogWrite ( led, i );
        delay ( stepDuration );
      }
      for ( int i = 0; i < 255; i++ ) {
        analogWrite ( led, i );
        delay ( stepDuration );
      }
      activeLow ? digitalWrite ( led, HIGH ) : digitalWrite ( led, LOW );
    } else {
      for ( int i = 0; i < 255; i++ ) {
        analogWrite ( led, i );
        delay ( stepDuration );
      }
      for ( int i = 255; i > 0; i-- ) {
        analogWrite ( led, i );
        delay ( stepDuration );
      }
      activeLow ? digitalWrite ( led, HIGH ) : digitalWrite ( led, LOW );
    }
    // dwell
    delay ( off );
    repeat--;
  }
}

#endif
