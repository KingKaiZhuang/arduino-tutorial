/*** 範例11.4.2.B(I2C範例-2 for UNO_B) ***/
#include <Wire.h>
#define LedPin 13                //板載LED接腳固定為13
int flag=0, cnt=0;

/***************************************************
 * setup
 ***************************************************/
void setup() {
  pinMode(LedPin,OUTPUT);        //設定內建LED(D13)接腳為輸出模式
  Wire.begin(8);                 //將本裝置初始成slave，且位址為8
  Wire.onReceive(receiveEvent);  //註冊onReceive要執行的函式
  Wire.onRequest(requestEvent);  //註冊onRequest要執行的函式
}

/***************************************************
 * loop
 ***************************************************/
void loop() {
  if(flag==1) {                //flag==1表示有從master接收到資料
    digitalWrite(LedPin,HIGH); //點亮LED一段時間後熄滅
    delay(1000-cnt*100);
    digitalWrite(LedPin,LOW);
    cnt++;  flag=0;
  }
}

/***************************************************
 * receiveEvent
 ***************************************************/
void receiveEvent(int bytes) {
  while(!Wire.available());
  cnt=Wire.read();
  flag=1;           //從master接收到資料，設定flag=1
}

/***************************************************
 * requestEvent
 ***************************************************/
void requestEvent( ) {
  Wire.write(cnt);  //master有請求request時，就傳回cnt
}
