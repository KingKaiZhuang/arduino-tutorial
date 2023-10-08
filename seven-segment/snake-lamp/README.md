# 7段顯示器蛇行燈

### 定義七段顯示器相關常數和變數

```cpp
#define seg7_a 2

int seg7_digit[8]={B10000000, B01000000, B00000010 , B00001000, B00010000, B00100000, B00000010, B00000100 };
int digits[4]={10,11,12,13};

```

- `#define seg7_a 2`：這是一個預處理器指令，將 `seg7_a` 定義為2，表示七段顯示器的起始引腳連接到Arduino的第2個數位引腳。
- `int seg7_digit[8]`：這是一個整數數組，包含了8個元素，每個元素代表一個七段顯示器上的數字或字符的位模式。每個元素都以 `B` 開頭，後面跟著8位的二進制數字，表示七段顯示器的各段位是否應該點亮。
- `int digits[4]`：這是另一個整數數組，包含了4個元素，每個元素代表控制七段顯示器的四個數位（digits）的引腳。

### 區塊 2: 設定Arduino引腳和初始化

```cpp
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
  digitalWrite(digits[3], LOW);
}

```

- `void setup()`：這是Arduino的設定函數，在程式啟動時運行一次。
- `pinMode(seg7_a+i, OUTPUT)`：在迴圈中，將七段顯示器引腳設定為輸出模式，並將其初始狀態設定為低電位，以確保七段顯示器段位最初都是熄滅的。
- `pinMode(digits[i], OUTPUT)`：同樣在迴圈中，將控制數位的引腳設定為輸出模式，並將其初始狀態設定為高電位。
- `digitalWrite(digits[3], LOW)`：將最後一個數位引腳設定為低電位，用於選擇七段顯示器的特定數位。

### 區塊 3: 定義 `show` 函數

```cpp
void show(int val){
  int mask0 = B10000000;
  int mask;
  for(int i=0; i<8; i++){
    mask = mask0 >> i;
    if(val&mask) digitalWrite(seg7_a+i, HIGH);
    else digitalWrite(seg7_a+i, LOW);
  }
}

```

- `void show(int val)`：這是一個自定義函數，用於根據輸入的 `val` 值來控制七段顯示器的各段位。
- `int mask0 = B10000000;`：定義了一個位掩碼 `mask0`，它的二進制表示是 `10000000`，用於遍歷 `val` 的每一位。
- `int mask;`：定義了另一個整數變數 `mask`，用於存儲位掩碼的值。
- `for(int i=0; i<8; i++)`：這是一個迴圈，遍歷了 `val` 的8個位。
- `mask = mask0 >> i;`：在迴圈中，使用右位移運算將 `mask0` 向右移動 `i` 位，然後將結果存儲在 `mask` 變數中，以便逐位檢查 `val`。
- `if(val&mask)`：在每次迴圈迭代中，使用位運算 `val & mask` 來檢查 `val` 中的每個位。如果 `val` 中的某個位和 `mask` 中的對應位都是1，則執行下一行程式碼。
- `digitalWrite(seg7_a+i, HIGH)`：如果條件成立，則將相應的七段顯示器段位引腳設定為高電位，以點亮該段位。

### 區塊 4: 主循環 `loop`

```cpp
void loop() {
  // put your main code here, to run repeatedly:
 for(int i=0; i<8; i++){
   show(seg7_digit[i]);
   delay(100);
 }
}

```

- `void loop()`：這是Arduino的主循環函數，在設備啟動後會一直運行。
- `for(int i=0; i<8; i++)`：這是一個迴圈，遍歷了 `seg7_digit` 數組中的8個元素。
- `show(seg7_digit[i])`：在每次迴圈迭代中，調用 `show` 函數，並傳遞 `seg7_digit` 數組中的元素作為參數。這將使七段顯示器顯