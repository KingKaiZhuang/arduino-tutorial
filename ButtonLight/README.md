# Homework-1 Arduino按鈕控制LED燈（含去彈跳和多次按壓功能）

## 多次按壓功能

程式中使用 `buttonPressCount` 變數來追蹤按鈕按下的次數，並在 `loop()` 函數中使用 `switch` 敘述根據按下次數執行不同的操作。

- 第一次按下，LED亮一秒後滅掉。
- 第二次按下，LED亮滅交替一秒，重複兩次。
- 第三次按下，LED亮滅交替一秒，重複三次。
- 第四次按下，LED全滅五秒，然後重新計數。

## 程式碼說明
```
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
```              
# Arduino按鈕控制LED燈（含去彈跳）

這是一個簡單的Arduino程式，用於控制一個LED燈，當按鈕按下時，改變LED燈的狀態，並包含去彈跳的處理。

## 硬體需求

- Arduino板（例如Arduino Uno）
- 一個LED燈
- 一個按鈕
- 連接電纜

## 程式碼說明

程式碼包含了以下主要部分：

- `state` 和 `buttonUp` 兩個布林變數用於追蹤LED燈和按鈕的狀態。
- 在 `setup()` 函數中，設定了引腳13為輸出模式，用於控制LED燈，並啟用了引腳7的內部上拉電阻，確保按鈕未按下時處於高電位。
- `loop()` 函數中，通過檢測按鈕是否被按下，來切換LED燈的狀態，並使用去彈跳的技術處理按鈕彈跳。

### 去彈跳（Debounce）的處理

為了避免按鈕在物理接觸時可能造成的彈跳問題，我們在程式中實現了去彈跳的處理。這是通過以下方式實現的：

- 當按鈕被按下時，我們檢查按鈕是否處於未按下的狀態（`buttonUp == true`）。
- 如果按鈕處於未按下的狀態，我們切換LED燈的狀態，然後將按鈕的狀態設定為已按下。
- 當按鈕被釋放時，我們將按鈕的狀態設定為已釋放。
- 這樣可以確保只有在按鈕被按下且釋放後，才會切換LED燈的狀態，從而去除了彈跳所帶來的干擾。

## 用法

1. 將硬體按照硬體需求中的說明連接到Arduino板上。
2. 上傳這個程式到你的Arduino板。
3. 按下按鈕，LED燈的狀態將會切換，並且去除了彈跳問題的影響。

# Arduino按鈕控制LED燈

這是一個簡單的Arduino程式，用於控制一個LED燈，當按鈕按下時，改變LED燈的狀態。

## 程式碼說明

這個程式碼包含了以下主要部分：

```
boolean state = false;  // 這是一個布林變數，用於追蹤LED燈的狀態，最初設定為關閉
boolean buttonUp = true;  // 這是一個布林變數，用於追蹤按鈕是否處於未按下的狀態，最初設定為是

void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);  // 設定引腳13為輸出模式，用於控制LED燈
  digitalWrite(13, LOW);  // 將引腳13的輸出設定為低電位，關閉LED燈
  pinMode(7, INPUT);  // 設定引腳7為輸入模式，用於連接按鈕
  digitalWrite(7, HIGH);  // 將引腳7的內部上拉電阻啟用，確保按鈕未按下時處於高電位
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(7) != HIGH && buttonUp == true) {
    state = !state;  // 切換LED燈的狀態，從開啟變為關閉，或從關閉變為開啟
    digitalWrite(13, state);  // 將LED燈的狀態應用到引腳13，控制LED燈的亮滅
    buttonUp = false;  // 將按鈕的狀態設定為未按下
  } else if (digitalRead(7) == HIGH && buttonUp != true) {
    buttonUp = true;  // 當按鈕被釋放時，將按鈕的狀態設定為已釋放
  }
}
```






