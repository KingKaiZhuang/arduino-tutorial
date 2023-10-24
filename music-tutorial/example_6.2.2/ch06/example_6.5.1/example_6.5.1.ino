/*** 範例6.5.1(28BYJ-48步進馬達) ***/
#include <Stepper.h>             //引用Arduino內建的Stepper程式庫
#define stepsPerRevolution 2048  //設定28BYJ-48轉一圈的step數  
Stepper myStepper(stepsPerRevolution, 4, 6, 5, 7);
//宣告Stepper物件，需指定每圈的步數及接線的ping腳，
//特別注意:因為28BYJ-48的接線順序與Stepper程式庫定義的不同，
//所以接腳5,6的指定順序要對調才能正確動作

void setup() {
  myStepper.setSpeed(5);  //設定轉動速度=5(RPM,每分鐘5圈)
}

void loop() {
  myStepper.step(2048);   //正轉(順時針)1圈
  delay(2000);
  myStepper.step(-1024);  //反轉(逆時針)0.5圈
  delay(2000);
}
