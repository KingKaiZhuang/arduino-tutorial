#include "HCSR04.h"
#define Trig 3
#define Echo 4
#define Buzzer 5
HCSR04 myHc(Trig,Echo);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(Buzzer,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int range = myHc.dist();
  Serial.print("Range=");Serial.println(range);
  if(range<30){
    digitalWrite(Buzzer,HIGH);
    delay(200);
    digitalWrite(Buzzer,LOW);
    delay(50);
  }else if(range<60){
    digitalWrite(Buzzer,HIGH);
    delay(900);
    digitalWrite(Buzzer,LOW);
    delay(100);
  }
}
