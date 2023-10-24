/*** 範例13.1.4(sleep範例-2) ***/
#include <avr/sleep.h>
#include <avr/wdt.h>
int WUP_cnt=0, num=0;
volatile int WDT_cnt=0;        //使用在WDT ISR的變數

/***************************************************
 * setup
 ***************************************************/
void setup() {
  Serial.begin(9600);
  Serial.println("Initial...");
  //---設定WDT
  WDTCSR|=_BV(WDCE)|_BV(WDE);  //將WDCE與WDE設為1，進入WDT設定模式
  WDTCSR=_BV(WDP3);            //設定WDP[3:0]=10002，timeout時間為4秒
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
  if(WDT_cnt%2==0) enterSleep();  //若WDT_cnt為偶數，則進入睡眠模式
  Serial.println(num++%1000);
  delay(100);
}

/***************************************************
 * 看門狗WDT中斷服務程式 
 ***************************************************/
ISR(WDT_vect) {
  WDT_cnt++;
}

/***************************************************
 * 進入睡眠模式
 ***************************************************/
void enterSleep() {
  Serial.println("Sleeping ..."); delay(100);
  sleep_enable();   //啟用睡眠功能
  sleep_cpu();      //進入睡眠狀態

  //---特別注意，此為喚醒後的程式執行點
  sleep_disable();  //停用睡眠功能
  Serial.print("Wake-up:");
  Serial.println(WUP_cnt++); delay(100);
}
