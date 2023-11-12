#define LedPin 13
#define BtnPin 2

int cnt;
int flag;
int lastDebounceTime;     //目前去彈跳起始時間
int debounceDelay;        //去彈跳延遲時間
int btnState;             //目前按鍵狀態
int lastBtnState = HIGH;  //之前按鍵狀態
int ledCnt;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(BtnPin, INPUT_PULLUP);  //腳2為輸入，有內建提升電阻
  pinMode(LedPin, OUTPUT);        //腳13為輸出
  digitalWrite(LedPin, LOW);      //LED滅
  cnt = 0;
  flag = 0;
  lastDebounceTime = 0;
  debounceDelay = 50;
  ledCnt = 0;
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
    if (cnt == 4) cnt = 1;
    ledCnt = cnt;
    flag = 1;
    Serial.print("Counter = ");
    Serial.println(cnt);
  }
  if (btnState == HIGH) {
    flag = 0;
  }
  for(int i =0;i<ledCnt;i++){
    digitalWrite(LedPin,HIGH);
    delay(1000/cnt/2);
    digitalWrite(LedPin,LOW);
    delay(1000/cnt/2);
  }
  ledCnt = 0;
}