#define TRIG 7
#define ECHO 6

#define BLUE 3
#define RED 10
#define GREEN 11
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
 
  
}

void loop() {
  
  long duration, distance;
  digitalWrite(TRIG, LOW);  
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);

  delayMicroseconds(10); 
  digitalWrite(TRIG, LOW);

  duration = pulseIn(ECHO, HIGH);
  distance = (duration/2) / 29.1;
  Serial.println(distance);
  if (distance < 50) {  
    
    //digitalWrite(RED,HIGH);
    analogWrite(RED, 255 - distance*5);
    if(distance > 10)
    {
    analogWrite(GREEN,distance*5);
    }
    else
    {
      analogWrite(GREEN, 0);
    }
  }
  else {
    digitalWrite(RED,LOW);
    digitalWrite(GREEN,HIGH);
  }
  delay(10);

  
}
