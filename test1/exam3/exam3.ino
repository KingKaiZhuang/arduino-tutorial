#define seg7_a 2
//共陰極七段顯示器顯示值與a,b,c,d,e,f,g,h 等8顆LED HI/LO設定關係
int seg7_digit[10]={0xfc, 0x60, 0xda, 0xf2, 0x66, 0xb6, 0xbe, 0xe4, 0xfe, 0xf6};
//4位數7段顯示器最左邊到最右邊之位數(即位數1~4)之Arduino控制腳位(10~13)
int digits[4]={10,11,12,13};
#define BtnPin A0
int cnt;
int flag;
int lastDebounceTime; //目前去彈跳起始時間
int debounceDelay; //去彈跳延遲時間
int btnState; //目前按鍵狀態
int lastBtnState = HIGH; //之前按鍵狀態
int reading;

int TimeCnt;

void setup() {
  // put your setup code here, to run once:
  for(int i=0; i<8; i++) {
    pinMode(seg7_a+i, OUTPUT);//設定腳位2~9對應到七段顯示器之a,b,c,d,e,f,g,h
    digitalWrite(seg7_a+i, LOW);//共陰極滅掉
  }
  for(int i=0; i<4; i++) {
    pinMode(digits[i], OUTPUT);//設定七段顯示器位數1,2,3,4由arduino腳10,11,12,13控制
    digitalWrite(digits[i], HIGH);//共陰極滅掉
  }
  pinMode(BtnPin, INPUT_PULLUP); //腳2為輸入，有內建提升電阻
  reading = digitalRead(BtnPin);
  lastDebounceTime = reading;
  btnState = reading;
  cnt = 0;
  flag = 0;
  lastDebounceTime = 0;
  debounceDelay = 50;
  TimeCnt = 0;
  Serial.begin(9600);
}

void show(int val) {
  int mask0 = 0x80;
  int mask;
  int val2 = seg7_digit[val];
  for(int i=0; i<8; i++) {
    mask = mask0 >> i;
    if(val2&mask) digitalWrite(seg7_a+i, HIGH);
    else digitalWrite(seg7_a+i, LOW);
  }
}

void disp (int val){
  long t0 = millis();
  while(millis()-t0<100){
    int x = val;
    int d;
    //顯示千位數
    d = x/1000;
    //hide_seg7();
    show(d);
    digitalWrite(digits[0], LOW);
    delay(5);
    digitalWrite(digits[0], HIGH);
    //顯示百位數
    x = x%1000;
    d = x/100;
    show(d);
    digitalWrite(digits[1], LOW);
    delay(5);
    digitalWrite(digits[1], HIGH);
    //顯示十位數
    x = x%100;
    d = x/10;
    show(d);
    digitalWrite(seg7_a+7, HIGH);//點亮h(七段顯示器十位數上的小數點)
    digitalWrite(digits[2], LOW);
    delay(5);
    digitalWrite(digits[2], HIGH);
    //顯示個位數
     x = x%10;
    d = x/1;
    show(d);
    digitalWrite(digits[3], LOW);
    delay(5);
    digitalWrite(digits[3], HIGH);
  }
}
void loop() {
  // put your main code here, to run repeatedly:
  //每一秒共陰極七段顯示器顯示一0~9之數值
    int reading = digitalRead(BtnPin);
  if(reading!=lastBtnState) {
    lastDebounceTime = millis();
  }
  if((millis()-lastDebounceTime)>debounceDelay) {
    if(reading != btnState)
      btnState = reading;
  }
  lastBtnState = reading;
  //去彈跳結束
  if(btnState==LOW && flag==0) {
    cnt++;
    if(cnt==3) cnt = 0;
    flag = 1;
  }
 if(btnState==HIGH)  {
    flag = 0;
 }
  if(cnt == 0){
    TimeCnt = 0;
  }
  else if(cnt == 1){
    TimeCnt++;
    if(TimeCnt == 9999) cnt = 2;
  }
  disp(TimeCnt);
  Serial.println(String("cnt = ")+String(cnt)+String(", TimeCnt = ")+String(TimeCnt));
}
 