/*** 範例13.2.4(power範例-1) ***/
#include <avr/wdt.h>
#include <avr/sleep.h>
#include <avr/power.h>
#define LedPin 13

/***************************************************
 * setup
 ***************************************************/
void setup() {
  //---盡可能停用耗電的模組
  ADCSRA=0;             //停用ADC轉換器
  ACSR |= (1<<ACD);     //停用AC類比比較器
  MCUSR |= (1<<PUD);    //停用Pull-up上拉模組
  DIDR0 = 0x3F;         //停用ADC pin腳的數位輸入緩衝器
  DIDR1 = 0x03;         //停用AC類比比較器的數位輸入緩衝器
  sleep_bod_disable();  //進入睡眠模式前停用BOD
  //---設定WDT
  WDTCSR|=_BV(WDCE)|_BV(WDE);  //將WDCE與WDE設為1，進入WDT設定模式
  WDTCSR=_BV(WDIE)|_BV(WDP3);  //設定WDT timeout=4s且為中斷模式
  //---設定睡眠模式
  set_sleep_mode (SLEEP_MODE_PWR_DOWN);  //設定power-down睡眠模式
}

/***************************************************
 * loop
 ***************************************************/
void loop() {  
  power_all_disable();  //停用所有的周邊模組  
  sleep_enable();       //開啟睡眠功能
  sleep_cpu();          //進入睡眠狀態
  
  //此為喚醒後的程式執行點
  sleep_disable();     //停用睡眠功能
  power_all_enable();  //致能所有的周邊模組
  LED_flash();         //LED閃爍10次
}

/***************************************************
 * LED_flash
 ***************************************************/
void LED_flash() {
  pinMode(LedPin,OUTPUT);
  for(int i=0;i<10;i++) {                    //LED閃爍10次
    digitalWrite(LedPin,HIGH); delay (50);
    digitalWrite(LedPin,LOW);  delay (50);
  }
}

/***************************************************
 * 看門狗WDT中斷服務程式 
 ***************************************************/
ISR(WDT_vect) {
  //empty
}
