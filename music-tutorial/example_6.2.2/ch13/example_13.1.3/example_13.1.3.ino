/*** 範例13.1.3(sleep範例-1) ***/
#include <avr/sleep.h>
#include <avr/wdt.h>
#define LedPin 13
int cnt=0;

/***************************************************
 * setup
 ***************************************************/
void setup() {
  Serial.begin(9600);
  Serial.println("Initial...");
  pinMode(LedPin,OUTPUT);
  //---設定WDT
  WDTCSR|=_BV(WDCE)|_BV(WDE);  //將WDCE與WDE設為1，進入WDT設定模式
  WDTCSR=_BV(WDP3)|_BV(WDP0);  //設定WDP[3:0]=1001，timeout時間為8秒
  WDTCSR|=_BV(WDIE);           //設定WDT為中斷模式
  //---設定睡眠模式
  set_sleep_mode (SLEEP_MODE_PWR_DOWN);  //設定power-down睡眠模式
  //---設定完成
  Serial.println("Initial complete."); delay(100);
}

/***************************************************
 * loop
 ***************************************************/
void loop() {
  sleep_enable();   //啟用睡眠功能
  sleep_cpu();      //進入睡眠狀態
  
  //---特別注意，此為喚醒後的程式執行點
  sleep_disable();  //停用睡眠功能
  Serial.print("Wake-up: "); Serial.println(cnt++); delay(100);
}

/***************************************************
 * WDT中斷服務程式 
 ***************************************************/
ISR(WDT_vect) {
  digitalWrite(LedPin,!digitalRead(LedPin));  //反轉LED現在的狀態 
}
