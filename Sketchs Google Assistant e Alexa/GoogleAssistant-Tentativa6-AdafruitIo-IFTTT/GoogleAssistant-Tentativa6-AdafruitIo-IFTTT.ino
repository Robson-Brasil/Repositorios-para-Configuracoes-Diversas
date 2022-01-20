/************************* Inclusão das Bibliotecas *********************************/
#include <WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
 
/************************* Conexão WiFi*********************************/
 
#define WIFI_SSID       "RVR 2,4GHz" // nome de sua rede wifi
#define WIFI_PASS       "RodrigoValRobson2021"     // senha de sua rede wifi
 
/********************* Credenciais Adafruit io *************************/
 
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "LoboAlfa" // Seu usuario cadastrado na plataforma da Adafruit
#define AIO_KEY         "aio_IIoi47ogUlAVQfyQEjIu1sjQeFwk"       // Sua key da dashboard
 
/********************** Variaveis globais *******************************/

#define Rele1            23
#define Rele2            22
#define Rele3            21
#define Rele4            19
#define Rele5            18
#define Rele6             5
#define Rele7            25
#define Rele8            26
//int Rele1 = 23; // pino do rele
//int Rele2 = 22; // pino do rele
//int Rele3 = 21; // pino do rele
//int Rele4 = 19; // pino do rele
//int Rele5 = 18; // pino do rele
//int Rele6 = 5; // pino do rele
//int Rele7 = 25; // pino do rele
//int Rele8 = 26; // pino do rele
 
/****************************** Declaração dos Feeds ***************************************/
 
WiFiClient client;
 
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

//Adafruit_MQTT_Publish Light = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/Rele");

/* feed responsavel por receber os dados da nossa dashboard */
Adafruit_MQTT_Subscribe Light1 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Rele1"); //MQTT_QOS_1
Adafruit_MQTT_Subscribe Light2 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Rele2");
Adafruit_MQTT_Subscribe Light3 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Rele3");
Adafruit_MQTT_Subscribe Light4 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Rele4");
Adafruit_MQTT_Subscribe Light5 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Rele5");
Adafruit_MQTT_Subscribe Light6 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Rele6");
Adafruit_MQTT_Subscribe Light7 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Rele7");
Adafruit_MQTT_Subscribe Light8 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Rele8");
 
/*************************** Declaração dos Prototypes ************************************/
 
void initSerial();
void initPins();
void initWiFi();
void initMQTT();
void conectar_broker();
 
/*************************** Sketch ************************************/
 
void setup() {
  initSerial();
  initPins();
  initWiFi();
  initMQTT();
}
 
void loop() {
  conectar_broker();
  mqtt.processPackets(5000);
 
}
 
/*************************** Implementação dos Prototypes ************************************/
 
/* Conexao Serial */
void initSerial() {
  Serial.begin(115200);
  delay(10);
}
 
/* Configuração dos pinos */
void initPins() {
  pinMode(Rele1, OUTPUT);
  digitalWrite(Rele1, HIGH);
  
  pinMode(Rele2, OUTPUT);
  digitalWrite(Rele2, HIGH);
  
  pinMode(Rele3, OUTPUT);
  digitalWrite(Rele3, HIGH);
  
  pinMode(Rele4, OUTPUT);
  digitalWrite(Rele4, HIGH);
  
  pinMode(Rele5, OUTPUT);
  digitalWrite(Rele5, HIGH);
  
  pinMode(Rele6, OUTPUT);
  digitalWrite(Rele6, HIGH);
  
  pinMode(Rele7, OUTPUT);
  digitalWrite(Rele7, HIGH);
  
  pinMode(Rele8, OUTPUT);
  digitalWrite(Rele8, HIGH);
}
 
/* Configuração da conexão WiFi */
void initWiFi() {
  Serial.print("Conectando-se na rede "); Serial.println(WIFI_SSID);
 
  WiFi.begin(WIFI_SSID, WIFI_PASS);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
 
  Serial.println("Conectado à rede com sucesso"); Serial.println("Endereço IP: "); Serial.println(WiFi.localIP());
}
 
/* Configuração da conexão MQTT */
void initMQTT() {
  Light1.setCallback(Rele1_callback);
  mqtt.subscribe(&Light1);
  
  Light2.setCallback(Rele2_callback);
  mqtt.subscribe(&Light2);
  
  Light3.setCallback(Rele3_callback);
  mqtt.subscribe(&Light3);
  
  Light4.setCallback(Rele4_callback);
  mqtt.subscribe(&Light4);
  
  Light5.setCallback(Rele5_callback);
  mqtt.subscribe(&Light5);
  
  Light6.setCallback(Rele6_callback);
  mqtt.subscribe(&Light6);
  
  Light7.setCallback(Rele7_callback);
  mqtt.subscribe(&Light7);
  
  Light8.setCallback(Rele8_callback);
  mqtt.subscribe(&Light8);
}

/*************************** Implementação dos Callbacks ************************************/
 
/* callback responsavel por tratar o feed do rele */
void Rele1_callback(char *data, uint16_t len) {
  String state = data;
 
  if (state == "ON") {
    digitalWrite(Rele1, LOW);
  } else {
    digitalWrite(Rele1, HIGH);
  }
 
  Serial.print("Led: "); Serial.println(state);
 
}

void Rele2_callback(char *data, uint16_t len) {
  String state = data;
 
  if (state == "ON") {
    digitalWrite(Rele2, LOW);
  } else {
    digitalWrite(Rele2, HIGH);
  }
 
  Serial.print("Led: "); Serial.println(state);
 
}
void Rele3_callback(char *data, uint16_t len) {
  String state = data;
 
  if (state == "ON") {
    digitalWrite(Rele3, LOW);
  } else {
    digitalWrite(Rele3, HIGH);
  }
 
  Serial.print("Led: "); Serial.println(state);
 
}
void Rele4_callback(char *data, uint16_t len) {
  String state = data;
 
  if (state == "ON") {
    digitalWrite(Rele4, LOW);
  } else {
    digitalWrite(Rele4, HIGH);
  }
 
  Serial.print("Led: "); Serial.println(state);
 
}
void Rele5_callback(char *data, uint16_t len) {
  String state = data;
 
  if (state == "ON") {
    digitalWrite(Rele5, LOW);
  } else {
    digitalWrite(Rele5, HIGH);
  }
 
  Serial.print("Led: "); Serial.println(state);
 
}
void Rele6_callback(char *data, uint16_t len) {
  String state = data;
 
  if (state == "ON") {
    digitalWrite(Rele6, LOW);
  } else {
    digitalWrite(Rele6, HIGH);
  }
 
  Serial.print("Led: "); Serial.println(state);
 
}
void Rele7_callback(char *data, uint16_t len) {
  String state = data;
 
  if (state == "ON") {
    digitalWrite(Rele7, LOW);
  } else {
    digitalWrite(Rele7, HIGH);
  }
 
  Serial.print("Led: "); Serial.println(state);
 
}
void Rele8_callback(char *data, uint16_t len) {
  String state = data;
 
  if (state == "ON") {
    digitalWrite(Rele8, LOW);
  } else {
    digitalWrite(Rele8, HIGH);
  }
 
  Serial.print("Led: "); Serial.println(state);
 }
 
/*************************** Demais implementações ************************************/
 
/* Conexão com o broker e também servirá para reestabelecer a conexão caso caia */
void conectar_broker() {
  int8_t ret;
 
  if (mqtt.connected()) {
    return;
  }
 
  Serial.println("Conectando-se ao broker mqtt...");
 
  uint8_t num_tentativas = 3;
  while ((ret = mqtt.connect()) != 0) {
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Falha ao se conectar. Tentando se reconectar em 5 segundos.");
    mqtt.disconnect();
    delay(5000);
    num_tentativas--;
    if (num_tentativas == 0) {
      Serial.println("Seu ESP será resetado.");
      while (1);
    }
  }
 
  Serial.println("Conectado ao broker com sucesso.");
}
