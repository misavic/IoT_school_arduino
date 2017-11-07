#include <MQTTClient.h>
#include <WolkConn.h>
#include "WiFiEsp.h"
WiFiEspClient espClient;

PubSubClient client(espClient);

const char* ssid = "wifi_ssid";
const char* password = "wifi_password";
const char* mqtt_server = "52.213.16.227";

const char *device_key = "device_key";
const char *password_key = "password_key";
int portno = 1883;

char reference[32];
char command [32];
char value[64];
static wolk_ctx_t wolk;

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

  wolk_publish_single (&wolk, "TS", "Arduino", DATA_TYPE_STRING, 0);
  
  wolk_publish_single (&wolk, "TN", "30", DATA_TYPE_NUMERIC, 0);

  wolk_publish_single (&wolk, "TB", "true", DATA_TYPE_BOOLEAN, 0);

  delay (10000);

  wolk_add_bool_reading(&wolk, "TB", false, 0);

  wolk_add_string_reading(&wolk, "TS", "Miki", 0);

  wolk_add_numeric_reading(&wolk, "TN", 100, 0);

  wolk_publish (&wolk);
  
}

void loop() {

  delay(1000);
  
  
}

