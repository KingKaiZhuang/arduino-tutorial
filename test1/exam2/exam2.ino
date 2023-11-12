#define seg7_a 2
//使用4位數7段顯示器，在最右邊之位數(個位數)每秒依序顯示0~9數字
//共陰極七段顯示器顯示值與a,b,c,d,e,f,g,h 等8顆LED HI/LO設定關係
int seg7_digit[10] = { 0xfc, 0x60, 0xda, 0xf2, 0x66, 0xb6, 0xbe, 0xe4, 0xfe, 0xf6 };
//4位數7段顯示器最左邊到最右邊之位數(即位數1~4)之Arduino控制腳位(10~13)
int digits[4] = { 10, 11, 12, 13 };

#define BtnPin A0

int cnt;
int flag;
int lastDebounceTime;  //目前去彈跳起始時間
int debounceDelay;     //去彈跳延遲時間
int btnState;          //目前按鍵狀態
int lastBtnState = HIGH;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  for (int i = 0; i < 8; i++) {
    pinMode(seg7_a + i, OUTPUT);    //設定腳位2~9對應到七段顯示器之a,b,c,d,e,f,g,h
    digitalWrite(seg7_a + i, LOW);  //共陰極滅掉
  }
  for (int i = 0; i < 4; i++) {
    pinMode(digits[i], OUTPUT);     //設定七段顯示器位數1,2,3,4由arduino腳10,11,12,13控制
    digitalWrite(digits[i], HIGH);  //共陰極滅掉
  }
  pinMode(BtnPin, INPUT_PULLUP);
  cnt = 0;
  flag = 0;
  lastDebounceTime = 0;
  debounceDelay = 50;
}

void show(int val) {
  int mask0 = 0x80;
  int mask;
  int val2 = seg7_digit[val];
  for (int i = 0; i < 8; i++) {
    mask = mask0 >> i;
    if (val & mask) digitalWrite(seg7_a + i, HIGH);
    else digitalWrite(seg7_a + i, LOW);
  }
}
void disp(int val) {
  long t0 = millis();
  while (millis() - t0 < 100) {
    int x = val;
    int d;
    //顯示千位數
    d = x / 1000;
    show(seg7_digit[d]);
    digitalWrite(digits[0], LOW);
    delay(5);
    digitalWrite(digits[0], HIGH);
    //顯示百位數
    x = x % 1000;
    d = x / 100;
    show(seg7_digit[d]);
    digitalWrite(digits[1], LOW);
    delay(5);
    digitalWrite(digits[1], HIGH);
    //十位數
    x = x % 100;
    d = x / 10;
    show(seg7_digit[d]);
    digitalWrite(digits[2], LOW);
    delay(5);
    digitalWrite(digits[2], HIGH);
    //個位數
    x = x % 10;
    d = x / 1;
    show(seg7_digit[d]);
    digitalWrite(digits[3], LOW);
    delay(5);
    digitalWrite(digits[3], HIGH);

    
  }
}

void hide_seg7(){
  for(int i=0; i<4; i++){
    pinMode(digits[i], OUTPUT);
    digitalWrite(digits[i], HIGH);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  //去彈跳開始
  int reading = digitalRead(BtnPin);
  if (reading != lastBtnState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != btnState)
      btnState = reading;
  }
  lastBtnState = reading;
  //去彈跳結束
  if (btnState == LOW && flag == 0) {
    cnt++;
    Serial.println(cnt);
    if (cnt == 21) cnt = 0;
    show(cnt);
    flag = 1;
  }
  if (btnState == HIGH) {
    flag = 0;
  }
  disp(cnt);
}