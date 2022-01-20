//IoT - Automação Residencial
//Dispositivo : ESP32
//Google Assistant
//Ativação por comando de voz "Ok, Google"
//Autor : Robson Brasil
//Criado em : 15/01/2022
//Versão : 30
//Última Modificação : 17/01/2022

#include <WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define Rele1            23
#define Rele2            22
#define Rele3            21
#define Rele4            19
#define Rele5            18
#define Rele6             5
#define Rele7            25
#define Rele8            26

#define WLAN_SSID       "RVR 2,4GHz"             // Your SSID
#define WLAN_PASS       "RodrigoValRobson2021"   // Your password

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com" //Adafruit Server
#define AIO_SERVERPORT  1883                   
#define AIO_USERNAME    "LoboAlfa"
#define AIO_KEY         "aio_IIoi47ogUlAVQfyQEjIu1sjQeFwk"

//WIFI CLIENT
WiFiClient client;

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

//Adafruit_MQTT_Publish _Rele = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/light");

Adafruit_MQTT_Subscribe _Rele1 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Rele1"); // Crie aqui sua variavel
Adafruit_MQTT_Subscribe _Rele2 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Rele2"); // a palavra feeds deve estar em todos
Adafruit_MQTT_Subscribe _Rele3 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Rele3");
Adafruit_MQTT_Subscribe _Rele4 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Rele4");
Adafruit_MQTT_Subscribe _Rele5 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Rele5");
Adafruit_MQTT_Subscribe _Rele6 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Rele6");
Adafruit_MQTT_Subscribe _Rele7 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Rele7");
Adafruit_MQTT_Subscribe _Rele8 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Rele8");

void MQTT_connect();

void setup() {
  Serial.begin(115200);
    delay(10);

  pinMode(Rele1, OUTPUT);
  pinMode(Rele2, OUTPUT);
  pinMode(Rele3, OUTPUT);
  pinMode(Rele4, OUTPUT);
  pinMode(Rele5, OUTPUT);
  pinMode(Rele6, OUTPUT);
  pinMode(Rele7, OUTPUT);
  pinMode(Rele8, OUTPUT);

  digitalWrite(Rele1, HIGH);
  digitalWrite(Rele2, HIGH);
  digitalWrite(Rele3, HIGH);
  digitalWrite(Rele4, HIGH);
  digitalWrite(Rele5, HIGH);
  digitalWrite(Rele6, HIGH);
  digitalWrite(Rele7, HIGH);
  digitalWrite(Rele8, HIGH);      
  
  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
    delay(500);
    while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
  }
  Serial.println();
  
  Serial.println("WiFi connected");
  Serial.println("IP address: "); 
  Serial.println(WiFi.localIP());
 
  mqtt.subscribe(&_Rele1);
  mqtt.subscribe(&_Rele2);
  mqtt.subscribe(&_Rele3);
  mqtt.subscribe(&_Rele4);
  mqtt.subscribe(&_Rele5);
  mqtt.subscribe(&_Rele6);
  mqtt.subscribe(&_Rele7);
  mqtt.subscribe(&_Rele8);
}

void loop() {
 
  MQTT_connect();
  
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(20000))) {
    if (subscription == &_Rele1) {
      Serial.print(F("Got: "));
      Serial.println((char *)_Rele1.lastread);
      int _Rele1_State = atoi((char *)_Rele1.lastread);
      digitalWrite(Rele1, _Rele1_State);
    }
    if (subscription == &_Rele2) {
      Serial.print(F("Got: "));
      Serial.println((char *)_Rele2.lastread);
      int _Rele2_State = atoi((char *)_Rele2.lastread);
      digitalWrite(Rele2, _Rele2_State);
    }
    if (subscription == &_Rele3) {
      Serial.print(F("Got: "));
      Serial.println((char *)_Rele3.lastread);
      int _Rele3_State = atoi((char *)_Rele3.lastread);
      digitalWrite(Rele3, _Rele3_State);
    }
    if (subscription == &_Rele4) {
      Serial.print(F("Got: "));
      Serial.println((char *)_Rele4.lastread);
      int _Rele4_State = atoi((char *)_Rele4.lastread);
      digitalWrite(Rele4, _Rele4_State);
    }
    if (subscription == &_Rele5) {
      Serial.print(F("Got: "));
      Serial.println((char *)_Rele5.lastread);
      int _Rele5_State = atoi((char *)_Rele5.lastread);
      digitalWrite(Rele5, _Rele5_State);
    }
    if (subscription == &_Rele6) {
      Serial.print(F("Got: "));
      Serial.println((char *)_Rele6.lastread);
      int _Rele6_State = atoi((char *)_Rele6.lastread);
      digitalWrite(Rele6, _Rele6_State);
    }
    if (subscription == &_Rele7) {
      Serial.print(F("Got: "));
      Serial.println((char *)_Rele7.lastread);
      int _Rele7_State = atoi((char *)_Rele7.lastread);
      digitalWrite(Rele7, _Rele7_State);
    }
    if (subscription == &_Rele8) {
      Serial.print(F("Got: "));
      Serial.println((char *)_Rele8.lastread);
      int _Rele8_State = atoi((char *)_Rele8.lastread);
      digitalWrite(Rele8, _Rele8_State);
    }
  }
}

void MQTT_connect() {
  int8_t ret;
  
  //Conectando MQTT
  if (mqtt.connected()) {
    return;
  }
      Serial.println("MQTT Conectado!");
           
   uint8_t retries = 3;
   
   while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);  // wait 5 seconds
           retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
     }
   }
  Serial.print("Conectando MQTT...");
}
