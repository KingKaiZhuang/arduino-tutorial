/*** 範例6.5.3(直流馬達) ***/
#define motorPin 5  //設定直流馬達的訊號接腳為pin5       
int duty;           //duty cycle 0-255
void setup() {
  Serial.begin(9600);
  pinMode(motorPin, OUTPUT);  
}

void loop() {
  for(duty=50;duty<=150;duty+=50)  {  //漸快，間隔2秒
    Serial.println(duty);
    analogWrite(motorPin, duty);
    delay(2000);                      
  }
  
  for(duty=200;duty>=100;duty-=50)  {  //漸慢，間隔2秒
    Serial.println(duty);
    analogWrite(motorPin, duty);
    delay(2000);  
  }
}
