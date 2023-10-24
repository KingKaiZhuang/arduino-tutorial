/*** 範例10.5.2.B(UART範例-2 for UNO_B) ***/
#include <SoftwareSerial.h>
SoftwareSerial BSerial(2,3);  //宣告軟體UART，(Rx,Tx)=(D2,D3)
char ch;

/***************************************************
 * setup
 ***************************************************/
void setup() {
  Serial.begin(9600);   //硬體UART速度9600
  BSerial.begin(9600);  //軟體UART速度9600
}

/***************************************************
 * loop
 ***************************************************/
void loop() {
  if(Serial.available()>0) {  //如果PC端有輸入
    BSerial.print("[B]:");    //先送出[B]:
    while(1) {                //再送出所有輸入字元
      ch=Serial.read();
      if(ch==-1) break;
      else { BSerial.print(ch); Serial.print(ch); }
    }
  }

  if(BSerial.available()>0) {  //如果軟體UART有輸入
    while(1) {                 //在PC串列埠視窗印出所有讀到的字元
      ch=BSerial.read();
      if(ch==-1) break;
      else Serial.print(ch);
    }
  }
}
