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


## 作者

- 作者：鈞凱

如果你有任何問題或建議，請隨時聯絡我。
