#include "MQTTClient.h"
#include <ESP8266WiFi.h>
#include "WolkConn.h"

const char* ssid = "wifi_ssid";
const char* password = "wifi_password";
const char* mqtt_server = "52.213.16.227";

const char *device_key = "device_key";
const char *password_key = "password_key";
int portno = 1883;
const char *actuator1 = "Climate";

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

  wolk_set_actuator_references (&wolk, 1, actuator1);

  wolk_publish_num_actuator_status (&wolk, actuator1, 0, ACTUATOR_STATUS_READY, 0);
  
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
    if (strcmp(reference, actuator1)==0)
    {
      int val = atoi (value);
      Serial.println(value);
      wolk_publish_num_actuator_status (&wolk,actuator1, val, ACTUATOR_STATUS_READY, 0);   
    } 
  }
  
  String input = Serial.readString();
  input.trim();
  char charBuf[50];
  input.toCharArray(charBuf, 50);
  if(strstr(charBuf, "Press") != NULL)
  {
    char *ptr = strstr(charBuf,":");
    if (ptr!=NULL)
    {
      wolk_publish_single (&wolk, "P", ptr+1, DATA_TYPE_NUMERIC, 0);
    }
  } else if (strstr(charBuf, "Temp") != NULL)
  {
    char *ptr = strstr(charBuf,":");
    if (ptr!=NULL)
    {
      wolk_publish_single (&wolk, "T", ptr+1, DATA_TYPE_NUMERIC, 0);
    }
  } else if (strstr(charBuf, "Hum") != NULL)
  {
    char *ptr = strstr(charBuf,":");
    if (ptr!=NULL)
    {
      wolk_publish_single (&wolk, "H", ptr+1, DATA_TYPE_NUMERIC, 0);
    }
  }
 
  delay(1000);
  
  
}
