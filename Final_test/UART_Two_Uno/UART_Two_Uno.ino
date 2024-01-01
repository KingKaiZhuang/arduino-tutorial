#define BUTTON_PIN 5
#define LED_PIN 13
#define DEBOUNCE_DELAY 50 // 按鈕去彈跳的延遲時間，單位為毫秒

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP); // 使用內部上拉電阻
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);        // 初始化時熄滅LED
  Serial.begin(9600);                // 開始串列通信
}

void loop() {
  static unsigned long lastDebounceTime = 0; // 上一次切換狀態的時間
  static int lastButtonState = HIGH;        // 按鈕的上一次狀態
  int reading = digitalRead(BUTTON_PIN);    // 當前讀取的按鈕狀態

  // 檢查按鈕狀態是否有變化
  if (reading != lastButtonState) {
    lastDebounceTime = millis(); // 重置去彈跳計時器
  }

  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
    // 如果按鈕狀態穩定超過去彈跳時間
    if (reading == LOW) { // 檢查按鈕是否被穩定按下
      Serial.write('1');  // 向另一塊板發送信號
      delay(10);          // 防止連續發送
    }
  }

  lastButtonState = reading; // 更新按鈕狀態

  if (Serial.available() > 0) {
    if (Serial.read() == '1') { // 接收到信號
      digitalWrite(LED_PIN, HIGH); // 點亮LED
      delay(3000);                 // 等待三秒
      digitalWrite(LED_PIN, LOW);  // 關閉LED
    }
  }

  // 清空串列通信緩存
  while (Serial.available() > 0) {
    Serial.read();
  }
}
