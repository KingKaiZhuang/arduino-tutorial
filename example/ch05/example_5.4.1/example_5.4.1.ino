/*** 範例5.4.1(滾珠開關) ***/
#define LedPin  13  //UNO開發板上內建LED的接腳固定為D13
#define BallPin 2   //指定按鈕開關的接腳為pin 2
int cnt=0;          //宣告計數值變數

void setup() {
  Serial.begin(9600);             //設定串列埠傳輸速率為9600 bps
  pinMode(LedPin,OUTPUT);         //設定LED接腳為輸出模式
  pinMode(BallPin,INPUT_PULLUP);  //設定滾珠開關接腳，並啟用內建的上拉電阻
  digitalWrite(LedPin,LOW);       //初始LED為熄滅的狀態
}

void loop() {
  if(digitalRead(BallPin)==LOW) { //讀取滾珠開關接腳的電位是否為LOW
    //若是，就代表導通，則開啟LED，計數值+1並顯示
    digitalWrite(LedPin,HIGH);    
    Serial.print("cnt="); Serial.println(cnt++);
    delay(300);                   //適當的延遲，避免連續+1   
  }
  else digitalWrite(LedPin,LOW);  //否則，關閉LED
}
