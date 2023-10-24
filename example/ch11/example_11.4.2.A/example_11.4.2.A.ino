/*** 範例11.4.2.A(I2C範例-2 for UNO_A) ***/
#include <Wire.h>
#define LedPin 13            //板載LED接腳固定為13
int cnt=0;

/***************************************************
 * setup
 ***************************************************/
void setup() {
  pinMode(LedPin,OUTPUT);    //設定內建LED(D13)接腳為輸出模式
  Wire.begin();              //將本裝置初始成master
}

/***************************************************
 * loop
 ***************************************************/
void loop() {
  if(cnt==10) cnt=0;
  digitalWrite(LedPin,HIGH);      //點亮LED一段時間後熄滅
  delay(1000-cnt*100);
  digitalWrite(LedPin,LOW);
  Wire.beginTransmission(8);      //向slave #8 傳送資料
  Wire.write(cnt);                //傳送cnt的值
  if(Wire.endTransmission()==0){  //如果成功結束
    while(1) {
      Wire.requestFrom(8,1);      //向slave #8請求1 byte資料
      while(!Wire.available());   //等待資料回傳
      if(Wire.read()==(cnt+1))    //如果slave回傳的值等於cnt+1
      { cnt++; break; }           //cnt=cnt+1，並跳出等待迴圈
    } 
  }
}
