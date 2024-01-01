/*** 範例7.1.2(中斷) ***/
void setup() {
  Serial.begin(9600);
  pinMode(2,INPUT_PULLUP);   //設定接腳2為INPUT，並啟用內建的上拉電阻
  pinMode(13,OUTPUT);        //設定板載LED為輸出模式
  digitalWrite(13,LOW);      //初始LED為不亮的狀態
  attachInterrupt(digitalPinToInterrupt(2),my_ISR,FALLING);  //中斷設置
}

void loop() {
  //You can do anything.
}

void my_ISR() {
  Serial.println("hi");
  digitalWrite(13,!digitalRead(13));  //反轉板載Led的狀態
}
