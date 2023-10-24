/*** 範例8.4.6(WDT範例-1) ***/
#include <avr/wdt.h>
#define TIMEOUT WDTO_4S        //定義WDT的timeout時間=4s
#define LED_PIN 13
char keyin;

/***************************************************
 * setup
 ***************************************************/
void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN,OUTPUT);
  wdt_enable(TIMEOUT);         //啟用WDT，並設定timeout時間為4秒
  Serial.println("System Reboot ...... ");
  Serial.println("Input char");
}

/***************************************************
 * loop
 ***************************************************/
void loop() {
  if(Serial.available()>0) {   //若偵測到字元輸入
     digitalWrite(LED_PIN,HIGH);
     keyin=Serial.read();
     if(keyin=='x') while(1);  //如果keyin='x'，則進入無窮迴圈，LED恆亮
     else {                    //否則LED亮100ms後關閉
       delay(100);
       digitalWrite(LED_PIN,LOW);
     }
  }
  wdt_reset();                 //清除WDT的計數值，避免系統重啟
}
