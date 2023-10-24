/*** 範例5.5.2(四位數七段顯示器) ***/
#include "seg7.h"
#define Button A5               //指定按鈕開關的pin腳為A5
int num=0, d3, d2, d1, d0;

void setup() {
  Serial.begin(9600);           //設定串列埠傳輸速率為9600 bps
  pinMode(Button,INPUT_PULLUP); //設定Button接腳，並啟用內建的上拉電阻
  seg7x4_init(2);               //初始化四位數七段顯示器，第一隻接腳為D2
  randomSeed(analogRead(A0));   //產生亂數種子
}

void loop() {  
  if(digitalRead(Button)==LOW) {
    //若按下button，產生0~9999的亂數
    num=random(10000);
    Serial.println(num);  //印出亂數
    delay(200);           //避免連續觸發
  } 

  d3=num/1000;        //取得第3位數字
  seg7x4_show(3,d3);  //秀出第3位數字
  delay(5);           //延遲5ms

  d2=(num%1000)/100;  //取得第2位數字
  seg7x4_show(2,d2);  //秀出第2位數字
  delay(5);           //延遲5ms

  d1=(num%100)/10;    //取得第1位數字
  seg7x4_show(1,d1);  //秀出第1位數字
  delay(5);           //延遲5ms

  d0=num%10;          //取得第0位數字
  seg7x4_show(0,d0);  //秀出第0位數字
  delay(5);           //延遲5ms
}
