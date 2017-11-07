

#define RL1 6
#define RL2 10


void setup() {
  Serial.begin(9600);
  pinMode(RL2, OUTPUT);
  pinMode(RL1, OUTPUT);
}

void loop() {
  digitalWrite(RL2, HIGH);
  digitalWrite(RL1, HIGH);
  Serial.println(digitalRead(RL2));
  delay(5000);
  digitalWrite(RL2, LOW);
  digitalWrite(RL1, LOW);
  Serial.println(digitalRead(RL2));
  delay(5000);
  

}
