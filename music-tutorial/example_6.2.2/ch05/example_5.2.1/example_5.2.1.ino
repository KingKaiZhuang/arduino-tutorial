/*** 範例5.2.1(內建LED) ***/
#define Led 13          //UNO開發板上內建LED的接腳固定為D13

void setup() {
  pinMode(Led,OUTPUT);  //設定LED接腳為輸出模式
}

void loop() {
  digitalWrite(Led,HIGH); delay(1000);  //點亮LED，並持續1秒
  digitalWrite(Led,LOW);  delay(1000);  //關閉LED，並持續1秒
}
