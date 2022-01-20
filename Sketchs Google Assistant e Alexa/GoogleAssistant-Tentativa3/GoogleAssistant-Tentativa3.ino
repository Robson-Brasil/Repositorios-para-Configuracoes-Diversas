/*
 * If you encounter any issues:
 * - check the readme.md at https://github.com/sinricpro/esp8266-esp32-sdk/blob/master/README.md
 * - ensure all dependent libraries are installed
 *   - see https://github.com/sinricpro/esp8266-esp32-sdk/blob/master/README.md#arduinoide
 *   - see https://github.com/sinricpro/esp8266-esp32-sdk/blob/master/README.md#dependencies
 * - open serial monitor and check whats happening
 * - check full user documentation at https://sinricpro.github.io/esp8266-esp32-sdk
 * - visit https://github.com/sinricpro/esp8266-esp32-sdk/issues and check for existing issues or open a new one
 */

// Uncomment the following line to enable serial debug output
//#define ENABLE_DEBUG

#ifdef ENABLE_DEBUG
       #define DEBUG_ESP_PORT Serial
       #define NODEBUG_WEBSOCKETS
       #define NDEBUG
#endif 

//#include <Arduino.h>
//#ifdef ESP8266 
//       #include <ESP8266WiFi.h>
//#endif 
#ifdef ESP32   
       #include <WiFi.h>
#endif

#include "SinricPro.h"
#include "SinricProSwitch.h"

#define WIFI_SSID         "RVR 2,4GHz"    
#define WIFI_PASS         "RodrigoValRobson2021"
#define APP_KEY           "529aedf6-7f26-4479-977a-274ceabe972c"      // Should look like "de0bxxxx-1x3x-4x3x-ax2x-5dabxxxxxxxx"
#define APP_SECRET        "90c00f1b-8c4e-473a-b022-8535bf5750d2-48f513e7-419b-4dc7-951e-4df9a9d7bdfd"   // Should look like "5f36xxxx-x3x7-4x3x-xexe-e86724a9xxxx-4c4axxxx-3x3x-x5xe-x9x3-333d65xxxxxx"
#define SWITCH_ID         "61e395d2c2131463b7feb473, 61e3975e5237d163c300b6e6, 61e39811c2131463b7feb56a"    // Should look like "5dc1564130xxxxxxxxxxxxxx"
//#define SWITCH_ID         "61e3975e5237d163c300b6e6"    // Should look like "5dc1564130xxxxxxxxxxxxxx"
//#define SWITCH_ID         "61e39811c2131463b7feb56a"    // Should look like "5dc1564130xxxxxxxxxxxxxx"
//#define BAUD_RATE         115200                // Change baudrate to your need

#define RELAY_1_PIN         23                  // Pin where the relay is connected (D5 = GPIO 14 on ESP8266)
#define RELAY_2_PIN         22                  // Pin where the relay is connected (D5 = GPIO 14 on ESP8266)
#define RELAY_3_PIN         21                  // Pin where the relay is connected (D5 = GPIO 14 on ESP8266)

bool onPowerState(const String &deviceId, bool &state) {
  digitalWrite(RELAY_1_PIN, state);             // set pin state
  digitalWrite(RELAY_2_PIN, state);             // set pin state
  digitalWrite(RELAY_3_PIN, state);             // set pin state
  return true;                                // request handled properly
}

void setup() {
  pinMode(RELAY_1_PIN, INPUT);                 // set relay-pin to output mode
  pinMode(RELAY_2_PIN, INPUT);                 // set relay-pin to output mode
  pinMode(RELAY_3_PIN, INPUT);                 // set relay-pin to output mode
  WiFi.begin(WIFI_SSID, WIFI_PASS);           // start wifi

  SinricProSwitch& mySwitch = SinricPro[SWITCH_ID];   // create new switch device
  mySwitch.onPowerState(onPowerState);                // apply onPowerState callback
  SinricPro.begin(APP_KEY, APP_SECRET);               // start SinricPro
}

void loop() {
  SinricPro.handle();                         // handle SinricPro commands
}
