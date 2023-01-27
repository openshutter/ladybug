#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "board.h"
#include "board_common.h"
#include "periph/adc.h"
#include "shell.h"
#include "thread.h"
#include "ztimer.h"

#define RES     ADC_RES_12BIT

static int read_adc(int argc, char **argv) {
  ( void ) argc;
  ( void ) argv;

  int sample = 0;
  for (unsigned i = 0; i < ADC_NUMOF; i++) {
    sample = adc_sample(ADC_LINE(i), RES);
    if (sample < 0) {
      printf("ADC_LINE(%u): selected resolution not applicable\n", i);
    } else {
      printf("ADC_LINE(%u): %i\n", i, sample);
    }
  }
  return 0;
}

static int init_adc(int argc, char **argv) {
  ( void ) argc;
  ( void ) argv;

  /* initialize all available ADC lines */
  for (unsigned i = 0; i < ADC_NUMOF; i++) {
    if (adc_init(ADC_LINE(i)) < 0) {
      printf("Initialization of ADC_LINE(%u) failed\n", i);
      return 1;
    } else {
      printf("Successfully initialized ADC_LINE(%u)\n", i);
    }
  }
  return 0;
}


// Register our shell command
SHELL_COMMAND(adcread, "Read ADC", read_adc);
SHELL_COMMAND(adcinit, "Read ADC", init_adc);
