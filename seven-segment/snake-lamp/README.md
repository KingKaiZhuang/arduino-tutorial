# 7段顯示器蛇行燈

```arduino
#define seg7_a 2

int seg7_digit[8]={B11111010, B00111110, B11110110, B11011110, B01111010, B10011100, B11110110, B10001110};
int digits[4]={10,11,12,13};
void setup() {
  // put your setup code here, to run once:
  for(int i=0; i<8; i++)
  {
    pinMode(seg7_a+i, OUTPUT);
    digitalWrite(seg7_a+i, LOW);
  }
  for(int i=0; i<4; i++){
     pinMode(digits[i], OUTPUT);
    digitalWrite(digits[i], HIGH);
  }
  digitalWrite(digits[0], LOW);
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
  // put your main code here, to run repeatedly:
 for(int i=0; i<8; i++){
   show(seg7_digit[i]);
   delay(1000);
 }
}
```

### 引入和全域變數宣告

```cpp
#define seg7_a 2

// 七段顯示器要顯示的數字的二進制表示
int seg7_digit[8] = {B11111010, B00111110, B11110110, B11011110, B01111010, B10011100, B11110110, B10001110};

// 七段顯示器的數位引腳
int digits[4] = {10, 11, 12, 13};

```

- `#define seg7_a 2`：定義了 `seg7_a` 常數，它的值為2。這是用於控制七段顯示器的起始引腳。
- `int seg7_digit[8]`：定義了一個整數數組，其中包含8個二進制數字，用於表示要顯示在七段顯示器上的數字。每個數字都以二進制表示，例如 `B11111010` 表示數字0。
- `int digits[4]`：定義了一個整數數組，包含4個數位引腳的編號，用於選擇七段顯示器的哪一個數位（0到3）。

### `setup()` 函數

```cpp
void setup() {
  // 設定程式的初始化配置，只執行一次

  // 設定七段顯示器的每個段位的控制引腳
  for (int i = 0; i < 8; i++) {
    pinMode(seg7_a + i, OUTPUT);
    digitalWrite(seg7_a + i, LOW);
  }

  // 設定數位引腳，用於選擇七段顯示器的哪一個數位
  for (int i = 0; i < 4; i++) {
    pinMode(digits[i], OUTPUT);
    digitalWrite(digits[i], HIGH);
  }

  // 選擇第一個七段顯示器的數位
  digitalWrite(digits[0], LOW);
}

```

- `setup()` 函數是一個Arduino的初始化函數，它在程式開始運行時執行一次。
- 在這個函數中，首先設定了七段顯示器的每個段位的控制引腳，將它們設定為輸出模式並將它們的狀態設定為低電位，以確保七段顯示器的所有段位關閉。
- 接著，設定了數位引腳，用於選擇要顯示的七段顯示器的哪一個數位。這些引腳也設定為輸出模式，並將它們的狀態設定為高電位，最初選擇第一個數位。

### `show()` 函數

```cpp
// 函數用於顯示七段顯示器的某個數字
void show(int val) {
  int mask0 = B10000000;
  int mask;

  // 遍歷七段顯示器的每個段位
  for (int i = 0; i < 8; i++) {
    mask = mask0 >> i;

    // 進行位運算，決定是否點亮這個段位
    if (val & mask) {
      digitalWrite(seg7_a + i, HIGH);
    } else {
      digitalWrite(seg7_a + i, LOW);
    }
  }
}

```

- `show()` 函數用於控制七段顯示器的各個段位以顯示特定的數字。
- 在函數內部，定義了 `mask0` 和 `mask` 兩個整數變數，用於進行位運算。
- 透過迴圈遍歷了七段顯示器的每個段位