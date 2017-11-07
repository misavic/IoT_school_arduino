/*
  Basic ESP8266 MQTT example
  This sketch demonstrates the capabilities of the pubsub library in combination
  with the ESP8266 board/library.
  It connects to an MQTT server then:
  - publishes "hello world" to the topic "outTopic" every two seconds
  - subscribes to the topic "inTopic", printing out any messages
    it receives. NB - it assumes the received payloads are strings not binary
  - If the first character of the topic "inTopic" is an 1, switch ON the ESP Led,
    else switch it off
  It will reconnect to the server if the connection is lost using a blocking
  reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to
  achieve the same result without blocking the main loop.
  To install the ESP8266 board, (using Arduino 1.6.4+):
  - Add the following 3rd party board manager under "File -> Preferences -> Additional Boards Manager URLs":
       http://arduino.esp8266.com/stable/package_esp8266com_index.json
  - Open the "Tools -> Board -> Board Manager" and click install for the ESP8266"
  - Select your ESP8266 in "Tools -> Board"
*/

#include "WiFiEsp.h"
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <EEPROM.h>

#define PWM 3
#define INT 12

#define CLOCK 52
#define SDO 50
#define SDI 51
#define LT 53

#define ZERO  0x7E
#define ONE   0x0A
#define TWO   0xB6
#define THREE 0x9E
#define FOUR  0xCA
#define FIVE  0xDC
#define SIX   0xFC
#define SEVEN 0x0E
#define EIGHT 0xFE
#define NINE  0xDE
#define ALL 0xFE
#define NONE 0x00
#define LINE 0x80

const int numbers[10] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE };



void setup() {
  Serial.begin(9600);
  
  digitalWrite(SS, HIGH);
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV8);

  digitalWrite(SS, LOW);
  SPI.transfer(ZERO);
  SPI.transfer(ZERO);
  digitalWrite(SS, HIGH); 

  digitalWrite(SS, LOW);
  SPI.transfer(ONE);
  SPI.transfer(TWO);
  digitalWrite(SS, HIGH); 

}


  
void loop() {

  delay(1);
}



