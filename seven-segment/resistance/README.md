- 電阻值顯示
    1. **定義 (Macro Definitions):**
        
        ```cpp
        #define seg7_a 2
        #define Vin A0
        
        ```
        
        這部分程式碼使用宏定義，將 `seg7_a` 設定為數字2，它用於指定七段顯示器的引腳；同時，將 `Vin` 設定為 `A0`，這是用來讀取模擬數位電壓的引腳。
        
    2. **位元組陣列 (Byte Arrays):**
        
        ```cpp
        int seg7_digit[10] = {0xfc, 0x60, 0xda, 0xf2, 0x66, 0xb6, 0xbe, 0xe4, 0xfe, 0xf6};
        
        ```
        
        這個陣列包含了0到9的七段顯示器位元組設置，以便在七段顯示器上顯示相應的數字，這部分與之前的程式相同。
        
    3. **引腳定義 (Pin Definitions):**
        
        ```cpp
        int digits[4] = {10, 11, 12, 13};
        
        ```
        
        這個陣列定義了七段顯示器的8個段 (a到g以及小數點)，它們分別對應到 Arduino 的引腳 10 到 13。這部分也與之前的程式相同。
        
    4. **`setup` 函數:**
        
        ```cpp
        void setup() {
          // 設置段和位元組的引腳為輸出，並初始化為低電平（關閉）。
          for (int i = 0; i < 8; i++) {
            pinMode(seg7_a + i, OUTPUT);
            digitalWrite(seg7_a + i, LOW);
          }
          for (int i = 0; i < 4; i++) {
            pinMode(digits[i], OUTPUT);
            digitalWrite(digits[i], HIGH);
          }
          // 開啟串口通信，設定波特率為9600，以便通過Serial Monitor顯示數據。
          Serial.begin(9600);
          // 最初將4個位元組的引腳都設置為高電平（開啟）。
          digitalWrite(digits[0], HIGH);
          digitalWrite(digits[1], HIGH);
          digitalWrite(digits[2], HIGH);
          digitalWrite(digits[3], HIGH);
        }
        
        ```
        
        `setup` 函數設置程式的初始狀態，其中一個新的功能是啟用了串口通信，以便通過Serial Monitor來顯示數據。同樣，七段顯示器的引腳被設置為輸出並初始化為關閉。
        
    5. **自訂 `show` 函數:**
        
        ```cpp
        void show(int val) {
          int mask0 = 0x80;
          int mask;
          for (int i = 0; i < 8; i++) {
            mask = mask0 >> i;
            if (val & mask) digitalWrite(seg7_a + i, HIGH);
            else digitalWrite(seg7_a + i, LOW);
          }
        }
        
        ```
        
        這部分與之前的程式碼相同，自訂的 `show` 函數用於設置七段顯示器的各個段的狀態。
        
    6. **`loop` 函數:**
        
        ```cpp
        void loop() {
          int d, x, t0;
          float vr = analogRead(Vin) * 5.0 / 1024;
          Serial.println(vr);
          x = vr * 1000;
          // 千位數
          d = x / 1000;
          show(seg7_digit[d]);
          digitalWrite(9, HIGH);
          digitalWrite(10, LOW);
          delay(5);
          digitalWrite(10, HIGH);
          // 百位數
          x %= 1000;
          d = x / 100;
          show(seg7_digit[d]);
          digitalWrite(11, LOW);
          delay(5);
          digitalWrite(11, HIGH);
          // 十位數
          x %= 100;
          d = x / 10;
          show(seg7_digit[d]);
          digitalWrite(12, LOW);
          delay(5);
          digitalWrite(12, HIGH);
          // 個位數
          x %= 10;
          d = x / 1;
          show(seg7_digit[d]);
          digitalWrite(13, LOW);
          delay(5);
          digitalWrite(13, HIGH);
        }
        
        ```
        
        在 `loop` 函數中，它執行以下操作：
        
        - 讀取從模擬引腳 `Vin` 讀取的數位電壓，然後將其轉換為實際電壓值（0到5V之間）。
        - 使用 `Serial.println(vr)` 將電壓值輸出到串口，以便在Serial Monitor上檢視。
        - 透過計算將電壓值乘以1000，然後將結果存儲在 `x` 中，接下來顯示它的千位、百位、十位和個位數字。
        - 通過控制位元組的引腳來啟用不同的位元組，使用 `delay(5)` 控制每個位元組的顯示時間。
    
    這個程式的目的是讀取模擬電壓值並將其顯示在七段顯示器上，同時通過串口通信將電壓值輸出到Serial Monitor。