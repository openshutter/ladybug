
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ladybug_ble.h"

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

int battery_level = 45;

static const char *devinfo_manufacturer_name = CONFIG_DEVINFO_MANUFACTURER_NAME;
static const char *devinfo_model_number      = CONFIG_DEVINFO_MODEL_NUMBER;
static const char *devinfo_serial_number     = CONFIG_DEVINFO_SERIAL_NUMBER;
static const char *devinfo_fw_ver            = CONFIG_DEVINFO_FW_VER;
static const char *devinfo_hw_ver            = CONFIG_DEVINFO_HW_VER;

// static event_queue_t   eq;
// static event_t         update_evt;
// static event_timeout_t update_timeout_evt;

static uint16_t conn_handle;

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
      printf("[ble] [READ] device information service: manufacturer name value\n");
      str = devinfo_manufacturer_name;
      break;
    case BLE_GATT_CHAR_MODEL_NUMBER_STR:
      printf("[ble] [READ] device information service: model number value\n");
      str = devinfo_model_number;
      break;
    case BLE_GATT_CHAR_SERIAL_NUMBER_STR:
      printf("[ble] [READ] device information service: serial number value\n");
      str = devinfo_serial_number;
      break;
    case BLE_GATT_CHAR_FW_REV_STR:
      printf("[ble] [READ] device information service: firmware revision value\n");
      str = devinfo_fw_ver;
      break;
    case BLE_GATT_CHAR_HW_REV_STR:
      printf("[ble] [READ] device information service: hardware revision value\n");
      str = devinfo_hw_ver;
      break;
    default:
      return BLE_ATT_ERR_UNLIKELY;

      int res = os_mbuf_append(ctxt->om, str, strlen(str));
      return (res == 0) ? 0 : BLE_ATT_ERR_INSUFFICIENT_RES;
  }

  int res = os_mbuf_append(ctxt->om, str, strlen(str));
  return (res == 0) ? 0 : BLE_ATT_ERR_INSUFFICIENT_RES;
}

int ble_bas_handler(
    uint16_t                     conn_handle,
    uint16_t                     attr_handle,
    struct ble_gatt_access_ctxt *ctxt,
    void                        *arg) {
  ( void ) conn_handle;
  ( void ) attr_handle;
  ( void ) arg;

  printf("[ble] [READ] battery level service: battery level value\n");

  uint8_t level = battery_level; /* this battery will never drain :-) */
  int     res   = os_mbuf_append(ctxt->om, &level, sizeof(level));
  return (res == 0) ? 0 : BLE_ATT_ERR_INSUFFICIENT_RES;
}

void _start_updating(void) {
  printf("[ble] _start_updating called\n");
};
void _stop_updating(void) {
  printf("[ble] _stop_updating called\n");
};

/**
 * GAP Event callback handler
 */
int gap_event_cb(struct ble_gap_event *event, void *arg) {
  ( void ) arg;

  switch (event->type) {
    case BLE_GAP_EVENT_CONNECT:
      if (event->connect.status) {
        _stop_updating();
        nimble_autoadv_start(NULL);
        return 0;
      }
      conn_handle = event->connect.conn_handle;
      break;

    case BLE_GAP_EVENT_DISCONNECT:
      _stop_updating();
      nimble_autoadv_start(NULL);
      break;

    case BLE_GAP_EVENT_SUBSCRIBE:
      printf("event->subscribe.attr_handle: %c", event->subscribe.attr_handle);
      /*
      if (event->subscribe.attr_handle == hrs_val_handle) {
        if (event->subscribe.cur_notify == 1) {
          _start_updating();
        } else {
          _stop_updating();
        }
      }
      */
      break;
  }

  return 0;
}

/*
// Setup our service
static int gatt_devinfo_manuf(
    uint16_t                     conn_handle,
    uint16_t                     attr_handle,
    struct ble_gatt_access_ctxt *ctxt,
    void                        *arg);

static int gatt_devinfo_model(
    uint16_t                     conn_handle,
    uint16_t                     attr_handle,
    struct ble_gatt_access_ctxt *ctxt,
    void                        *arg);

static int gatt_svc_rw(
    uint16_t                     conn_handle,
    uint16_t                     attr_handle,
    struct ble_gatt_access_ctxt *ctxt,
    void                        *arg);
*/

// Setup our service definitions
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
  { /* Battery Level Service */
    .type = BLE_GATT_SVC_TYPE_PRIMARY,
    .uuid = BLE_UUID16_DECLARE(BLE_GATT_SVC_BAS),
    .characteristics =
        (struct ble_gatt_chr_def[]) {
            {
                .uuid      = BLE_UUID16_DECLARE(BLE_GATT_CHAR_BATTERY_LEVEL),
                .access_cb = ble_bas_handler,
                .flags     = BLE_GATT_CHR_F_READ,
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
    .adv_duration_ms = BLE_HS_FOREVER,
    .adv_itvl_ms     = BLE_GAP_ADV_ITVL_MS(100),
    .flags           = NIMBLE_AUTOADV_FLAG_CONNECTABLE | NIMBLE_AUTOADV_FLAG_LEGACY |
             NIMBLE_AUTOADV_FLAG_SCANNABLE,
    .channel_map   = 0,
    .filter_policy = 0,
    .own_addr_type = nimble_riot_own_addr_type,
    .phy           = NIMBLE_PHY_1M,
    .tx_power      = 0,
  };
  nimble_autoadv_cfg_update(&cfg);

  /* configure and set the advertising data */
  // nimble_autoadv_set_gap_cb(&gap_event_cb, NULL);

  /* start to advertise this node */
  nimble_autoadv_start(NULL);

  return 0;
}
