

#define RL2 53


void setup() {
  Serial.begin(9600);
  pinMode(RL2, OUTPUT);
  digitalWrite(RL2, HIGH);
  Serial.println(digitalRead(RL2));
  delay(1000);
  digitalWrite(RL2, LOW);
  Serial.println(digitalRead(RL2));
}

void loop() {
  digitalWrite(RL2, HIGH);
  Serial.println(digitalRead(RL2));
  delay(5000);
  digitalWrite(RL2, LOW);
  Serial.println(digitalRead(RL2));
  delay(5000);
  

}
