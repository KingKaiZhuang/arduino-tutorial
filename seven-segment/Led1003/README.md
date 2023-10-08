# 七段顯示器 單顆顯示數字1到9

```arduino
#define seg7_a 2

int seg7_digit[10]={0xfc, 0x60, 0xda, 0xf2, 0x66, 0xb6, 0xbe, 0xe4, 0xfe, 0xf6};
int digits[4]={10,11,12,13};
void setup() {
  for(int i=0; i<8; i++)
  {
    pinMode(seg7_a+i, OUTPUT);
    digitalWrite(seg7_a+i, LOW);
  }
  for(int i=0; i<4; i++){
     pinMode(digits[i], OUTPUT);
    digitalWrite(digits[i], HIGH);
  }
  digitalWrite(digits[3], LOW);
}
void show(int val){
  int mask0 = B10000000;
  int mask;
  for(int i=0; i<8; i++){
    mask = mask0 >> i;
    if(val&mask) digitalWrite(seg7_a+i, HIGH);
    else digitalWrite(seg7_a+i, LOW);
  }
}
void loop() {
 for(int i=0; i<10; i++){
   show(seg7_digit[i]);
   delay(1000);
 }
}
```

### 程式說明:

```cpp
#define seg7_a 2

```

這裡定義了 `seg7_a` 的值為2，它是一個用來表示七段顯示器的引腳的常數。

### 數字段位設定

```cpp
int seg7_digit[10] = {
  0xfc, 0x60, 0xda, 0xf2, 0x66, 0xb6, 0xbe, 0xe4, 0xfe, 0xf6
};

```

這個陣列 `seg7_digit` 包含了0到9的數字的七段顯示器段位設定。每個數字的段位被表示為一個十六進位數。

### 數位選擇引腳設定

```cpp
int digits[4] = {10, 11, 12, 13};

```

這個陣列 `digits` 包含了四個引腳的編號，用來選擇七段顯示器的數位（digit）。其中一個引腳設定為低電位，其他引腳設定為高電位，用於切換顯示的數位。

### `setup()` 函數

```cpp
void setup() {
  for (int i = 0; i < 8; i++) {
    pinMode(seg7_a + i, OUTPUT);
    digitalWrite(seg7_a + i, LOW);
  }
  for (int i = 0; i < 4; i++) {
    pinMode(digits[i], OUTPUT);
    digitalWrite(digits[i], HIGH);
  }
  digitalWrite(digits[3], LOW);
}

```

在 `setup()` 函數中，我們進行了一些初始設定：

- 將七段顯示器的段位引腳設定為輸出模式，並將它們設定為低電位，以關閉所有的段。
- 將數位選擇引腳設定為輸出模式，並將它們設定為高電位，其中一個引腳設定為低電位，以準備顯示數字。

### `show()` 函數

```cpp
void show(int val) {
  int mask0 = B10000000;
  int mask;
  for (int i = 0; i < 8; i++) {
    mask = mask0 >> i;
    if (val & mask) {
      digitalWrite(seg7_a + i, HIGH);
    } else {
      digitalWrite(seg7_a + i, LOW);
    }
  }
}

```

`show()` 函數用來顯示七段顯示器的數字。它接受一個十六進位的值 `val` 作為參數，並根據這個值來設定每個段位的狀態。具體來說，它使用位運算來檢查 `val` 中的每一位，如果某一位為1，則將對應的段位引腳設定為高電位，否則設定為低電位。

### `loop()` 函數

```cpp
void loop() {
  for (int i = 0; i < 10; i++) {
    show(seg7_digit[i]);
    delay(1000);
  }
}

```

`loop()` 函數是主要的程式循環。它用來連續顯示 `seg7_digit` 陣列中的數字。在這個例子中，它顯示0到9的數字，每個數字顯示1秒（1000毫秒），然後切換到下一個數字。