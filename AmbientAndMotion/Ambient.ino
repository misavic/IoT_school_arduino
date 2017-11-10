#include <Wire.h>

#define MOVEMENT 12
#define EN 47

#define RL2 53

int AMB_ADDR = 0x44; 


#define INT 10

byte a;
byte b;
unsigned int ambient_value = 0;
int d;

bool movementState = false;

void setup() {
  Serial.begin(9600);
  setup_ambient();
  setup_movement();
  
  
}

void loop() {
  loop_ambient(); 
  loop_movement(); 
 
  delay(3000);
 
}


void setup_ambient()
{
  Wire.begin();
  
  delay(100);

  Wire.beginTransmission(AMB_ADDR);

  Wire.write(0X01);
  Wire.write(0xC6);
  Wire.write(0x10);
   
  Wire.endTransmission();
   
  delay(1000);

   
  Wire.beginTransmission(AMB_ADDR);
  Wire.write(0X00);
  Wire.endTransmission();
}


void loop_ambient ()
{
  Wire.requestFrom(AMB_ADDR, 2);    // request 6 bytes from slave device #8 
  
  while(!Wire.available())
  {
  
  }

  a = Wire.read();
  b = Wire.read();

  ambient_value = (a << 8) + b;
 
  Serial.println(ambient_value);

  Serial.println();  
}


void setup_movement()
{
  pinMode(MOVEMENT, INPUT);
  pinMode(EN, OUTPUT);
  digitalWrite(EN, 0);
}


void loop_movement()
{
  if(digitalRead(MOVEMENT) == 1 && movementState == false)
  {
    movementState = true;
    Serial.println("Movement detected");
    
  }
  else if(digitalRead(MOVEMENT) == 0)
  {
    movementState = false;
  }
  Serial.println(digitalRead(MOVEMENT));
}

