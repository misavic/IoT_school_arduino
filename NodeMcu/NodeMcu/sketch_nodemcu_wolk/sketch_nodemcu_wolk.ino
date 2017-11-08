#include "MQTTClient.h"
#include <ESP8266WiFi.h>
#include "WolkConn.h"

const char* ssid = "wifi_ssid";
const char* password = "wifi_password";
const char* mqtt_server = "52.213.16.227";

const char *device_key = "device_key";
const char *password_key = "password_key";
int portno = 1883;
const char *relay1 = "RL1";
const char *relay2 = "RL2";

char reference[32];
char command [32];
char value[64];
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

  wolk_set_actuator_references (&wolk, 2, relay1, relay2);

  wolk_publish_bool_actuator_status (&wolk,relay1, false, ACTUATOR_STATUS_READY, 0);

  wolk_publish_bool_actuator_status (&wolk,relay2, false, ACTUATOR_STATUS_READY, 0);
  
}

void loop() {
  memset (reference, 0, 32);
  memset (command, 0, 32);
  memset (value, 0, 64);

  wolk_receive (&wolk);
  if  (wolk_read_actuator (&wolk, command, reference, value)!= W_TRUE)
  {
//    Serial.println("Wolk client - Received:");
//    Serial.print("Command: ");
//    Serial.println(command);
//    Serial.print("Actuator reference:");
//    Serial.println(reference);
//    Serial.print("Value:");
//    Serial.println(value);
    if (strcmp(reference, relay1)==0)
    {
      if (strcmp(value,"true")==0)
      {
        Serial.println("R1 ON");
        wolk_publish_bool_actuator_status (&wolk,relay1, true, ACTUATOR_STATUS_READY, 0);
      } else if (strcmp(value,"false")==0)
      {
        Serial.println("R1 OFF");
        wolk_publish_bool_actuator_status (&wolk,relay1, false, ACTUATOR_STATUS_READY, 0);
      }
      
    } else if (strcmp(reference, relay2)==0)
    {
      if (strcmp(value,"true")==0)
      {
        Serial.println("R2 ON");
        wolk_publish_bool_actuator_status (&wolk,relay2, true, ACTUATOR_STATUS_READY, 0);
      } else if (strcmp(value,"false")==0)
      {
        Serial.println("R2 OFF");
        wolk_publish_bool_actuator_status (&wolk,relay2, false, ACTUATOR_STATUS_READY, 0);
      }
      
    }
  } 
 
  delay(1000);
  
  
}
