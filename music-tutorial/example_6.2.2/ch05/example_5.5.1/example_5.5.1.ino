/*** 範例5.5.1(一位數七段顯示器) ***/
#include "seg7.h"
#define Button 10  //指定按鈕開關的接腳為D10
int num=0;

void setup() {
  pinMode(Button,INPUT_PULLUP); //設定Button接腳，並啟用內建的上拉電阻
  seg7x1_init(2);  //初始化七段顯示器，第一隻接腳為D2，到D9
  seg7x1_show(0);  //顯示數字0
}

void loop() {
  if(digitalRead(Button)==LOW) { //讀取Button接腳的電位是否為LOW
    num=++num%10;          //若是，就代表按下開關，num+1後取10的餘數
    seg7x1_show(num);      //顯示數字num
    delay(300);            //避免持續累加
  }
}
