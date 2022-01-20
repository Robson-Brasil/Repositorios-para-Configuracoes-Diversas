/* This is a demo of an elegant way to run as many relays you want to
 * please check the notes in configuration section below!
 *
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

#include <SinricPro.h>
#include <SinricProSwitch.h>

/*****************
 * Configuration *
 *****************/

struct RelayInfo {
  String deviceId;
  String name;
  int pin;
};

std::vector<RelayInfo> relays = {
    {"61e395d2c2131463b7feb473", "Relay 1", 23},
    {"61e3975e5237d163c300b6e6", "Relay 2", 22},
    {"61e39811c2131463b7feb56a", "Relay 3", 21}};
//    {"5fxxxxxxxxxxxxxxxxxxxxxx", "Relay 4", D4},
//    {"5fxxxxxxxxxxxxxxxxxxxxxx", "Relay 5", D5},
//    {"5fxxxxxxxxxxxxxxxxxxxxxx", "Relay 6", D6},
 //   {"5fxxxxxxxxxxxxxxxxxxxxxx", "Relay 7", D7},
 //   {"5fxxxxxxxxxxxxxxxxxxxxxx", "Relay 8", D8}};
/*   ^^^^^^^^^^^^^^^^^^^^^^^^^   ^^^^^^^^^  ^^^
 *              |                     |      |
 *              |                     |      +---> digital PIN or GPIO number (see Note below!)
 *              |                     +----------> Name that will be printed to serial monitor
 *              +--------------------------------> deviceId
 * 
 *  In the vector above, you can add as many relays you want to have
 *  This is only limited to:
 *    - the number of SinricPro devices you have available
 *    - the number of pins / GPIOs your board have
 *
 *  Note: Some GPIO's are set to specific level when the board boots up
 *        This might result in strange behavior if there are relays connected to those pins
 *        Check your board documentation!
 */

#define WIFI_SSID  "RVR 2,4GHz"
#define WIFI_PASS  "RodrigoValRobson2021"
#define APP_KEY    "529aedf6-7f26-4479-977a-274ceabe972c"    // Should look like "de0bxxxx-1x3x-4x3x-ax2x-5dabxxxxxxxx"
#define APP_SECRET "90c00f1b-8c4e-473a-b022-8535bf5750d2-48f513e7-419b-4dc7-951e-4df9a9d7bdfd" // Should look like "5f36xxxx-x3x7-4x3x-xexe-e86724a9xxxx-4c4axxxx-3x3x-x5xe-x9x3-333d65xxxxxx"

#define BAUD_RATE  115200             // Change baudrate to your need

bool onPowerState(const String &deviceId, bool &state) {
  for (auto &relay : relays) {                                                            // for each relay configuration
    if (deviceId == relay.deviceId) {                                                       // check if deviceId matches
      Serial.printf("Equipamento, %s está %s\r\n", relay.name.c_str(), state ? "Ligado" : "Desligado");     // print relay name and state to serial
      digitalWrite(relay.pin, state);                                                         // set state to digital pin / gpio
      return true;                                                                            // return with success true
    }
  }
  return false; // if no relay configuration was found, return false
}

void setupRelayPins() {
  for (auto &relay : relays) {    // for each relay configuration
    pinMode(relay.pin, OUTPUT);     // set pinMode to OUTPUT
    digitalWrite(relay.pin, LOW);
  }
}

void setupWiFi() {
  Serial.printf("\r\n[Wifi]: Conectando");
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.printf(".");
    delay(250);
  }
  Serial.printf("Connectado!\r\n[WiFi]: IP-Address is %s\r\n", WiFi.localIP().toString().c_str());
}

void setupSinricPro() {
  for (auto &relay : relays) {                             // for each relay configuration
    SinricProSwitch &mySwitch = SinricPro[relay.deviceId];   // create a new device with deviceId from relay configuration
    mySwitch.onPowerState(onPowerState);                     // attach onPowerState callback to the new device
  }

  SinricPro.onConnected([]() { Serial.printf("Conectado ao SinricPro\r\n"); });
  SinricPro.onDisconnected([]() { Serial.printf("Desconectado para SinricPro\r\n"); });

  SinricPro.begin(APP_KEY, APP_SECRET);
}

void setup() {
  Serial.begin(BAUD_RATE);
  setupRelayPins();
  setupWiFi();
  setupSinricPro();
}

void loop() {
  SinricPro.handle();
}
