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

#define GATT_DEVICE_INFO_UUID       0x180A
#define GATT_MANUFACTURER_NAME_UUID 0x2A29
#define GATT_MODEL_NUMBER_UUID      0x2A24

// Overall service uuid
// UUID = 2606839e-59c6-4074-8a40-d7950dac4467
#define GATT_EXAMPLE_SVC_UUID \
  BLE_UUID128_INIT(           \
      0x67,                   \
      0x44,                   \
      0xac,                   \
      0x0d,                   \
      0x95,                   \
      0xd7,                   \
      0x40,                   \
      0x8a,                   \
      0x74,                   \
      0x40,                   \
      0xc6,                   \
      0x59,                   \
      0x9e,                   \
      0x83,                   \
      0x06,                   \
      0x26)


// Write field uuid
// UUID = c74d2ab1-14e1-49a6-9570-8c3f4a2127c3
#define GATT_EXAMPLE_SVC_RW_UUID \
  BLE_UUID128_INIT(              \
      0xc3,                      \
      0x27,                      \
      0x21,                      \
      0x4a,                      \
      0x3f,                      \
      0x8c,                      \
      0x70,                      \
      0x95,                      \
      0xa6,                      \
      0x49,                      \
      0xe1,                      \
      0x14,                      \
      0xb1,                      \
      0x2a,                      \
      0x4d,                      \
      0xc7)


// Read field uuid
// UUID = 09debdc4-050f-4111-993a-409752cb73a0
#define GATT_EXAMPLE_SVC_RO_UUID \
  BLE_UUID128_INIT(              \
      0xa0,                      \
      0x73,                      \
      0xcb,                      \
      0x52,                      \
      0x97,                      \
      0x40,                      \
      0x3a,                      \
      0x99,                      \
      0x11,                      \
      0x41,                      \
      0x0f,                      \
      0x05,                      \
      0xc4,                      \
      0xbd,                      \
      0xde,                      \
      0x09)

/**
 * Initializes BLE and starts advertising
 */
extern int init_ble(void);

#endif /* LADYBUG_BLE_H */
