
#ifndef ADC_PARAMS_H
  #define ADC_PARAMS_H

  #include "board.h"
  #include "periph/adc.h"
  #include "saul/periph.h"

  #ifdef __cplusplus
extern "C" {
  #endif

/**
 * @brief    ADC configuration
 */
static const saul_adc_params_t saul_adc_params[] = {
  {
      .name = "ADC_LINE(0)",
      .line = 0,
  },
  {
      .name = "ADC_LINE(1)",
      .line = 1,
  },
  {
      .name = "ADC_LINE(2)",
      .line = 2,
  },
  {
      .name = "ADC_LINE(3)",
      .line = 3,
  },
  {
      .name = "ADC_LINE(4)",
      .line = 4,
  },
  {
      .name = "ADC_LINE(5)",
      .line = 5,
  },
  {
      .name = "ADC_LINE(6)",
      .line = 6,
  },
  {
      .name = "ADC_LINE(7)",
      .line = 7,
  },
  {
      .name = "ADC_LINE(8)",
      .line = 8,
  },
  {
      .name = "ADC_LINE(9)",
      .line = 9,
  },
};

  #ifdef __cplusplus
}
  #endif

#endif /* ADC_PARAMS_H */
/** @} */
