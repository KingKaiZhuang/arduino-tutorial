/*** 範例10.5.1.B(UART範例-1 for UNO_B) ***/
#define LedPin 13             //指定LED接腳

/***************************************************
 * setup
 ***************************************************/
void setup() {
   Serial.begin(9600);        //設定串列埠傳輸速率為9600 bps
   pinMode(LedPin,OUTPUT);
}

/***************************************************
 * loop
 ***************************************************/
void loop() {
  if(Serial.available()>0) {
    if(Serial.read()=='1') {
      digitalWrite(LedPin,HIGH); //接收到'1'，點亮LED
      delay(500);                //持續500ms
      digitalWrite(LedPin,LOW);  //關掉LED
    }
  }
}
