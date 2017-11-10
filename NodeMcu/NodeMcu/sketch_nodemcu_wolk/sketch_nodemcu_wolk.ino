#include "MQTTClient.h"
#include <ESP8266WiFi.h>
#include "WolkConn.h"



const char* ssid = "wifi_ssid";
const char* password = "wifi_pass";
const char* mqtt_server = "52.213.16.227";

const char *device_key = "PROXIMITY";
const char *password_key = "bf0844d1-9f53-4f23-abd2-cc629f72e0db";

int portno = 1883;

static wolk_ctx_t wolk;
WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
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


void setup() {
  Serial.begin(9600);

  setup_wifi();

  wolk_set_protocol(&wolk, PROTOCOL_TYPE_JSON);

  wolk_connect(&wolk, &client, mqtt_server, portno, device_key, password_key);
  
}

void loop() {
  //Serial.println("Read:");
  String input = Serial.readString();
  Serial.println(input);
  input.trim();
  char charBuf[50];
  input.toCharArray(charBuf, 50);

  wolk_publish_single (&wolk, "PR", charBuf, DATA_TYPE_NUMERIC, 0);

  delay(1000);
 
 
}
