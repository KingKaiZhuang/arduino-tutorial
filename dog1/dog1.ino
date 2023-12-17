#include <avr/wdt.h>

#define TIMEOUT WDTO_4S  // 使用 WDTO_4S 來表示 4 秒的定時器
char keyin;

void setup() {
  Serial.begin(9600);
  wdt_enable(TIMEOUT);  // 使用 wdt_enable 來啟用看門狗定時器
  Serial.println("系統重啟");
  Serial.println("請輸入字元");
}

void loop() {
  if (Serial.available() > 0) {
    keyin = Serial.read();
    if (keyin == 'x') {
      Serial.println("系統四秒後重啟");
      while (1);
    } else {
      Serial.println(String("請輸入字元為") + String(keyin));
    }
  }
  wdt_reset();
}
