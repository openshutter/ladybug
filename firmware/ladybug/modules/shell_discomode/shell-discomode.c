/*
 * Copyright (C) 2008, 2009, 2010 Kaspar Schleiser <kaspar@schleiser.de>
 * Copyright (C) 2013 INRIA
 * Copyright (C) 2013 Ludwig Knüpfer <ludwig.knuepfer@fu-berlin.de>
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     examples
 * @{
 *
 * @file
 * @brief       Default application that shows a lot of functionality of RIOT
 *
 * @author      Kaspar Schleiser <kaspar@schleiser.de>
 * @author      Oliver Hahm <oliver.hahm@inria.fr>
 * @author      Ludwig Knüpfer <ludwig.knuepfer@fu-berlin.de>
 *
 * @}
 */

#include <stdio.h>
#include <string.h>

#include "board.h"
#include "board_common.h"
// #include "clk.h"
#include "periph/gpio.h"
// #include "periph_conf.h"
#include "shell.h"
// #include "thread.h"
// #include "timex.h"
// #include "ztimer/config.h"
#include "ztimer.h"


static void delay(void) {
  ztimer_sleep(ZTIMER_USEC, 50000);
}

static int disco(int argc, char **argv) {
  ( void ) argc;
  ( void ) argv;

  int pins[] = {
    PIN_D2, PIN_D3, PIN_D4, PIN_D5, PIN_D6,
  };

  for (int i = 0; i < 5; i++) { gpio_init(pins[i], GPIO_OUT); }

  while (true) {
    for (int i = 0; i < 5; i++) {
      gpio_set(pins[i]);
      delay();
    }
    delay();
    for (int i = 0; i < 5; i++) {
      gpio_clear(pins[i]);
      delay();
    }
    delay();
  };
  return 0;
}

// Register our shell command
SHELL_COMMAND(discomode, "Disco mode", disco);
