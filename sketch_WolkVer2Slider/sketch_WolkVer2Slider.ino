#include "WiFiEsp.h"
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <EEPROM.h>

#define RED 21
#define GREEN 20

#define CLOCK 52
#define SDO 50
#define SDI 51
#define LT 53


// Update these with values suitable for your network and device.
const char* ssid = "Radionice";
const char* password = "1112131415";
const char* mqtt_server = "52.213.16.227";

const char* username_mqtt = "123123123";
const char* password_mqtt = "db0052fc-b1ed-4c0a-a9a2-fe5cd68b3d8a";

const char* actuation_topic = "actuators/commands/123123123/CSL";
const char* status_topic = "actuators/status/123123123/CSL";
const char* readings_topic = "readings/123123123/CLR";

WiFiEspClient espClient;

PubSubClient client(espClient);

WiFiEspClient wiFiClient;

int state = 0;
int state_old = 0;
bool boot = true;

void setup() {
  Serial.begin(9600);

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  Serial2.setTimeout(970);

}

void loop() {

  bool test;
  if (!client.connected()) {
    Serial.println("Going under...");
    reconnect();
  }

  String toPublish = " {\"status\":\"READY\", \"value\":" + String(state) + "} " ;
  char publishMsg[toPublish.length()];
  toPublish.toCharArray(publishMsg, toPublish.length());

  
  
  if ( state != state_old || boot == true)
  {
    state_old = state;
    boot = false;

    
    Serial.print("Received value from slider: ");
    Serial.println(state);
    client.publish(status_topic,  publishMsg);

    String message = " {\"data\":\"" + String(state) + "\"} " ;

    char* msgBuf = message.c_str();
    Serial.println(String(state));

   client.publish(readings_topic, msgBuf);
   
  } else
  {
    client.publish(status_topic,  "PING REQ");
  }




  String msg = Serial2.readString().substring(67);
  char charMsg[msg.length()];
  msg.toCharArray(charMsg, msg.length());
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(msg);

  if (!root.success())
  {
    return;
  }

  state = root["value"];
  
}


void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  Serial2.begin(115200);
  WiFi.init(&Serial2);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(WiFi.status());
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(), username_mqtt, password_mqtt)) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      //client.publish(topic_temp, message_test);
      // ... and resubscribe
      bool tst = client.subscribe(actuation_topic);
      if (tst == true)
      {
        Serial.print("fSubsrcibe ok");
      } else
      {
        Serial.print("fSubsrcibe failed");
      }
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}



