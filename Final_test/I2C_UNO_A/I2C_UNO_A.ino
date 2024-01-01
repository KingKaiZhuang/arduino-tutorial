#include <Wire.h>

#define LED_PIN 13
#define I2C_SLAVE_ADDRESS 8

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  Wire.begin(); // 啟動I2C作為主設備
}

void loop() {
  Wire.requestFrom(I2C_SLAVE_ADDRESS, 1); // 從Slave請求1位元組的數據

  if (Wire.available()) {
    char c = Wire.read(); // 讀取收到的數據
    if (c == '1') {
      static int count = 0;
      digitalWrite(LED_PIN, !digitalRead(LED_PIN)); // 反轉LED狀態
      count = (count + 1) % 100; // 計數並保持在0~99
      Serial.print("Count: ");
      Serial.println(count);
    }
  }

  delay(100); // 稍微延遲以減少I2C流量
}
