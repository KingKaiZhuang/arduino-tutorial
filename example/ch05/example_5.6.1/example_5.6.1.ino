/*** 範例5.6.1(讀取可變電阻/電位器的輸出值) ***/
const int potPin=A0;   //指定可變電阻的接腳為A0
int val,pre_val=0;
float volt;

void setup() {
  Serial.begin(9600);
  pinMode(potPin,INPUT);
}

void loop() {
  val=analogRead(potPin);    //讀取A0，傳回0-1023
  if(val!=pre_val) {         //判斷值是否改變
    volt=(float)val/1023*5;  //將val從0-1023區間轉換成0-5V的區間
    Serial.print(val);  Serial.print(" => "); //印出結果
    Serial.print(volt,2);    //小數點2位
    Serial.println('V');
    pre_val=val;
  }
  delay(1000);               //延遲1秒
}
