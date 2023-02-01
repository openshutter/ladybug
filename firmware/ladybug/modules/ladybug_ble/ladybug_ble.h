#ifndef LADYBUG_BLE_H
#define LADYBUG_BLE_H

#ifndef CONFIG_DEVINFO_MANUFACTURER_NAME
  #define CONFIG_DEVINFO_MANUFACTURER_NAME
#endif

#ifndef CONFIG_DEVINFO_MODEL_NUMBER
  #define CONFIG_DEVINFO_MODEL_NUMBER
#endif

#ifndef CONFIG_DEVINFO_SERIAL_NUMBER
  #define CONFIG_DEVINFO_SERIAL_NUMBER
#endif

#ifndef CONFIG_DEVINFO_FW_VER
  #define CONFIG_DEVINFO_FW_VER
#endif

#ifndef CONFIG_DEVINFO_HW_VER
  #define CONFIG_DEVINFO_HW_VER
#endif

/**
 * { "name": "Battery Service", "identifier": "org.bluetooth.service.battery_service", "uuid":
 * "180F", "source": "gss" },
 */
#define BLE_GATT_SVC_battery_service (0x180F)

/**
 * { "name": "Battery Level", "identifier":
 * "org.bluetooth.characteristic.battery_level", "uuid": "2A19" , "source": "gss"},
 */
#define BLE_GATT_CHAR_battery_level (0x2A19)

/**
 * { "name": "Battery Power State", "identifier":
 * "org.bluetooth.characteristic.battery_power_state", "uuid": "2A1A" , "source": "gss"},
 */
#define BLE_GATT_CHAR_battery_power_state (0x2A1A)

/**
 * Our ladybug services
 */
#define BLE_GATT_SVC_openshutter_triggers       (0xF000)
#define BLE_GATT_CHAR_openshutter_trigger0_fire (0xF011)

/**
 * Initializes BLE and starts advertising
 */
extern int init_ble(void);

#endif /* LADYBUG_BLE_H */
