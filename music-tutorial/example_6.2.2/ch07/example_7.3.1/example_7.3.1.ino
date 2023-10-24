/*** 範例7.3.1(ISR的撰寫) ***/
void setup() {
  Serial.begin(9600);        //設定串列埠傳輸速率為9600 bps
  pinMode(2,INPUT_PULLUP);   //設定接腳2為INPUT，並啟用內建的上拉電阻
  attachInterrupt(digitalPinToInterrupt(2),my_ISR,FALLING);  //中斷設置
}

void loop() {
  //You can do anything.
}

void my_ISR() {
  Serial.println(millis());  //印出53321
  Serial.println(micros());  //印出53322544
  delay(200);                //不會有延遲200ms的效果
  Serial.println(millis());  //印出53321，不變
  Serial.println(micros());  //印出53323388，只差距844us
  Serial.println("-------------");
}
