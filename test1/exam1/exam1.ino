#include "HCSR04.h"
#define Trig 2
#define Echo 3
#define Buzzer 4
HCSR04 myHC(Trig, Echo);
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(Buzzer, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int range = myHC.dist();
  Serial.print("Range="); Serial.println(range);
  if(range>50){
    digitalWrite(Buzzer, LOW);
    // noTone(Buzzer);
  }
  else if(range>30){
    for(int i=0;i<2;i++){
      // 有緣蜂鳴器
      digitalWrite(Buzzer, HIGH);
      delay(1000/2/2);
      digitalWrite(Buzzer, LOW);
      delay(1000/2/2);
      // 無緣蜂鳴器
      /*tone(腳位,頻率,時間)
      tone(Buzzer,2000,1000/2/2);
      delay(1000/2/2);
      */
    }
    delay(500);
  }
  else if(range>10) {
    for(int i=0;i<6;i++){
      digitalWrite(Buzzer, HIGH);
      delay(1000/6/2);
      digitalWrite(Buzzer, LOW);
      delay(1000/6/2);
      // 無緣蜂鳴器
      /*
      tone(Buzzer,2000,1000/2/2);
      delay(1000/2/2);
      */
    }
    delay(500);
  }
  else{
    // 有緣蜂鳴器
    digitalWrite(Buzzer,HIGH);
    // 無緣蜂鳴器
    /*
    tone(Buzzer,2000,1000/2/2);
    delay(1000/2/2);
    */
  }
}