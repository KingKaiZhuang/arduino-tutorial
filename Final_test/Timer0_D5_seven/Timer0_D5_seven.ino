void setup() {
    // 設置D5為輸出，用於PWM
    pinMode(5, OUTPUT);

    // 設置Timer0為快速PWM模式
    TCCR0A = 0;  // 清除TCCR0A寄存器
    TCCR0A |= (1 << WGM01) | (1 << WGM00);  // 設置快速PWM模式

    // 開啟非反相模式
    TCCR0A |= (1 << COM0B1);

    // 設置預分頻器為1024
    TCCR0B = 0;  // 清除TCCR0B寄存器
    TCCR0B |= (1 << CS02) | (1 << CS00);

    // 設置比較匹配值為3%的占空比
    OCR0B = 8;

    // 設置D6為輸出，並設置為高電平
    pinMode(6, OUTPUT);
    digitalWrite(6, HIGH);
}

void loop() {
    // 在這裡可以添加其他程式碼
}
