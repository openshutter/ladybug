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

float mvToPercent(float mvolts) {
  float battery_level;

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

/**
 * Samples battery ADC voltage
 * Returns raw ADC output
 *
 * Per schematic, we have to set P0.14 ()
 */
static int batteryinfo_cli(int argc, char **argv) {
  ( void ) argc;
  ( void ) argv;

  printf("[bat] About to read battery at ADC %i\n", BAT_ADC_LINE);
  gpio_init(BAT_READ_ENABLE, GPIO_OUT);
  gpio_set(BAT_READ_ENABLE);
  gpio_clear(BAT_READ_ENABLE);

  int sample = 0;
  adc_init(ADC_LINE(BAT_ADC_LINE));
  sample = adc_sample(ADC_LINE(BAT_ADC_LINE), BAT_ADC_RESOLUTION);

  float sampleMv = (BAT_MV_PER_LSB * sample);

  float samplePer = mvToPercent(sampleMv);

  if (sample < 0) {
    printf("[bat] Selected resolution not applicable\n");
    return -1;
  } else {
    printf("[bat] Raw ADC_LINE(%i): %i \n", BAT_ADC_LINE, sample);
    printf("[bat] Lipo mV: %g \n", sampleMv);
    printf("[bat] Charge Percentage: %f \n", samplePer);
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
SHELL_COMMAND(batteryinfo, "Read Battery Charge", batteryinfo_cli);
// SHELL_COMMAND(vbat, "Vbat method", vbat);
