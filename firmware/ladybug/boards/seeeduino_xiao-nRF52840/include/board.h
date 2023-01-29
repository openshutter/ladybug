/*
 * Copyright (C) 2020 Freie Universität Berlin
 * Modified for Seeedstudio XIAO nRF52840 by g-o-o-s
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     boards_seeeduino_xiao-nRF52840
 * @{
 *
 * @file
 * @brief       Board specific configuration for the Seeeduino xiao-nRF52840
 *
 * @author      Martine S. Lenders <m.lenders@fu-berlin.de>
 */


// MODULE_ZTIMER_EXTEND

#ifndef BOARD_H
  #define BOARD_H

  #include "board_common.h"
  #include "cpu.h"
  #include "periph/adc.h"
  #include "periph/gpio.h"

  #ifdef __cplusplus
extern "C" {
  #endif

/**
 * @name    GPIO Pin Mapping
 * @{
 */

  #define GPIOA_BASE (0x0u)

  // D0 .. D13
  #define PIN_D0  GPIO_PIN(0, 2)     // D0  is P0.02 (A0)
  #define PIN_D1  GPIO_PIN(0, 3)     // D1  is P0.03 (A1)
  #define PIN_D2  GPIO_PIN(0, 28)    // D2  is P0.28 (A2)
  #define PIN_D3  GPIO_PIN(0, 29)    // D3  is P0.29 (A3)
  #define PIN_D4  GPIO_PIN(0, 4)     // D4  is P0.04 (A4,SDA)
  #define PIN_D5  GPIO_PIN(0, 5)     // D5  is P0.05 (A5,SCL)
  #define PIN_D6  GPIO_PIN(1, 11)    // D6  is P1.11 (TX)
  #define PIN_D7  GPIO_PIN(1, 12)    // D7  is P1.12 (RX)
  #define PIN_D8  GPIO_PIN(1, 13)    // D8  is P1.13 (SCK)
  #define PIN_D9  GPIO_PIN(1, 14)    // D9  is P1.14 (MISO)
  #define PIN_D10 GPIO_PIN(1, 15)    // D10 is P1.15 (MOSI)

  // A0 .. A5
  #define PIN_A1 PIN_D1
  #define PIN_A2 PIN_D2
  #define PIN_A3 PIN_D3
  #define PIN_A4 PIN_D4
  #define PIN_A5 PIN_D5

  // i2c/spi/uart
  #define PIN_SDA     PIN_D4
  #define PIN_SDL     PIN_D5
  #define PIN_UART_TX PIN_D6
  #define PIN_UART_RX PIN_D7
  #define PIN_SCLK    PIN_D8
  #define PIN_MISO    PIN_D9
  #define PIN_MOSI    PIN_D10

  // LEDs
  #define PIN_D11 GPIO_PIN(0, 26)    // D11 is P0.26 (LED RED)
  #define PIN_D12 GPIO_PIN(0, 6)     // D12 is P0.06 (LED BLUE)
  #define PIN_D13 GPIO_PIN(0, 30)    // D13 is P0.30 (LED GREEN)

  // LSM6DS3TR
  #define PIN_D15 GPIO_PIN(1, 8)     // D15 is P1.08 (6D_PWR)
  #define PIN_D16 GPIO_PIN(0, 27)    // D16 is P0.27 (6D_I2C_SCL)
  #define PIN_D17 GPIO_PIN(0, 7)     // D17 is P0.07 (6D_I2C_SDA)
  #define PIN_D18 GPIO_PIN(0, 11)    // D18 is P0.11 (6D_INT1)

  // MIC
  #define PIN_D19 GPIO_PIN(1, 10)    // 17,//42,   // D19 is P1.10 (MIC_PWR)
  #define PIN_D20 GPIO_PIN(1, 0)     // 26,//32,   // D20 is P1.00 (PDM_CLK)
  #define PIN_D21 GPIO_PIN(0, 16)    // 25,//16,   // D21 is P0.16 (PDM_DATA)

  // BQ25100 - Battery & Charge Control
  #define PIN_D22 GPIO_PIN(0, 13)    // D22 is P0.13 (HICHG)
  #define PIN_D23 GPIO_PIN(0, 17)    // D23 is P0.17 (~CHG) - Active when charging
  #define PIN_D14 GPIO_PIN(0, 14)    // D14 is P0.14 (READ_BAT) - Active Low
  #define PIN_A7  GPIO_PIN(0, 31)    // Battery Sample ADC

  // QSPI
  #define PIN_D24       GPIO_PIN(0, 21)    // D24 is P0.21 (QSPI_SCK)
  #define PIN_D25       GPIO_PIN(0, 25)    // D25 is P0.25 (QSPI_CSN)
  #define PIN_D26       GPIO_PIN(0, 20)    // D26 is P0.20 (QSPI_SIO_0 DI)
  #define PIN_D27       GPIO_PIN(0, 24)    // D27 is P0.24 (QSPI_SIO_1 DO)
  #define PIN_D28       GPIO_PIN(0, 22)    // D28 is P0.22 (QSPI_SIO_2 WP)
  #define PIN_D29       GPIO_PIN(0, 23)    // D29 is P0.23 (QSPI_SIO_3 HOLD)
  #define PIN_QSPI_SCK  PIN_D24
  #define PIN_QSP_CSN   PIN_D25
  #define PIN_QSPI_DI   PIN_D26
  #define PIN_QSPI_DO   PIN_D27
  #define PIN_QSPI_WP   PIN_D28
  #define PIN_QSPI_HOLD PIN_D29

  // NFC
  #define PIN_D30  GPIO_PIN(0, 9)     // D30 is P0.09 (NFC1)
  #define PIN_D31  GPIO_PIN(0, 10)    // D31 is P0.10 (NFC2)
  #define PIN_NFC1 PIN_D30
  #define PIN_NFC2 PIN_D31

/** @} */

/**
 * @name LED pin configuration
 * @{
 */

  /** @brief The red LED */
  #define LED0_PIN PIN_D11
  /** @brief The blue LED */
  #define LED1_PIN PIN_D12
  /** @brief The green LED */
  #define LED2_PIN PIN_D13

  /** @} */

  /**
   * @name    LED access macros
   * @{
   */

  /** @brief Enable red LED */
  #define LED0_ON gpio_clear(LED0_PIN)
  /** @brief Disable red LED */
  #define LED0_OFF gpio_set(LED0_PIN)
  /** @brief Toggle red LED */
  #define LED0_TOGGLE gpio_toggle(LED0_PIN)

  /** @brief Enable blue LED */
  #define LED1_ON gpio_clear(LED1_PIN)
  /** @brief Disable blue LED */
  #define LED1_OFF gpio_set(LED1_PIN)
  /** @brief Toggle blue LED */
  #define LED1_TOGGLE gpio_toggle(LED1_PIN)

  /** @brief Enable green LED */
  #define LED2_ON gpio_clear(LED2_PIN)
  /** @brief Disable green LED */
  #define LED2_OFF gpio_set(LED2_PIN)
  /** @brief Toggle green LED */
  #define LED2_TOGGLE gpio_toggle(LED2_PIN)

/** @} */


/**
 * @name  Battery access pins / adc config
 * @{
 */
  #define BAT_READ_ENABLE    PIN_D14
  #define BAT_ADC_LINE       7
  #define BAT_MV_PER_LSB     (0.87891)
  #define BAT_ADC_RESOLUTION ADC_RES_12BIT
/** @} */

  #ifdef __cplusplus
}
  #endif

#endif /* BOARD_H */
/** @} */
