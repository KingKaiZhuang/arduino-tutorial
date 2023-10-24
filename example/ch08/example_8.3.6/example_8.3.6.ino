/*** 範例8.3.6(Timer範例-2:4位數7段顯示器，使用Timer2) ***/
#include "seg7.h"  
#define Button A5        //指定按鈕開關的pin腳為A5
int digit[4]={0,0,0,0};  //宣告int陣列來儲存4個數字，初值皆為0
volatile int index=0;    //使用在ISR中記錄數字的index
int num;

/***************************************************
 * setup
****************************************************/
void setup() {
  Serial.begin(9600);           //設定串列埠傳輸速率為9600 bps
  pinMode(Button,INPUT_PULLUP); //設定Button接腳，並啟用內建的上拉電阻
  seg7x4_init(2);               //初始化四位數七段顯示器，第一隻接腳為D2
  randomSeed(analogRead(A0));   //產生亂數種子
  setupTimer2();                //設定定時器Timer2
}

/***************************************************
 * loop
****************************************************/
void loop() {
  if(digitalRead(Button)==LOW) {
    //若按下button，產生0-9999的亂數
    num=random(10000);        //產生0-9999的亂數
    Serial.println(num);      //印出亂數
    digit[3]=num/1000;        //取得第3位數字
    digit[2]=(num%1000)/100;  //取得第2位數字
    digit[1]=(num%100)/10;    //取得第1位數字
    digit[0]=num%10;          //取得第0位數字
    delay(200);               //避免連續觸發
  }
}

/***************************************************
 * Timer2的COMPA中斷服務程式，每5ms產生一次中斷
****************************************************/
ISR(TIMER2_COMPA_vect) {
  seg7x4_show(index,digit[index]);  //秀出第index位數字
  index=++index%4;                  //index=(index+1) mod 4，
}

/***************************************************
 * 設定定時器
****************************************************/
void setupTimer2() {
  //---step1:初始暫存器
   TCCR2A=0;              //設定初始值為0
   TCCR2B=0;
   TCNT2=0;

  //---step2:設定CTC模式
   TCCR2A |= _BV(WGM21);  //將1左移WGM21=1個位元，進行位元OR邏輯運算

  //---step3:設定預先除頻倍數prescaler與正確的TOP上限值
  //在prescaler=1024，TOP=156的設定下，Timer2會固定每5ms產生一次中斷
   TCCR2B |= B00000111;   //prescaler=1024   
   OCR2A=78;              //設定TOP=156

  //---step4:致能對應的中斷
   TIMSK2 |= _BV(OCIE2A); //致能輸出比較中斷A
}
