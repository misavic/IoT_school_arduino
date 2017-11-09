#include <SoftwareSerial.h>

SoftwareSerial mySerial(13, 12); // RX, TX

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  mySerial.begin(9600);
}

void loop() { // run over and over
  if (mySerial.available()) {
    String value = mySerial.readString();
    Serial.println(value);
  }
}
