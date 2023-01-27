#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "triggers.h"

#include "board.h"
#include "periph/gpio.h"
#include "shell.h"

#include "ztimer.h"

/**
 * Fires a trigger in a typical half-press -> full-press sequence
 *
 * @param trigger trigger index to fire
 * @param duration miliseconds to fire TRGn_TIP
 * @param preshoot miliseconds to fire TRGn_RING before TRGn_TIP
 */
int trigger(int trigger = 0, int duration = 250, int preshoot = 0) {
  if (trigger != 0) {
    printf("Only one trigger supported at this time!");
    return -1;
  }

  int tip = TRG0_TIP;
  int ring = TRG0_RING;

  printf("Firing trigger TRG%i with: \n", trigger);
  printf("duration:  %6ims \n", duration);
  printf("preshoot:  %6ims \n", preshoot);

  // Init pins as outputs
  gpio_init(tip, GPIO_OUT);
  gpio_init(ring, GPIO_OUT);

  // Ensure they're both pulled low
  gpio_write(tip, 0);
  gpio_write(ring, 0);

  // Pull "half-press" high
  gpio_write(ring, 1);
  // Sleep for preshoot miliseconds
  ztimer_sleep(ZTIMER_USEC, (preshoot * 1000));
  // Pull "full-press" high
  gpio_write(tip, 1);

  // Sleep for duration miliseconds
  ztimer_sleep(ZTIMER_USEC, (duration * 1000));

  // Pull both low
  gpio_write(tip, 0);
  gpio_write(ring, 0);
  return 0;
}

/**
 * Fires just TRGn_RING ("half-press" / preshoot).
 * Caller is responsible for ensuring TRGn_TIP is overlapped with this pulse
 *
 * @param trigger trigger index to fire
 * @param duration miliseconds to fire TRGn_RING
 */
int trigger_ring(int trigger = 0, int duration = 250) {
  if (trigger != 0) {
    printf("Only one trigger supported at this time!");
    return -1;
  }

  // int tip = TRG0_TIP;
  int ring = TRG0_RING;

  printf("Firing trigger TRG%i_RING with: \n", trigger);
  printf("duration:  %6ims \n", duration);

  gpio_init(ring, GPIO_OUT);
  gpio_write(ring, 0);
  // Sleep for duration miliseconds
  ztimer_sleep(ZTIMER_USEC, (duration * 1000));
  gpio_write(ring, 0);
  return 0;
}

/**
 * Fires just TRGn_TIP ("full-press" / shoot)
 *
 * @param trigger trigger index to fire
 * @param duration miliseconds to fire TRGn_TIP
 */
int trigger_tip(int trigger = 0, int duration = 250) {
  if (trigger != 0) {
    printf("Only one trigger supported at this time!");
    return -1;
  }

  int tip = TRG0_TIP;
  // int ring = TRG0_RING;

  printf("Firing trigger TRG%i_TIP with: \n", trigger);
  printf("duration:  %6ims \n", duration);

  gpio_init(tip, GPIO_OUT);
  gpio_write(tip, 0);
  // Sleep for duration miliseconds
  ztimer_sleep(ZTIMER_USEC, (duration * 1000));
  gpio_write(tip, 0);
  return 0;
}

/**
 * CLI interface for trigger
 */
static int trigger_cli(int argc, char **argv) {
  // Check number of arguments passed
  if (!(argc == 1 || argc == 3)) {
    printf("Invalid # of arguments\n");
    printf("Usage: %s [duration] [preshoot]\n", argv[0]);
    return -1;
  }

  if (argc == 1) {
    ( void ) trigger(0, 250, 500);
  }
  if (argc == 3) {
    ( void ) trigger(0, atoi(argv[1]), atoi(argv[2]));
  }
  return 0;
}
// Register our shell command
SHELL_COMMAND(trigger, "Trigger Control", trigger_cli);
