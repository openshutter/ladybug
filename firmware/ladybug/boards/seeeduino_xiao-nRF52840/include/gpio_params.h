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
 * @brief       Configuration of SAUL mapped GPIO pins
 *
 * @author      Martine S. Lenders <m.lenders@fu-berlin.de>
 */

#ifndef GPIO_PARAMS_H
  #define GPIO_PARAMS_H

  #include "board.h"
  #include "saul/periph.h"

  #ifdef __cplusplus
extern "C" {
  #endif

/**
 * @brief    LED configuration
 */
static const saul_gpio_params_t saul_gpio_params[] = {
  {
      .name  = "LED Red",
      .pin   = LED0_PIN,
      .mode  = GPIO_OUT,
      .flags = (SAUL_GPIO_INIT_CLEAR | SAUL_GPIO_INVERTED),
  },
  {
      .name  = "LED Blue",
      .pin   = LED1_PIN,
      .mode  = GPIO_OUT,
      .flags = (SAUL_GPIO_INIT_CLEAR | SAUL_GPIO_INVERTED),
  },
  {
      .name  = "LED Green",
      .pin   = LED2_PIN,
      .mode  = GPIO_OUT,
      .flags = (SAUL_GPIO_INIT_CLEAR | SAUL_GPIO_INVERTED),
  },
};

  #ifdef __cplusplus
}
  #endif

#endif /* GPIO_PARAMS_H */
/** @} */
