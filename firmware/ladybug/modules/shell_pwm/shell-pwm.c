#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "board.h"
#include "board_common.h"
#include "periph/pwm.h"
#include "shell.h"


typedef struct pwmpin {
  char  *key;
  gpio_t pin;
} PWMPIN;

// yay lexical ordering!
PWMPIN gpioTable[] = {
  // A0 .. A5
  { "A1", PIN_D1 }, { "A2", PIN_D2 }, { "A3", PIN_D3 }, { "A4", PIN_D4 }, { "A5", PIN_D5 },
};

static int compare_keys(const void *va, const void *vb) {
  const PWMPIN *a = va, *b = vb;
  int            res = strcmp(a->key, b->key);
  // printf("strcmp(%s, %s) = %d\n", a->key, b->key, res);
  return res;
}

gpio_t get_pin(char *key) {
  PWMPIN  key_pair[1] = { { key, 0 } };
  PWMPIN *pwmpin     = bsearch(
      key_pair,
      gpioTable,
      sizeof gpioTable / sizeof gpioTable[0],
      sizeof gpioTable[0],
      compare_keys);
  return pwmpin ? pwmpin->pin : PWM_UNDEF;
}

static int pwm_control(int argc, char **argv) {
  // Check number of arguments passed
  if (!(argc == 3 || argc == 4)) {
    printf("Invalid # of arguments\n");
    printf("Usage: %s [set ] [PIN]\n", argv[0]);
    return -1;
  }

  // Fetch GPIO pin reference based on argument given
  gpio_t pin = get_pin(argv[2]);
  if (pin == GPIO_UNDEF) {
    printf("Invalid pin provided\n");
    return -1;
  }
  return -1;
}

// Register our shell command
SHELL_COMMAND(pwm, "PWM Control", pwm_control);
