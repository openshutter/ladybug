
#ifndef PWM_PARAMS_H
  #define PWM_PARAMS_H

  #include "board.h"
  #include "periph/pwm.h"
  #include "saul/periph.h"

  #ifdef __cplusplus
extern "C" {
  #endif

/**
 * @brief    LED configuration
 */
static const saul_pwm_dimmer_params_t saul_pwm_dimmer_params[] = {
  {
      .name    = "LED Red",
      .channel = { PWM_DEV(0), 0, SAUL_PWM_INVERTED },
  },
  {
      .name    = "LED Blue",
      .channel = { PWM_DEV(0), 1, SAUL_PWM_INVERTED },
  },
  {
      .name    = "LED Green",
      .channel = { PWM_DEV(0), 2, SAUL_PWM_INVERTED },
  },
};

  #ifdef __cplusplus
}
  #endif

#endif /* PWM_PARAMS_H */
/** @} */
