/*********************************************************************
This is an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

This example is for a 128x32 size display using SPI to communicate
4 or 5 pins are required to interface

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "cactus_io_BME280_I2C.h"

//ARDUINO MEGA
#define OLED_MOSI  51
#define OLED_CLK   52
#define OLED_DC    5
#define OLED_CS    53
#define OLED_RESET 49

String message = "";
char* msgBuf;

Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

BME280_I2C bme(0x76);
//MQ135 gasSensor = MQ135(PF0);
String inputString = "";  
boolean stringComplete;
String addr="";

/* Uncomment this block to use hardware SPI
#define OLED_DC     6
#define OLED_CS     7
#define OLED_RESET  8
Adafruit_SSD1306 display(OLED_DC, OLED_RESET, OLED_CS);
*/

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup()   {                
  Serial.begin(9600);
  Serial3.begin(9600);
  Serial3.setTimeout(1000);
 
  if (!bme.begin()) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
  
  bme.setTempCal(-2);

  display.begin(SSD1306_SWITCHCAPVCC);
  writeText(">>IoT School<<");
  delay(2000);
  Serial3.println("Start");

}


void loop() {
  
  bme.readSensor();
  
  String pressure  = String(bme.getPressure_MB());
  String temperature = String(bme.getTemperature_C());
  String humidity = String(bme.getHumidity());
  
  writeText(temperature);
  String message = "Temp:" + temperature;
  Serial3.println (message);
  delay(3000);
  writeText(pressure);
  String message2 = "Press:" + pressure;
  Serial3.println (message2);
  delay (3000);
  writeText(humidity);
  String message3 = "Hum:" + humidity;
  Serial3.println (message3);
  delay(3000);
  String txt = Serial3.readString();
  Serial.println(txt);
  String message4 = ">>From cloud:" + txt + "<<";
  writeText(message4);
//  delay(1000);
//  String txt = Serial3.readString();
//  writeText(txt);

  delay(3000);
  
}

void writeText (String text)   
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(32,20);
  display.println(text);
  display.display();  
}






