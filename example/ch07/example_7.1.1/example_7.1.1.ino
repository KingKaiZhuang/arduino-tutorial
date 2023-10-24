/*** 範例7.1.1(輪詢) ***/
void setup() {
  pinMode(2,INPUT_PULLUP);   //設定接腳2為INPUT，並啟用內建的上拉電阻
  pinMode(13,OUTPUT);        //設定板載LED為輸出模式
  digitalWrite(13,LOW);      //初始LED為不亮的狀態
}

void loop() {
  if(digitalRead(2)==LOW) {  //輪詢，讀取Button接腳的電位是否為LOW
    digitalWrite(13,!digitalRead(13));  //若是，反轉板載LED的狀態
    delay(200);              //避免連續讀取
  }
}
