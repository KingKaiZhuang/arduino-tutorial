#include <TimerOne.h>

#define LED_PIN 7           // LED接腳
#define BUTTON_PIN 2         // 按鈕接腳，用於外部中斷
#define BLINK_FAST 200000    // 快速閃爍的時間間隔（微秒）
#define BLINK_SLOW 700000    // 慢速閃爍的時間間隔（微秒）

volatile bool blinkFast = true; // 閃爍模式標誌，初始設為快速閃爍

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP); // 使用內部上拉電阻
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), toggleBlinkSpeed, FALLING);

  Timer1.initialize(blinkFast ? BLINK_FAST : BLINK_SLOW); 
  Timer1.attachInterrupt(toggleLED); // 每個間隔切換LED狀態
}

void loop() {
  // 主迴圈保持空白
}

void toggleBlinkSpeed() {
  blinkFast = !blinkFast; // 切換閃爍模式
  Timer1.setPeriod(blinkFast ? BLINK_FAST : BLINK_SLOW); // 更新閃爍間隔
}

void toggleLED() {
  digitalWrite(LED_PIN, digitalRead(LED_PIN) ^ 1); // 切換LED狀態
}
