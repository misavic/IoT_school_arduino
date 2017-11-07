
#define MOVEMENT 12
#define EN 47

#define RL2 53

int currentState = 0;

void setup() {
  Serial.begin(9600);
  
  pinMode(MOVEMENT, INPUT);
  pinMode(EN, OUTPUT);
  digitalWrite(EN, 0);
}

void loop() {
  if(digitalRead(MOVEMENT) == 1 && currentState == 0)
  {
    currentState = 1;
    Serial.println("Movement detected");
    
  }
  else if(digitalRead(MOVEMENT) == 0)
  {
    currentState = 0;
  }
  Serial.println(digitalRead(MOVEMENT));
  delay(1000);
  

}
