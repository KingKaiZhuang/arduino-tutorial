/*** 範例6.4.1(HC-SR04超音波距離感測器) ***/
#include "HCSR04.h"
#define TrigPIN 3              //定義發送端Trig pin腳
#define EchoPIN 2              //定義接收端Echo pin腳
HCSR04 myHC(TrigPIN,EchoPIN);  //宣告HCSR04物件

void setup() {
  Serial.begin(9600);
}

void loop() {
  int range = myHC.dist();  //讀取距離資料
  Serial.print("Range="); Serial.println(range);   //印出距離數值
  delay(2000);              //延遲2秒
}
