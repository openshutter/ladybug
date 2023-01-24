
/*
 * Copyright (C) 2020 Freie Universität Berlin
 * Modified for Seedstudio XIAO nRF52840 by g-o-o-s
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
 * @brief       Peripheral configuration for the Seeeduino xiao-nRF52840
 *
 * @author      Martine S. Lenders <m.lenders@fu-berlin.de>
 *
 */

#ifndef PERIPH_CONF_H
  #define PERIPH_CONF_H

  #include "board.h"
  #include "saul/periph.h"

  #include "periph_cpu.h"
  #include "cfg_clock_32_1.h"
  #include "cfg_rtt_default.h"
  #include "cfg_timer_default.h"


  #ifdef __cplusplus
extern "C" {
  #endif

/**
 * @name   PWM configuration
 * @{
 */
static const pwm_conf_t pwm_config[] = {
    {
        NRF_PWM0,
        {
            GPIO_PIN(0, 26),
            GPIO_PIN(0, 6),
            GPIO_PIN(0, 30),
        }
    },
};
#define PWM_NUMOF ARRAY_SIZE(pwm_config)
/** @} */

/**
 * @name    UART configuration
 * @{
 */
static const uart_conf_t uart_config[] = {
  {
      .dev    = NRF_UARTE0,
      .rx_pin = GPIO_PIN(1, 11),
      .tx_pin = GPIO_PIN(1, 12),
  #ifdef MODULE_PERIPH_UART_HW_FC
      .rts_pin = GPIO_UNDEF,
      .cts_pin = GPIO_UNDEF,
  #endif
      .irqn = UARTE0_UART0_IRQn,
  },
};

  #define UART_0_ISR (isr_uart0)

  #define UART_NUMOF ARRAY_SIZE(uart_config)
/** @} */

/**
 * @name    SPI configuration
 * @{
 */
static const spi_conf_t spi_config[] = { {
    .dev  = NRF_SPIM0,
    .sclk = GPIO_PIN(1, 13),
    .mosi = GPIO_PIN(1, 15),
    .miso = GPIO_PIN(1, 14),
} };

  #define SPI_NUMOF ARRAY_SIZE(spi_config)
/** @} */

/**
 * @name    I2C configuration
 * @{
 */
static const i2c_conf_t i2c_config[] = {
  { .dev = NRF_TWIM1, .scl = GPIO_PIN(0, 5), .sda = GPIO_PIN(0, 4), .speed = I2C_SPEED_NORMAL }
};
  #define I2C_NUMOF ARRAY_SIZE(i2c_config)
/** @} */

  #ifdef __cplusplus
}
  #endif

#endif /* PERIPH_CONF_H */
/** @} */
