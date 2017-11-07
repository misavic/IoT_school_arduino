
int delayTime = 200;
int val = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  val = analogRead(A2);
  
  Serial.println(promileClc(val)); 
 
  Serial.println();
  delay(delayTime);
  delay(2000);
}


String promileClc(int  val)
{
  Serial.println(val);

  if(val < 615) {
    return "Level of alcohol < 0.2 promille ";
  }
  else if(val < 680) {
    return "Level of alcohol between 0.2 and 0.3 Promille";
  }
  else if(val < 721) {
    return "Level of alcohol between 0.3 and 0.4 Promille";
  }
  else if(val < 753) {
    return "Level of alcohol between 0.4 and 0.5 Promille";
  }
  else if(val < 777) {
    return "Level of alcohol between 0.5 and 0.6 Promille";
  }
  else if(val < 811) {
    return "Level of alcohol between 0.6 and 0.8 Promille";
  }
  else if(val < 835) {
    return "Level of alcohol between 0.8 and 1.0 Promille";
  }
  else if(val < 853) {
    return "Level of alcohol between 1.0 and 1.2 Promille";
  }
  else if(val < 873) {
    return "Level of alcohol between 1.2 and 1.5 Promille";
  }
  else if(val < 888) {
    return "Level of alcohol between 1.5 and 1.8 Promille";
  }
  else {
    return "Level of alcohol > 1.8";
  }
  
}

