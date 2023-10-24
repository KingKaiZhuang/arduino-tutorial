/*** 範例7.4.3(ISR版本) ***/
#define LedPin    13  //Uno開發板上內建LED的接腳固定為D13
#define ButtonPin 2   //指定按鈕開關的接腳為D2
volatile int cnt=0;                //使用在ISR的計數值變數
volatile unsigned long now, pre=0; //使用在ISR的時間變數

void setup() {
  Serial.begin(9600);              //設定串列埠傳輸速率為9600 bps
  pinMode(LedPin,OUTPUT);          //設定LED接腳為OUTPUT
  pinMode(ButtonPin,INPUT_PULLUP); //設定按鈕開關接腳為INPUT_PULLUP
  digitalWrite(LedPin,LOW);        //初始LED為熄滅的狀態
  EIMSK |= _BV(INT0);     //致能INT0
  EICRA |= _BV(ISC01);    //將觸發模式設為FALLING(ISC01=1,ISC00=0)
  EICRA &= ~_BV(ISC00);
}

void loop() {
  //You can do anything.
}

// INT0固定呼叫的中斷處理函式
ISR(INT0_vect) {
  now=millis();                              //取得現在的時間
  if((now-pre)<200) { pre=now; return; }     //去彈跳的關鍵
  digitalWrite(LedPin,!digitalRead(LedPin)); //反轉LED燈現在的狀態
  cnt++; Serial.println(cnt);                //計數值+1，並印出
  pre=now;
}
