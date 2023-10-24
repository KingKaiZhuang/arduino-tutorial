/*** 範例5.2.2(外接LED) ***/
#define LedA 13  //Uno開發板上內建LED的接腳固定為D13
#define LedB 5   //指定外接LED的接腳為D5

void setup() {
  pinMode(LedA,OUTPUT);       //設定LED接腳為輸出模式
  pinMode(LedB,OUTPUT);       
  digitalWrite(LedA,LOW);     //初始LED為熄滅的狀態
  digitalWrite(LedB,LOW);
}

void loop() {
  //內建LED持續亮1秒後熄滅
  digitalWrite(LedA,HIGH); delay(1000); digitalWrite(LedA,LOW);
  //外接LED持續亮1秒後熄滅
  digitalWrite(LedB,HIGH); delay(1000); digitalWrite(LedB,LOW);
}
