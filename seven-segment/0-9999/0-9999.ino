#define seg7_a 2

int seg7_digit[10]={0xfc, 0x60, 0xda, 0xf2, 0x66, 0xb6, 0xbe, 0xe4, 0xfe, 0xf6};
int digits[4]={10,11,12,13};
int buttonPin = 1;

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
  digitalWrite(digits[0], HIGH);
  digitalWrite(digits[1], HIGH);
  digitalWrite(digits[2], HIGH);
  digitalWrite(digits[3], HIGH);
  pinMode(buttonPin, INPUT);
}
void show(int val){
  int mask0 = 0x80;
  int mask;
  for(int i=0; i<8; i++){
    mask = mask0 >> i;
    if(val&mask) digitalWrite(seg7_a+i, HIGH);
    else digitalWrite(seg7_a+i, LOW);
  }
}
void loop() {
  int x;
  int d;
  unsigned long t1;
  int toggle = 0;
  int cnt = 0;
  int buttonState; // 儲存按鈕狀態的變數
  //每0.1秒共陰極4位數七段顯示器顯示0000~9999
  
  buttonState = digitalRead(buttonPin);
    for(int x1=0;x1 < 10000;x1++){
    t1 = millis();
    while(millis()-t1 < 100){
        x = x1;
        // 千位數
        d = x / 1000;
        show(seg7_digit[d]);
        digitalWrite(10,LOW);
        delay(5);
        digitalWrite(10,HIGH);
        // 百位數
        x %= 1000;
        d = x /100;
        show(seg7_digit[d]);
        digitalWrite(11,LOW);
        delay(5);
        digitalWrite(11,HIGH);
        // 十位數
        x %= 100;
        d = x / 10;
        show(seg7_digit[d]);
        digitalWrite(seg7_a+7,HIGH);
        digitalWrite(12,LOW);
        delay(5);
        digitalWrite(12,HIGH);
        // 個位數
        x %= 10;
        d = x / 1;
        show(seg7_digit[d]);
        digitalWrite(13,LOW);
        delay(5);
        digitalWrite(13,HIGH);      
    }
    }
}


