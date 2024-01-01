#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT11
#define BUTTON_PIN 6

DHT dht(DHTPIN, DHTTYPE);
bool lastButtonState = HIGH;      // 上一次按鈕的狀態
bool readingTaken = false;        // 是否已經取得讀數

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.begin(9600);
  dht.begin();
  Serial.println(F("DHT11 test with button debouncing!"));
}

void loop() {
  bool currentButtonState = digitalRead(BUTTON_PIN);

  // 檢查按鈕是否從未按下變為按下
  if (lastButtonState == HIGH && currentButtonState == LOW) {
    if (!readingTaken) {
      measureTemperatureAndHumidity();
      readingTaken = true;  // 設定已取得讀數
    }
  }

  // 當按鈕釋放時重設readingTaken標誌
  if (currentButtonState == HIGH) {
    readingTaken = false;
  }

  lastButtonState = currentButtonState; // 更新按鈕狀態
}

void measureTemperatureAndHumidity() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.println(" *F");
}
