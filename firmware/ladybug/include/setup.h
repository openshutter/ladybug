#ifndef SETUP_H_
#define SETUP_H_

// Includes
#include <Adafruit_LittleFS.h>
#include <InternalFileSystem.h>
#include <bluefruit.h>

#include "led.h"

// BLE Service
BLEDfu  bledfu;     // OTA DFU service
BLEDis  bledis;     // device information
BLEUart bleuart;    // uart over ble
BLEBas  blebas;     // battery

// Trigger Pins
#define TRG0_RING D0
#define TRG0_TIP  D1

void startAdv ( void ) {
  // Advertising packet
  Bluefruit.Advertising.addFlags ( BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE );
  Bluefruit.Advertising.addTxPower ();

  // Include bleuart 128-bit uuid
  Bluefruit.Advertising.addService ( bleuart );

  // Secondary Scan Response packet (optional)
  // Since there is no room for 'Name' in Advertising packet
  Bluefruit.ScanResponse.addName ();

  /**
   *  Start Advertising
   * - Enable auto advertising if disconnected
   * - Interval:  fast mode = 20 ms, slow mode = 152.5 ms
   * - Timeout for fast mode is 30 seconds
   * - Start(timeout) with timeout = 0 will advertise forever (until connected)
   *
   * For recommended advertising interval
   * https://developer.apple.com/library/content/qa/qa1931/_index.html
   */
  Bluefruit.Advertising.restartOnDisconnect ( true );
  Bluefruit.Advertising.setInterval ( 32, 244 );    // in unit of 0.625 ms
  Bluefruit.Advertising.setFastTimeout ( 30 );      // number of seconds in fast mode
  Bluefruit.Advertising.start ( 0 );                // 0 = Don't stop advertising after n seconds
}

/**
 * callback invoked when central connects
 * @param conn_handle connection where this event happens
 */
void connect_callback ( uint16_t conn_handle ) {
  // Get the reference to current connection
  BLEConnection *connection = Bluefruit.Connection ( conn_handle );

  char central_name[32] = { 0 };
  connection->getPeerName ( central_name, sizeof ( central_name ) );

  if ( Serial ) {
    Serial.print ( "BLE Connected to " );
    Serial.println ( central_name );
  }
}

/**
 * Callback invoked when a connection is dropped
 * @param conn_handle connection where this event happens
 * @param reason is a BLE_HCI_STATUS_CODE which can be found in ble_hci.h
 */
void disconnect_callback ( uint16_t conn_handle, uint8_t reason ) {
  ( void ) conn_handle;
  ( void ) reason;

  if ( Serial ) {
    Serial.println ();
  }
  if ( Serial ) {
    Serial.print ( "BLE Disconnected, reason = 0x" );
    Serial.println ( reason, HEX );
  }
}

/**
 * Initial setup function to initialize output modes
 */
void initSetupOutputs () {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode ( LED_BUILTIN, OUTPUT );

  // set triggers as floating
  pinMode ( TRG0_RING, OUTPUT );
  digitalWrite ( TRG0_RING, LOW );
  pinMode ( TRG0_RING, INPUT );

  pinMode ( TRG0_TIP, OUTPUT );
  digitalWrite ( TRG0_TIP, LOW );
  pinMode ( TRG0_TIP, INPUT );
}

/**
 * Initial setup function to start up BLE
 */
void initSetupBle () {
  // Setup the BLE LED to be enabled on CONNECT
  // Note: This is actually the default behavior, but provided
  // here in case you want to control this LED manually via PIN 19
  Bluefruit.autoConnLed ( true );
  Bluefruit.configPrphBandwidth ( BANDWIDTH_LOW );
  Bluefruit.begin ();

  Bluefruit.setTxPower ( 4 );

  Bluefruit.Periph.setConnectCallback ( connect_callback );
  Bluefruit.Periph.setDisconnectCallback ( disconnect_callback );

  // To be consistent OTA DFU should be added first if it exists
  bledfu.begin ();

  // Configure and Start Device Information Service
  bledis.setManufacturer ( "Openshutter" );
  bledis.setModel ( "Ladybug" );
  bledis.setHardwareRev ( "v0" );
  bledis.setSoftwareRev ( "v0.0.1" );
  bledis.begin ();

  // Start BLE Battery Service
  blebas.begin ();
  blebas.write ( 100 );

  // Set up and start advertising
  startAdv ();
}

#endif
