/*

UNO

sda - pin 10
sck - pin 13
mosi - pin 11
miso - pin 12
rst - pin 8

#define SS_PIN 10
#define RST_PIN 9


*/
#include <MFRC522.h>
#include <SPI.h>

#include "MQTTClient.h"
#include <ESP8266WiFi.h>
#include "WolkConn.h"

#define SS_PIN 15
#define RST_PIN 2

const char* ssid = "ssid";
const char* password = "password";
const char* mqtt_server = "52.213.16.227";
int portno = 1883;

const char *device_key = "RFID123";
const char *password_key = "d7fd99c3-3ddd-477c-a4ee-fa0679518558";

static wolk_ctx_t wolk;
WiFiClient espClient;
PubSubClient client(espClient);

MFRC522 rfid(SS_PIN, RST_PIN);

int codeRead = 0;
String reading;
bool cardOn = false;


int card[] = { 229, 143, 127, 99 };
int token[] = { 96,140, 49, 82 };

bool lightOn = false;

void setup() {

  Serial.begin(9600);

  setup_wifi();
  wolk_set_protocol(&wolk, PROTOCOL_TYPE_JSON);  
  wolk_connect(&wolk, &client, mqtt_server, portno, device_key, password_key);
  
  SPI.begin();
  rfid.PCD_Init();

}

void loop() {

  if (rfid.PICC_IsNewCardPresent())
  {   
      readRFID();
      
   
  }
 
 
}

void readRFID()
{
  rfid.PICC_ReadCardSerial();

  reading = String(rfid.uid.uidByte[0]) + " " + String(rfid.uid.uidByte[1]) + " " + String(rfid.uid.uidByte[2]) + " " + String(rfid.uid.uidByte[3]);

  bool isCard = true;
  bool isToken = true;
  
  for(int i =0; i<4; i++)
  {
    if(card[i] != rfid.uid.uidByte[i])
    {
      isCard = false;
    }

    if(token[i] != rfid.uid.uidByte[i])
    {
      isToken = false;
    }
  }

  if(isCard)
  {
    Serial.println("Card detected");
    if(lightOn)
    {
      wolk_publish_single (&wolk, "RFID", "false", DATA_TYPE_BOOLEAN, 0);
      Serial.println("Light off\n");
      lightOn = false;
      
    }
    else
    {
      wolk_publish_single (&wolk, "RFID", "true", DATA_TYPE_BOOLEAN, 0);
      Serial.println("Light on\n");
      lightOn = true;
      
    }
    Serial.println();
  }
  else if(isToken)
  {
    Serial.println("Token detected");
  }




}

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

