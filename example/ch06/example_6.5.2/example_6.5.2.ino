/*** 範例6.5.2(SG90伺服馬達) ***/
#include <Servo.h>    //引用Arduino內建的Servo程式庫
Servo myServo;        //宣告Servo物件

void setup() {
  myServo.attach(8);  //設定伺服馬達的訊號接腳為 pin8
}

void loop() {
  myServo.write(0);   //旋轉到0度，歸零
  delay(1000);
  myServo.write(90);  //旋轉到90度
  delay(1000);
  myServo.write(180); //旋轉到180度
  delay(1000);
}
