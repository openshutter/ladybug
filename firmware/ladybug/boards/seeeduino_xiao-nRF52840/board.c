/**
 * @ingroup     boards_seeeduino_xiao-nRF52840
 * @{
 * @file
 * @brief       Initialize gpio
 *
 * @}
 */

#ifndef BOARD_H
  #include "board.h"
#endif

void board_init(void) {
  // leds off at startup
  LED0_OFF;
  LED1_OFF;
  LED2_OFF;
}
