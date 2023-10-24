/*** 範例10.5.2.A(UART範例-2 for UNO_A) ***/
#include <SoftwareSerial.h>
SoftwareSerial ASerial(2,3);  //宣告軟體UART，(Rx,Tx)=(D2,D3)
char ch;

/***************************************************
 * setup
 ***************************************************/
void setup() {
  Serial.begin(9600);   //硬體UART速度9600
  ASerial.begin(9600);  //軟體UART速度9600
}

/***************************************************
 * loop
 ***************************************************/
void loop() {
  if(Serial.available()>0) {  //如果PC端有輸入
    ASerial.print("[A]:");    //先送出[A]:
    while(1) {                //再送出所有輸入字元
      ch=Serial.read();
      if(ch==-1) break;
      else { ASerial.print(ch); Serial.print(ch); }
    }
  }

  if(ASerial.available()>0) {  //如果軟體UART有輸入
    while(1) {                 //在PC串列埠視窗印出所有讀到的字元
      ch=ASerial.read();
      if(ch==-1) break;
      else Serial.print(ch);
    }
  }
}
