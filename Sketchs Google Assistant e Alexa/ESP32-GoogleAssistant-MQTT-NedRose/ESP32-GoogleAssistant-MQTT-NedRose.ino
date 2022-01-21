/**********************************************************************************
//IoT - Automação Residencial
//Dispositivo : ESP32
//MQTT
//Red-Node
//Nora
//Google Assostant
//Autor : Robson Brasil
//Versão : 20
//Última Modificação : 29/12/2021
 **********************************************************************************/

#include <WiFi.h>
#include <PubSubClient.h>

// Relays
#define RelayPin1 23  //D23
#define RelayPin2 22  //D22
#define RelayPin3 21  //D21
#define RelayPin4 19  //D19
#define RelayPin5 18  //D18

//WiFi Status LED
#define wifiLed    0   //D0

// Update these with values suitable for your network.

const char* ssid = "RVR 2,4GHz"; //WiFI Name
const char* password = "RodrigoValRobson2021"; //WiFi Password
//const char* mqttServer = "broker.hivemq.com";
const char* mqttServer = "192.168.15.25";
const char* mqttUserName = "RobsonBrasil"; // MQTT username
const char* mqttPwd = "alfa"; // MQTT password
const char* clientID = "ESP32ClientGoogleAssistant"; // client id

#define sub1 "ESP32-MinhaCasaQuartoRobson/Lampada/LigarLampadaQuartoRobson"
#define sub2 "ESP32-MinhaCasaQuartoKinha/Lampada/LigarLampadaQuartoKinha"
#define sub3 "ESP32-MinhaCasaQuartoVal/Lampada/LigarLampadaQuartoVal"
#define sub4 "ESP32-MinhaCasaCozinha/Lampada/LigarLampadaCozinha"
#define sub5 "ESP32-MinhaCasaQuartoRobson/Bluetooth/LigarBluetooth"

#define pub1 "ESP32-MinhaCasaQuartoRobson/Lampada/LigarLampadaQuartoRobson"
#define pub2 "ESP32-MinhaCasaQuartoKinha/Lampada/LigarLampadaQuartoKinha"
#define pub3 "ESP32-MinhaCasaQuartoVal/Lampada/LigarLampadaQuartoVal"
#define pub4 "ESP32-MinhaCasaCozinha/Lampada/LigarLampadaCozinha"
#define pub5 "ESP32-MinhaCasaQuartoRobson/Bluetooth/LigarBluetooth"

WiFiClient espClient;
PubSubClient client(espClient);

unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (800)
char msg[MSG_BUFFER_SIZE];
int value = 0;

void setup_wifi() {
 delay(10);
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
 delay(500);
      Serial.print(".");
 }
      Serial.println("");
      Serial.println("WiFi connected");
      Serial.println("IP address: ");
      Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
  if (client.connect(clientID, mqttUserName, mqttPwd)) {
      Serial.println("MQTT connected");
      // ... and resubscribe
      client.subscribe(sub1);
      client.subscribe(sub2);
      client.subscribe(sub3);
      client.subscribe(sub4);
      client.subscribe(sub5);
    } 
  else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
      Serial.print("Message arrived [");
      Serial.print(topic);
      Serial.print("] ");

  if (strstr(topic, sub1))
  {
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
    }
      Serial.println();
    // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
      digitalWrite(RelayPin1, HIGH);   // Turn the LED on (Note that LOW is the voltage level
    } 
  else {
      digitalWrite(RelayPin1, LOW);  // Turn the LED off by making the voltage HIGH
    }    
  }
  else if ( strstr(topic, sub2))
  {
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
    }
      Serial.println();
    // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
      digitalWrite(RelayPin2, HIGH);   // Turn the LED on (Note that LOW is the voltage level
    } 
  else {
      digitalWrite(RelayPin2, LOW);  // Turn the LED off by making the voltage HIGH
    }
  }
  else if ( strstr(topic, sub3))
  {
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
    }
      Serial.println();
    // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
      digitalWrite(RelayPin3, HIGH);   // Turn the LED on (Note that LOW is the voltage level
    } 
  else {
      digitalWrite(RelayPin3, LOW);  // Turn the LED off by making the voltage HIGH
    }
  }
  else if ( strstr(topic, sub4))
  {
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
    }
      Serial.println();
    // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
      digitalWrite(RelayPin4, HIGH);   // Turn the LED on (Note that LOW is the voltage level
    } 
  else {
      digitalWrite(RelayPin4, LOW);  // Turn the LED off by making the voltage HIGH
    }
  }
    else if ( strstr(topic, sub5))
  {
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
    }
      Serial.println();
    // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
      digitalWrite(RelayPin5, HIGH);   // Turn the LED on (Note that LOW is the voltage level
    } 
  else {
      digitalWrite(RelayPin5, LOW);  // Turn the LED off by making the voltage HIGH
    }
  }
  else
  {
      Serial.println("unsubscribed topic");
  }
}

void setup() {
      Serial.begin(115200);
    
      pinMode(RelayPin1, OUTPUT);
      pinMode(RelayPin2, OUTPUT);
      pinMode(RelayPin3, OUTPUT);
      pinMode(RelayPin4, OUTPUT);
      pinMode(RelayPin5, OUTPUT);

      pinMode(wifiLed, OUTPUT);

  //During Starting all Relays should TURN OFF
      digitalWrite(RelayPin1, HIGH);
      digitalWrite(RelayPin2, HIGH);
      digitalWrite(RelayPin3, HIGH);
      digitalWrite(RelayPin4, HIGH);
      digitalWrite(RelayPin5, HIGH);
  
  //During Starting WiFi LED should TURN OFF
      digitalWrite(wifiLed, HIGH);

setup_wifi();
      client.setServer(mqttServer, 1883);
      client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
      digitalWrite(wifiLed, HIGH);
    reconnect();
  }
  else{
      digitalWrite(wifiLed, LOW);
  }
  client.loop();
}
