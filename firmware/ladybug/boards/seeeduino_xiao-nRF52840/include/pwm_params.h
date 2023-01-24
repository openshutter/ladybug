
#ifndef PWM_PARAMS_H
  #define PWM_PARAMS_H

  #include "board.h"
  #include "saul/periph.h"

  #ifdef __cplusplus
extern "C" {
  #endif

#define SAUL_PWM_NO_RGB /**< No RGB leds provided */

/**
 * @brief    LED configuration
 */
static const saul_pwm_dimmer_params_t saul_pwm_dimmer_params[] =
{
#ifdef LED0_PIN
    {
        .name    = "LED Red",
        .channel = { PWM_DEV(0), 0, SAUL_PWM_INVERTED },
    },
#endif
#ifdef LED1_PIN
    {
        .name    = "LED Blue",
        .channel = { PWM_DEV(0), 1, SAUL_PWM_INVERTED },
    },
#endif
#ifdef LED2_PIN
    {
        .name    = "LED Green",
        .channel = { PWM_DEV(0), 2, SAUL_PWM_INVERTED },
    },
#endif
};

  #ifdef __cplusplus
}
  #endif

#endif /* PWM_PARAMS_H */
/** @} */
