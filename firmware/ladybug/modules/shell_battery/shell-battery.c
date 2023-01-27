#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "board.h"
#include "board_common.h"
#include "periph/adc.h"
#include "periph/vbat.h"
#include "shell.h"
#include "thread.h"
#include "ztimer.h"

// not sure if these apply to xaio
// 3.6V ADC range and 12-bit ADC resolution = 3600mV/4096
#define VBAT_MV_PER_LSB   (0.87891)

// 2M + 0.806M voltage divider on VBAT = (2M / (0.806M + 2M))
// #define VBAT_DIVIDER      (0.71275837F)

// Compensation factor for the VBAT divider
// #define VBAT_DIVIDER_COMP (1.403F)


// Resolution
#define ADC_RESOLUTION     ADC_RES_12BIT  // maximum
// ADC Line
#define ADC_BATT_LINE      7              // battery on xaio is on adc(7)

uint8_t mvToPercent(float mvolts) {
  uint8_t battery_level;

  if (mvolts >= 3000) {
    battery_level = 100;
  } else if (mvolts > 2900) {
    battery_level = 100 - ((3000 - mvolts) * 58) / 100;
  } else if (mvolts > 2740) {
    battery_level = 42 - ((2900 - mvolts) * 24) / 160;
  } else if (mvolts > 2440) {
    battery_level = 18 - ((2740 - mvolts) * 12) / 300;
  } else if (mvolts > 2100) {
    battery_level = 6 - ((2440 - mvolts) * 6) / 340;
  } else {
    battery_level = 0;
  }

  return battery_level;
}

static int chargeLevel(int argc, char **argv) {
  ( void ) argc;
  ( void ) argv;

  printf("Reading battery at ADC %i\n", ADC_BATT_LINE);

  int sample = 0;
  adc_init(ADC_LINE(ADC_BATT_LINE));
  sample = adc_sample(ADC_LINE(ADC_BATT_LINE), ADC_RESOLUTION);

  float sampleMv = (VBAT_MV_PER_LSB * sample);

  uint8_t samplePer = mvToPercent(sampleMv);

  if (sample < 0) {
    printf("Selected resolution not applicable\n");
    return -1;
  } else {
    printf("Raw ADC_LINE(%i): %i \n", ADC_BATT_LINE, sample);
    printf("Lipo mV: %g \n", sampleMv);
    printf("Charge Percentage: %d \n", samplePer);
    return 0;
  }
}

/*
static int vbat(int argc, char **argv) {
  ( void ) argc;
  ( void ) argv;

  printf("Running vbat_init()");
  vbat_init();
  int32_t sample = vbat_sample_mv();
  printf("vbat mV %li", sample);
  return 0;
}
*/

// Register our shell command
SHELL_COMMAND(chargelevel, "Read Battery Charge", chargeLevel);
// SHELL_COMMAND(vbat, "Vbat method", vbat);
