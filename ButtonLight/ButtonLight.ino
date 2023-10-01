boolean state = false;
boolean buttonDown = false;
int buttonPressCount = 0;

void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  pinMode(7, INPUT_PULLUP); // 使用內部上拉電阻，按下為LOW，放開為HIGH
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(7) == LOW && !buttonDown) {
    Serial.print("Counter = ");Serial.println(buttonPressCount);
    buttonDown = true; // 表示按鈕被按下
    buttonPressCount++;

    // 根據按鈕按下次數執行不同的操作
    switch (buttonPressCount) {
      case 1:
        // 第一次按下，LED亮一秒後滅掉
        digitalWrite(13, HIGH);
        delay(1000);
        digitalWrite(13, LOW);
        break;
      case 2:
        // 第二次按下，LED亮滅交替一秒，重複兩次
        for (int i = 0; i < 2; i++) {
          digitalWrite(13, HIGH);
          delay(1000);
          digitalWrite(13, LOW);
          delay(1000);
        }
        break;
      case 3:
        // 第三次按下，LED亮滅交替一秒，重複三次
        for (int i = 0; i < 3; i++) {
          digitalWrite(13, HIGH);
          delay(1000);
          digitalWrite(13, LOW);
          delay(1000);
        }
        break;
      case 4:
        // 第四次按下，LED全滅五秒
        digitalWrite(13, LOW);
        delay(5000);
        buttonPressCount = 0;
        break;
    }
  } else if (digitalRead(7) == HIGH && buttonDown) {
    buttonDown = false; // 表示按鈕釋放
  }
}
