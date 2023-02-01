
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// some config defines in here
#include "ladybug_ble.h"

// Trigger firing
#include "ladybug_triggers.h"

// platform specific battery stuff
#include "seeeduino_xiao-nRF52840_battery.h"

#include "assert.h"
#include "event/timeout.h"
#include "ztimer.h"

#include "host/util/util.h"
#include "net/bluetil/ad.h"
#include "nimble_autoadv.h"
#include "nimble_riot.h"

#include "host/ble_gatt.h"
#include "host/ble_hs.h"
#include "services/gap/ble_svc_gap.h"
#include "services/gatt/ble_svc_gatt.h"

static const char *devinfo_manufacturer_name = CONFIG_DEVINFO_MANUFACTURER_NAME;
static const char *devinfo_model_number      = CONFIG_DEVINFO_MODEL_NUMBER;
static const char *devinfo_serial_number     = CONFIG_DEVINFO_SERIAL_NUMBER;
static const char *devinfo_fw_ver            = CONFIG_DEVINFO_FW_VER;
static const char *devinfo_hw_ver            = CONFIG_DEVINFO_HW_VER;

/**
 * BLE Device Info Request Handler
 */
int ble_devinfo_handler(
    uint16_t                     conn_handle,
    uint16_t                     attr_handle,
    struct ble_gatt_access_ctxt *ctxt,
    void                        *arg) {
  ( void ) conn_handle;
  ( void ) attr_handle;
  ( void ) arg;
  const char *str;

  switch (ble_uuid_u16(ctxt->chr->uuid)) {
    case BLE_GATT_CHAR_MANUFACTURER_NAME:
      str = devinfo_manufacturer_name;
      break;
    case BLE_GATT_CHAR_MODEL_NUMBER_STR:
      str = devinfo_model_number;
      break;
    case BLE_GATT_CHAR_SERIAL_NUMBER_STR:
      str = devinfo_serial_number;
      break;
    case BLE_GATT_CHAR_FW_REV_STR:
      str = devinfo_fw_ver;
      break;
    case BLE_GATT_CHAR_HW_REV_STR:
      str = devinfo_hw_ver;
      break;
    default:
      return BLE_ATT_ERR_UNLIKELY;
  }

  int res = os_mbuf_append(ctxt->om, str, strlen(str));
  return (res == 0) ? 0 : BLE_ATT_ERR_INSUFFICIENT_RES;
}

/**
 * Battery info handler
 */
int ble_bas_handler(
    uint16_t                     conn_handle,
    uint16_t                     attr_handle,
    struct ble_gatt_access_ctxt *ctxt,
    void                        *arg) {
  ( void ) conn_handle;
  ( void ) attr_handle;
  ( void ) arg;

  printf("[ble] battery service \n");

  int res = 0;

  switch (ble_uuid_u16(ctxt->chr->uuid)) {
    case BLE_GATT_CHAR_battery_level:
      int level = battery_charge_level();
      res       = os_mbuf_append(ctxt->om, &level, sizeof(level));
      break;
    case BLE_GATT_CHAR_battery_power_state:
      char state = battery_charge_status();
      res        = os_mbuf_append(ctxt->om, &state, sizeof(state));
      break;
    default:
      return BLE_ATT_ERR_UNLIKELY;
  }

  return (res == 0) ? 0 : BLE_ATT_ERR_INSUFFICIENT_RES;
}

/**
 * Trigger handler
 */
int ble_trigger_handler(
    uint16_t                     conn_handle,
    uint16_t                     attr_handle,
    struct ble_gatt_access_ctxt *ctxt,
    void                        *arg) {
  ( void ) conn_handle;
  ( void ) attr_handle;
  ( void ) arg;

  printf("[ble] trigger service \n");
  printf("[ble] op: %#010x \n", ctxt->op);
  printf("[ble] chr->uuid: %s \n", (char*) ctxt->chr->uuid);
  int res = 0;
  switch (ctxt->op) {
    case BLE_GATT_ACCESS_OP_READ_CHR:
      break;
    case BLE_GATT_ACCESS_OP_WRITE_CHR:
      switch (ble_uuid_u16(ctxt->chr->uuid)) {
        case BLE_GATT_CHAR_openshutter_trigger0_fire:
          trigger_sync(0, 250, 1000);
          res = os_mbuf_append(ctxt->om, "fired!", strlen("fired!"));
          break;
        default:
          return BLE_ATT_ERR_UNLIKELY;
      }
      break;
    case BLE_GATT_ACCESS_OP_READ_DSC:
      puts("read from descriptor");
      break;

    case BLE_GATT_ACCESS_OP_WRITE_DSC:
      puts("write to descriptor");
      break;

    default:
      return BLE_ATT_ERR_UNLIKELY;
  }
  return (res == 0) ? 0 : BLE_ATT_ERR_INSUFFICIENT_RES;
}

void _start_updating(void) {
  printf("[ble] _start_updating called\n");
}
void _stop_updating(void) {
  printf("[ble] _stop_updating called\n");
}

/**
 * Setup our service definitions
 */
const struct ble_gatt_svc_def gatt_svr_svcs[] = {
  { /* Device Information Service */
    .type = BLE_GATT_SVC_TYPE_PRIMARY,
    .uuid = BLE_UUID16_DECLARE(BLE_GATT_SVC_DEVINFO),
    .characteristics =
        (struct ble_gatt_chr_def[]) {
            {
                .uuid      = BLE_UUID16_DECLARE(BLE_GATT_CHAR_MANUFACTURER_NAME),
                .access_cb = ble_devinfo_handler,
                .flags     = BLE_GATT_CHR_F_READ,
            },
            {
                .uuid      = BLE_UUID16_DECLARE(BLE_GATT_CHAR_MODEL_NUMBER_STR),
                .access_cb = ble_devinfo_handler,
                .flags     = BLE_GATT_CHR_F_READ,
            },
            {
                .uuid      = BLE_UUID16_DECLARE(BLE_GATT_CHAR_SERIAL_NUMBER_STR),
                .access_cb = ble_devinfo_handler,
                .flags     = BLE_GATT_CHR_F_READ,
            },
            {
                .uuid      = BLE_UUID16_DECLARE(BLE_GATT_CHAR_FW_REV_STR),
                .access_cb = ble_devinfo_handler,
                .flags     = BLE_GATT_CHR_F_READ,
            },
            {
                .uuid      = BLE_UUID16_DECLARE(BLE_GATT_CHAR_HW_REV_STR),
                .access_cb = ble_devinfo_handler,
                .flags     = BLE_GATT_CHR_F_READ,
            },
            {
                0, /* no more characteristics in this service */
            },
        } },
  { /* Battery Status Service */
    .type = BLE_GATT_SVC_TYPE_PRIMARY,
    .uuid = BLE_UUID16_DECLARE(BLE_GATT_SVC_battery_service),
    .characteristics =
        (struct ble_gatt_chr_def[]) {
            {
                // battery level uint8
                .uuid      = BLE_UUID16_DECLARE(BLE_GATT_CHAR_battery_level),
                .access_cb = ble_bas_handler,
                .flags     = BLE_GATT_CHR_F_READ,
            },
            {
                // battery state
                .uuid      = BLE_UUID16_DECLARE(BLE_GATT_CHAR_battery_power_state),
                .access_cb = ble_bas_handler,
                .flags     = BLE_GATT_CHR_F_READ,
            },
            {
                0, /* no more characteristics in this service */
            },
        } },
  { /* Openshutter Service */
    .type = BLE_GATT_SVC_TYPE_PRIMARY,
    .uuid = BLE_UUID16_DECLARE(BLE_GATT_SVC_openshutter_triggers),
    .characteristics =
        (struct ble_gatt_chr_def[]) {
            {
                // Ondemand shutter trigger
                .uuid      = BLE_UUID16_DECLARE(BLE_GATT_CHAR_openshutter_trigger0_fire),
                .access_cb = ble_trigger_handler,
                .flags     = BLE_GATT_CHR_F_WRITE,
            },
            {
                0, /* no more characteristics in this service */
            },
        } },
  {
      0, /* no more services */
  },
};


/**
 * Initializes BLE and starts advertising
 */
int init_ble(void) {
  printf("[ble] Setting up BLE\n");
  int res = 0;
  ( void ) res;

  /* verify and add our custom services */
  res = ble_gatts_count_cfg(gatt_svr_svcs);
  assert(res == 0);
  res = ble_gatts_add_svcs(gatt_svr_svcs);
  assert(res == 0);

  /* set the device name */
  ble_svc_gap_device_name_set(CONFIG_NIMBLE_AUTOADV_DEVICE_NAME);
  /* reload the GATT server to link our added services */
  ble_gatts_start();

  // set advertise params
  nimble_autoadv_cfg_t cfg = {
    .adv_duration_ms = 60000,    // BLE_HS_FOREVER
    .adv_itvl_ms     = BLE_GAP_ADV_ITVL_MS(1000),
    .flags           = NIMBLE_AUTOADV_FLAG_CONNECTABLE | NIMBLE_AUTOADV_FLAG_SCANNABLE,
    .channel_map     = 0,
    .filter_policy   = 0,
    .own_addr_type   = nimble_riot_own_addr_type,
    .phy             = NIMBLE_PHY_1M,
    .tx_power        = 0,
  };
  nimble_autoadv_cfg_update(&cfg);

  /* configure and set the advertising data */
  // nimble_autoadv_set_gap_cb(&gap_event_cb, NULL);

  /* start to advertise this node */
  nimble_autoadv_start(NULL);

  return 0;
}
