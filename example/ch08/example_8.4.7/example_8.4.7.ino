/*** 範例8.4.7(WDT範例-2) ***/
#include <avr/wdt.h>
#define LED_PIN 13
char keyin;
volatile int flag;

/***************************************************
 * setup
 ***************************************************/
void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN,OUTPUT);
  WDT_setup();                  //設定WDT 
  Serial.println("System Start ...... ");
  Serial.println("Input char");
}

/***************************************************
 * loop
 ***************************************************/
void loop() {
  if(Serial.available()>0) {   //若偵測到字元輸入
     digitalWrite(LED_PIN,HIGH);
     keyin=Serial.read();
     flag=1;
     if(keyin=='x') while(flag); //如果keyin='x'，則進入無窮迴圈，LED恆亮
     else {                      //否則LED亮100ms後關閉
       delay(100);
       digitalWrite(LED_PIN,LOW);
     }
  }
  asm("WDR");   //送出組合語言指令"WDR"，清除WDT的計數值，避免系統重啟
}

/***************************************************
 * 看門狗WDT中斷服務程式 
 ***************************************************/
ISR(WDT_vect) {
  Serial.println("Timeout, back to loop without reboot");
  digitalWrite(LED_PIN,LOW);
  flag=0;
}

/***************************************************
 * 設定WDT
****************************************************/
void WDT_setup() {
  cli();                         //禁止中斷
  asm("WDR");                    //清除WDT的計數值
  //MCUSR &= ~_BV(WDRF);           //先將MCUSR暫存器中的WDRF位元清空為0
  WDTCSR |= _BV(WDCE)|_BV(WDE);  //同時將WDCE與WDE設為1，進入WDT設定模式
  WDTCSR = _BV(WDP3)|_BV(WDP0);  //設定WDP[3:0]=1001，timeout時間為8秒  
  WDTCSR |= (1<<WDE);           //設定WDIE=1,WDE=0，執行模式為中斷模式
  sei();                         //致能中斷
}

/***************************************************
 * 關閉WDT
****************************************************/
void WDT_off() {
  cli();                         //禁止中斷
  asm("WDR");                    //清除WDT的計數值
  MCUSR &= ~_BV(WDRF);           //先將MCUSR暫存器中的WDRF位元清空為0
  WDTCSR |= _BV(WDCE)|_BV(WDE);  //同時將WDCE與WDE設為1，進入WDT設定模式
  WDTCSR = 0;                    //全部清空為0
  sei();                         //致能中斷
}
