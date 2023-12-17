#include <avr/wdt.h>
#define TIMEOUT WDTO_8S
char keyin;
volatile char flag;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("系統重啟");
  Serial.println("請輸入字元:");
  flag = 0;
  wdt_enable(TIMEOUT);
  WDTCSR |= (1 << WDIE);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0){
    keyin = Serial.read();
    if(keyin == "x") {flag=1; while(flag);}
    else {
      Serial.println(String("請輸入字元為")+String(keyin));
    }
  }
  wdt_reset();
  // asm("WDR");
}

void WDT_setup() {
  cli();
  asm("WDR");
  WDTCSR |= _BV(WDCE);
  WDTCSR |= _BV(WDIE) | _BV(WDP3) | _BV(WDP0);
  sei();
}
