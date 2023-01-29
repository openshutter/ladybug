#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "board.h"
#include "board_common.h"
#include "periph/adc.h"
#include "shell.h"
#include "ztimer.h"

/**
 * Converts milivolts to approx lipo charge level
 *
 * @param mvolts milivolts to convert to percentage
 */
float mv_to_percent(float mvolts) {
  mvolts = ( float ) mvolts;
 
  float batteryLevel = 0.0;

  if (mvolts >= 3000) {
    batteryLevel = 100;
  } else if (mvolts > 2900) {
    batteryLevel = 100 - ((3000 - mvolts) * 58) / 100;
  } else if (mvolts > 2740) {
    batteryLevel = 42 - ((2900 - mvolts) * 24) / 160;
  } else if (mvolts > 2440) {
    batteryLevel = 18 - ((2740 - mvolts) * 12) / 300;
  } else if (mvolts > 2100) {
    batteryLevel = 6 - ((2440 - mvolts) * 6) / 340;
  } else {
    batteryLevel = 0;
  }
  return batteryLevel;
}

/**
 * Samples battery ADC
 * Returns raw adc voltage
 */
int battery_adc_sample(void) {
  // Per schematic for xiao-nrf52840, we have to set P0.14 high
  // in order to connect the battery to the adc
  gpio_init(BAT_READ_ENABLE_PIN, GPIO_OUT);

  // pulse the pin low for a shake to clear the adc
  gpio_clear(BAT_READ_ENABLE_PIN);
  ztimer_sleep(ZTIMER_USEC, (100 * 1000));

  // then set it high for our reading
  gpio_set(BAT_READ_ENABLE_PIN);


  int sample = 0;

  // turn on the adc
  adc_init(ADC_LINE(BAT_ADC_LINE));
  // wait half a shake for it to come alive
  ztimer_sleep(ZTIMER_USEC, (50 * 1000));
  // take our sample
  sample = adc_sample(ADC_LINE(BAT_ADC_LINE), BAT_ADC_RESOLUTION);

  // Disable battery reads
  gpio_clear(BAT_READ_ENABLE_PIN);

  return sample;
}

/**
 * Returns battery charge level as a percentage
 */
int battery_charge_level(void) {
  int sample = battery_adc_sample();

  float sampleMv  = ( float ) sample * BAT_MV_PER_LSB;
  float samplePer = mv_to_percent(sampleMv);
  return samplePer;
}

/**
 * Checks battery charging status
 * Returns TRUE on charging
 * FALSE on batteries
 *
 * Note: the actual signal is active low
 */
int battery_charge_status(void) {
  // Read charging status
  gpio_init(BAT_CHARGE_STATUS_PIN, GPIO_IN);
  int chargeStatus = gpio_read(BAT_CHARGE_STATUS_PIN);
  // Invert the result
  if (chargeStatus) {
    return 0;
  } else {
    return 1;
  }
}


/**
 * CLI interface for battery information in shell
 */
static int batteryinfo_cli(int argc, char **argv) {
  ( void ) argc;
  ( void ) argv;

  int   sample       = battery_adc_sample();
  float sampleMv     = mv_to_percent(sample);
  int   chargeStatus = battery_charge_status();
  int   chargeLevel  = battery_charge_level();

  char chargeText[] = "Off";
  if (chargeStatus == 1) {
    strcpy(chargeText, "On ");
  }
  if (sample < 0) {
    printf("[bat] Selected resolution not applicable\n");
    return -1;
  } else {
    printf("[bat] Raw ADC_LINE(%i): %i \n", BAT_ADC_LINE, sample);
    printf("[bat] Lipo mV: %f \n", sampleMv);
    printf("[bat] Charge Percentage: %d \n", chargeLevel);
    printf("[bat] Charge Status: %s \n", chargeText);
    return 0;
  }
}

// Register our shell command
SHELL_COMMAND(batteryinfo, "Read Battery Charge", batteryinfo_cli);
