#ifndef SEEEDUINO_XIAO_NRF52840_BATTERY_H
#define SEEEDUINO_XIAO_NRF52840_BATTERY_H

/**
 * Converts milivolts to approx lipo charge level
 * 
 * @param mvolts milivolts to convert to percentage
*/
extern float mv_to_percent(float mvolts);

/**
 * Samples battery ADC
 * Returns raw adc voltage
*/
extern int battery_adc_sample(void);

/**
 * Returns battery charge level as a percentage
*/
extern int battery_charge_level(void);

/**
 * Checks battery charging status
 * Returns TRUE on charging
 * FALSE on batteries
 * 
 * Note: the actual signal is active low
*/
extern int battery_charge_status(void);

#endif /* SEEEDUINO_XIAO_NRF52840_BATTERY_H */
