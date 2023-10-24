/*** 範例5.6.2(使用可變電阻控制LED燈光的強度) ***/
const int potPin=A0, ledPin=3;
int val,pre_val=0,duty;

void setup() {
  Serial.begin(9600);
  pinMode(potPin,INPUT);
  pinMode(ledPin,OUTPUT);
}

void loop() {
  val=analogRead(potPin);       //讀取A0，傳回0-1023
  if(val>pre_val+2 || val<pre_val-2) {  //判斷值是否明顯改變
    duty=map(val,0,1023,0,255); //將val從0-1023區間轉換成0-255的區間
    analogWrite(ledPin,duty);   //在指定的pin 3接腳輸出PWM訊號
    Serial.print(val);          //印出可變電阻的值
    Serial.print("->");
    Serial.println(duty);       //印出轉換後的duty cycle
    pre_val=val;
  }
  delay(500);       //延遲500ms，達到1秒讀取2次可變電阻的效果
}
