#include "esp_adc_cal.h"
#include <WiFi.h>
#include <PubSubClient.h>

#define LampadaRobson 23
#define Cooler 22
#define Bluetooth 21
#define LampadaVal 19
#define LampadaKinha 18
#define AutoFalante  5
#define Rele7 25
#define Rele8 26

/* Definições do Estado do RELÉ */
int toggleState_1  = 1; //Defina o número inteiro para lembrar o estado de alternância para o Relé 1
int toggleState_2  = 1; //Defina o número inteiro para lembrar o estado de alternância para o Relé 2
int toggleState_3  = 1; //Defina o número inteiro para lembrar o estado de alternância para o Relé 3
int toggleState_4  = 1; //Defina o número inteiro para lembrar o estado de alternância para o Relé 5
int toggleState_5  = 1; //Defina o número inteiro para lembrar o estado de alternância para o Relé 5

// WiFi Credentials
const char* ssid     =  "RVR 2,4GHz";
const char* password =  "RodrigoValRobson2021";

// MQTT client
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient); 
char *mqttServer = "broker.hivemq.com";
int mqttPort = 1883;
//const char* mqttUser = "RobsonBrasil";
//const char* mqttPassword = "@Lobo#Alfa@";

/* Setup Function for WiFi Connection */
void connectToWiFi() {
  Serial.print("Conectado a    ");
 
  WiFi.begin(ssid, password);
  Serial.println(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.print("Conectado.");
}

/* Setup Function for MQTT Communication */
void setupMQTT() {
  mqttClient.setServer(mqttServer, mqttPort);
  // define a função de retorno de chamada
  mqttClient.setCallback(callback);
}


/* Setup function, runs once */
void setup() {
  // Start serial communication
  Serial.begin(115200);

  //Comms setup
  connectToWiFi();
  setupMQTT();

  //LED Output
  pinMode(LampadaRobson, OUTPUT);
  digitalWrite(LampadaRobson, HIGH);

  pinMode(Cooler, OUTPUT);
  digitalWrite(Cooler, HIGH);

  pinMode(Bluetooth, OUTPUT);
  digitalWrite(Bluetooth, HIGH);

  pinMode(LampadaVal, OUTPUT);
  digitalWrite(LampadaVal, HIGH);

  pinMode(LampadaKinha, OUTPUT);
  digitalWrite(LampadaKinha, HIGH);
 
  pinMode(AutoFalante, OUTPUT);
  digitalWrite(AutoFalante, HIGH);
  
  pinMode(Rele7, OUTPUT);
  digitalWrite(Rele7, HIGH);
    
  pinMode(Rele8, OUTPUT);
  digitalWrite(Rele8, HIGH);
 
}

/* MQTT Reconnect Function */
void reconnect() {
  Serial.println("Conectando ao MQTT Broker...");
  while (!mqttClient.connected()) {
      Serial.println("Reconectando ao MQTT Broker..");
      String clientId = "ESP32ClientGoogleAssistant";
      clientId += String(random(0xffff), HEX);
      if (mqttClient.connect(clientId.c_str())) {
        Serial.println("Connected.");
        // inscreva-se no tópico
        mqttClient.subscribe("ESP32-MinhaCasa/Lampada/LigarLampadaQuartoRobson");
      }
  }
  while (!mqttClient.connected()) {
      Serial.println("Reconectando ao MQTT Broker..");
      String clientId = "ESP32ClientGoogleAssistant";
      clientId += String(random(0xffff), HEX);
      if (mqttClient.connect(clientId.c_str())) {
        Serial.println("Connected.");
        // inscreva-se no tópico
        mqttClient.subscribe("ESP32-MinhaCasa/Cooler/LigarCoolerQuartoRobson");
      }
  }
/*  
  while (!mqttClient.connected()) {
      Serial.println("Reconectando ao MQTT Broker..");
      String clientId = "ESP32ClientGoogleAssistant";
      clientId += String(random(0xffff), HEX);
      if (mqttClient.connect(clientId.c_str())) {
        Serial.println("Connected.");
        // inscreva-se no tópico        
        mqttClient.subscribe("/ESP32-MinhaCasa/LigarBluetoothQuartoRobson");
      }
  }
  while (!mqttClient.connected()) {
      Serial.println("Reconectando ao MQTT Broker..");
      String clientId = "ESP32ClientGoogleAssistant";
      clientId += String(random(0xffff), HEX);
      if (mqttClient.connect(clientId.c_str())) {
        Serial.println("Connected.");
        // inscreva-se no tópico
        mqttClient.subscribe("/ESP32-MinhaCasa/LigarLampadaQuartoVal");
      }
  }
  while (!mqttClient.connected()) {
      Serial.println("Reconectando ao MQTT Broker..");
      String clientId = "ESP32ClientGoogleAssistant";
      clientId += String(random(0xffff), HEX);
      if (mqttClient.connect(clientId.c_str())) {
        Serial.println("Connected.");
        // inscreva-se no tópico
        mqttClient.subscribe("/ESP32-MinhaCasa/LigarLampadaQuartoKinha");
      }
  }
  while (!mqttClient.connected()) {
      Serial.println("Reconectando ao MQTT Broker..");
      String clientId = "ESP32ClientGoogleAssistant";
      clientId += String(random(0xffff), HEX);
      if (mqttClient.connect(clientId.c_str())) {
        Serial.println("Connected.");
        // inscreva-se no tópico
        mqttClient.subscribe("/ESP32-MinhaCasa/LigarAutoFalanteQuartoRobson");
      }
  }
  while (!mqttClient.connected()) {
      Serial.println("Reconectando ao MQTT Broker..");
      String clientId = "ESP32ClientGoogleAssistant";
      clientId += String(random(0xffff), HEX);
      if (mqttClient.connect(clientId.c_str())) {
        Serial.println("Connected.");
        // inscreva-se no tópico
        mqttClient.subscribe("/ESP32-MinhaCasa/LigarRelé7QuartoRobson");
      }
  }
  while (!mqttClient.connected()) {
      Serial.println("Reconectando ao MQTT Broker..");
      String clientId = "ESP32ClientGoogleAssistant";
      clientId += String(random(0xffff), HEX);
      if (mqttClient.connect(clientId.c_str())) {
        Serial.println("Connected.");
        // inscreva-se no tópico
        mqttClient.subscribe("/ESP32-MinhaCasa/LigarRele8QuartoRobson");
      }
  }*/
}

/* MQTT Callback (Subscriber) Function */
void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  
   {
    for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    }
      if (payload[0] == '1'){
      digitalWrite(LampadaRobson, HIGH);
    }
    else if (payload[0] == '0'){
      digitalWrite(LampadaRobson, LOW);
        }
  }
   {
    for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    }
    if (payload[0] == '1'){
      digitalWrite(Cooler, HIGH);
    }
    else if (payload[0] == '0'){
      digitalWrite(Cooler, LOW);
        }
  }
}

void relayOnOff(int relay){

    switch(relay){
      case 1: 
             if(toggleState_1 == 1){
              digitalWrite(LampadaRobson, LOW); // Relé 1 Ligado
              toggleState_1 = 0;
//              Serial.println("Device1 ON");
              }
             else{
              digitalWrite(LampadaRobson, HIGH); // Relé 1 Desligado
              toggleState_1 = 1;
//              Serial.println("Device1 OFF");
              }
             delay(1);
      break;
      case 2: 
             if(toggleState_2 == 1){
              digitalWrite(Cooler, LOW); // Relé 2 Ligado
              toggleState_2 = 0;
//              Serial.println("Device2 ON");
              }
             else{
              digitalWrite(Cooler, HIGH); // Relé 2 Desligado
              toggleState_2 = 1;
//              Serial.println("Device2 OFF");
              }
             delay(1);
      break;
      case 3: 
             if(toggleState_3 == 1){
              digitalWrite(Bluetooth, LOW); // Relé 3 Ligado
              toggleState_3 = 0;
//              Serial.println("Device3 ON");
              }
             else{
              digitalWrite(Bluetooth, HIGH); // Relé 3 Desligado
              toggleState_3 = 1;
//              Serial.println("Device3 OFF");
              }
             delay(1);
      break;
      case 4: 
             if(toggleState_4 == 1){
              digitalWrite(LampadaVal, LOW); // Relé 4 Ligado
              toggleState_4 = 0;
//              Serial.println("Device4 ON");
              }
             else{
              digitalWrite(LampadaVal, HIGH); // Relé 4 Desligado
              toggleState_4 = 1;
//              Serial.println("Device4 OFF");
              }
             delay(1);
      break;
      case 5: 
             if(toggleState_5 == 1){
              digitalWrite(LampadaKinha, LOW); // Relé 5 Ligado
              toggleState_5 = 0;
//              Serial.println("Device5 ON");
              }
             else{
              digitalWrite(LampadaKinha, HIGH); // Relé 5 Desligado
              toggleState_5 = 1;
//              Serial.println("Device5 OFF");
              }
             delay(1);
      break;
      default : break;      
      }  
}
  /*
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    if((char)payload[i] == '1'){
      digitalWrite(Bluetooth, HIGH);
    }
    else{
      digitalWrite(Bluetooth, LOW);
        }
  }
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    if((char)payload[i] == '1'){
      digitalWrite(LampadaVal, HIGH);
    }
    else{
      digitalWrite(LampadaVal, LOW);
        }
      }
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    if((char)payload[i] == '1'){
      digitalWrite(LampadaKinha, HIGH);
    }
    else{
      digitalWrite(LampadaKinha, LOW);
        }
  }
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    if((char)payload[i] == '1'){
      digitalWrite(AutoFalante, HIGH);
    }
    else{
      digitalWrite(AutoFalante, LOW);
        }
  }
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    if((char)payload[i] == '1'){
      digitalWrite(Rele7, HIGH);
    }
    else{
      digitalWrite(Rele7, LOW);
        }
  }
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    if((char)payload[i] == '1'){
      digitalWrite(Rele8, HIGH);
    }
    else{
      digitalWrite(Rele8, LOW);
        }
  }*/

void loop() {
  if (!mqttClient.connected())
    reconnect();
  mqttClient.loop();
  delay(100);
}
