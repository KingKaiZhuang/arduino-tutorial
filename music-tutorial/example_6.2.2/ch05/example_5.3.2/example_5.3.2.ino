/*** 範例5.3.2(按鈕開關2) ***/
#define ButtonPin 2    //指定按鈕開關的接腳為pin 2
int cnt;   //宣告計數值變數
int flag;  //宣告旗標變數，

void setup() {
  Serial.begin(9600);              //設定串列埠傳輸速率為9600 bps
  pinMode(ButtonPin,INPUT_PULLUP); //設定Button接腳，並啟用內建的上拉電阻
  cnt=0; flag=0;
  Serial.print("計數值=");  Serial.println(cnt);
}

void loop() {
  if(digitalRead(ButtonPin)==HIGH) flag=0;
  if(digitalRead(ButtonPin)==LOW && flag==0)  { 
    //Button接腳的電位從HIGH變成LOW，只有第一次會符合條件
    cnt++;   //計數值+1
    Serial.print("計數值=");  Serial.println(cnt);
    flag=1;  //避免連續+1
  }
}
