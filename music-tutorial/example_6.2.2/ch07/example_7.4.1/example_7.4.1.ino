/*** 範例7.4.1(Polling版本) ***/
#define LedPin    13  //Uno開發板上內建LED的接腳固定為D13
#define ButtonPin 2   //指定按鈕開關的接腳為D2
int cnt=0;            //宣告計數值變數

void setup() {
  Serial.begin(9600);              //設定串列埠傳輸速率為9600 bps
  pinMode(LedPin,OUTPUT);          //設定LED接腳為OUTPUT
  pinMode(ButtonPin,INPUT_PULLUP); //設定按鈕開關接腳為INPUT_PULLUP
  digitalWrite(LedPin,LOW);        //初始LED為熄滅的狀態
}

void loop() {
  if(digitalRead(ButtonPin)==LOW) {
    //D2的電壓為LOW，代表按鈕被按下
    digitalWrite(LedPin,!digitalRead(LedPin)); //反轉LED燈現在的狀態
    cnt++; Serial.println(cnt);  //計數值+1，並印出    
    delay(200);                  //避免連續觸發
  }
}
