/*** 範例5.3.1(按鈕開關1) ***/
#define LedPin    13  //UNO開發板上內建LED的接腳固定為D13
#define ButtonPin 2   //指定按鈕開關的接腳為pin 2

void setup() {
  pinMode(LedPin,OUTPUT);          //設定LED接腳為輸出模式
  pinMode(ButtonPin,INPUT_PULLUP); //設定Button接腳，並啟用內建的上拉電阻
  digitalWrite(LedPin,LOW);        //初始LED為熄滅的狀態
}

void loop() {
  if(digitalRead(ButtonPin)==LOW)  //讀取Button接腳的電位是否為LOW
    digitalWrite(LedPin,HIGH);     //若是，就代表按下開關，開啟LED
  else digitalWrite(LedPin,LOW);   //否則，關閉LED
}
