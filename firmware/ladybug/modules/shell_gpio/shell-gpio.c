#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "board.h"
#include "board_common.h"
#include "periph/gpio.h"
#include "shell.h"


typedef struct gpiopin {
  char  *key;
  gpio_t pin;
} GPIOPIN;

// yay lexical ordering!
GPIOPIN gpioTable[] = {
  { "D0", PIN_D0 },       // D0  is P0.02 (A0)
  { "D1", PIN_D1 },       // D1  is P0.03 (A1)
  { "D10", PIN_D10 },     // D10 is P1.15 (MOSI)
  { "D11", PIN_D11 },     // D11 is P0.26 (LED RED)
  { "D12", PIN_D12 },     // D12 is P0.06 (LED BLUE)
  { "D13", PIN_D13 },     // D13 is P0.30 (LED GREEN)
  { "D14", PIN_D14 },     // D14 is P0.14 (READ_BAT)
  { "D15", PIN_D15 },     // D15 is P1.08 (6D_PWR)
  { "D16", PIN_D16 },     // D16 is P0.27 (6D_I2C_SCL)
  { "D17", PIN_D17 },     // D17 is P0.07 (6D_I2C_SDA)
  { "D18", PIN_D18 },     // D18 is P0.11 (6D_INT1)
  { "D19", PIN_D19 },     // D19 is P1.10 (MIC_PWR)
  { "D2", PIN_D2 },       // D2  is P0.28 (A2)
  { "D20", PIN_D20 },     // D20 is P1.00 (PDM_CLK)
  { "D21", PIN_D21 },     // D21 is P0.16 (PDM_DATA)
  { "D22", PIN_D22 },     // D22 is P0.13 (HICHG)
  { "D23", PIN_D23 },     // D23 is P0.17 (~CHG)
  { "D24", PIN_D24 },     // D24 is P0.21 (QSPI_SCK)
  { "D25", PIN_D25 },     // D25 is P0.25 (QSPI_CSN)
  { "D26", PIN_D26 },     // D26 is P0.20 (QSPI_SIO_0 DI)
  { "D27", PIN_D27 },     // D27 is P0.24 (QSPI_SIO_1 DO)
  { "D28", PIN_D28 },     // D28 is P0.22 (QSPI_SIO_2 WP)
  { "D29", PIN_D29 },     // D29 is P0.23 (QSPI_SIO_3 HOLD)
  { "D3", PIN_D3 },       // D3  is P0.29 (A3)
  { "D30", PIN_D30 },     // D30 is P0.09 (NFC1)
  { "D31", PIN_D31 },     // D31 is P0.10 (NFC2)
  { "D4", PIN_D4 },       // D4  is P0.04 (A4,SDA)
  { "D5", PIN_D5 },       // D5  is P0.05 (A5,SCL)
  { "D6", PIN_D6 },       // D6  is P1.11 (TX)
  { "D7", PIN_D7 },       // D7  is P1.12 (RX)
  { "D8", PIN_D8 },       // D8  is P1.13 (SCK)
  { "D9", PIN_D9 },       // D9  is P1.14 (MISO)
  { "LEDB", PIN_D12 },    // Blue LED
  { "LEDG", PIN_D13 },    // Green LED
  { "LEDR", PIN_D11 },    // Red LED
};

static int compare_keys(const void *va, const void *vb) {
  const GPIOPIN *a = va, *b = vb;
  int            res = strcmp(a->key, b->key);
  // printf("strcmp(%s, %s) = %d\n", a->key, b->key, res);
  return res;
}

gpio_t get_pin(char *key) {
  GPIOPIN  key_pair[1] = { { key, 0 } };
  GPIOPIN *gpiopin     = bsearch(
      key_pair,
      gpioTable,
      sizeof gpioTable / sizeof gpioTable[0],
      sizeof gpioTable[0],
      compare_keys);
  return gpiopin ? gpiopin->pin : GPIO_UNDEF;
}

static int gpio_control(int argc, char **argv) {
  // Check number of arguments passed
  if (!(argc == 3 || argc == 4)) {
    printf("Invalid # of arguments\n");
    printf("Usage: %s [set / read / read-pd / read-pu] [PIN]\n", argv[0]);
    return -1;
  }

  // Fetch GPIO pin reference based on argument given
  gpio_t pin = get_pin(argv[2]);
  if (pin == GPIO_UNDEF) {
    printf("Invalid pin provided\n");
    return -1;
  }

  //
  // GPIO set commands
  if (strcmp(argv[1], "set") == 0) {
    // Get value from args
    int value = atoi(argv[3]);

    // Set low
    if (value == 0) {
      gpio_init(pin, GPIO_OUT);
      gpio_clear(pin);
      printf("Set pin %s (mcu %d) low\n", argv[2], pin);
      return 0;

      // Set High
    } else if (value == 1) {
      gpio_init(pin, GPIO_OUT);
      gpio_set(pin);
      printf("Set pin %s (mcu %d) high\n", argv[2], pin);
      return 0;

      // Set floating / high-z
    } else if (value == 2) {
      gpio_clear(pin);
      gpio_init(pin, GPIO_IN);
      printf("Set pin %s (mcu %d) High-Z\n", argv[2], pin);
      return 0;
    } else {
      printf("Invalid value provided\n");
      return -1;
    }
    printf("An unknown error occurred\n");
    return -1;

    //
    // GPIO get commands
    // Read w/o pull up/down
  } else if (strcmp(argv[1], "read") == 0) {
    gpio_init(pin, GPIO_IN);
    int value = gpio_read(pin);
    printf("Read pin %s (mcu %d) value %d\n", argv[2], pin, value);
    return 0;

    // Read w/ pull-down
  } else if (strcmp(argv[1], "read-pd") == 0) {
    gpio_init(pin, GPIO_IN_PD);
    int value = gpio_read(pin);
    printf("Read pin %s (mcu %d) value %d\n", argv[2], pin, value);
    return 0;

    // Read with pull-up
  } else if (strcmp(argv[1], "read-pu") == 0) {
    gpio_init(pin, GPIO_IN_PU);
    int value = gpio_read(pin);
    printf("Read pin %s (mcu %d) value %d\n", argv[2], pin, value);
    return 0;
  }
  return -1;
}

// Register our shell command
SHELL_COMMAND(gpio, "GPIO Control", gpio_control);
