#include <Wire.h>

#define BUTTON_PIN 2
#define I2C_SLAVE_ADDRESS 8

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Wire.begin(I2C_SLAVE_ADDRESS); // 啟動I2C作為從設備
  Wire.onRequest(requestEvent); // 註冊I2C請求事件
}

void loop() {
  // 留空
}

void requestEvent() {
  static bool lastButtonState = HIGH;
  bool currentButtonState = digitalRead(BUTTON_PIN);

  if (currentButtonState == LOW && lastButtonState == HIGH) {
    Wire.write('1'); // 當按鈕被按下，發送'1'
  } else {
    Wire.write('0'); // 否則發送'0'
  }

  lastButtonState = currentButtonState;
}
