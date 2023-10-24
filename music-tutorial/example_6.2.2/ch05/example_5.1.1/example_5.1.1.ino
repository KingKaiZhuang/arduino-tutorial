/*** 範例5.1.1(USB通訊埠) ***/
char ch;                //宣告字元變數

void setup() {
  Serial.begin(9600);   //設定串列埠傳輸速率為9600 bps
}

void loop() {
  if(Serial.available()>0) {
    ch=Serial.read();
    if(ch>=97 && ch<=122) ch=ch-32;  //如果ch是小寫的英文字母就改成大寫
    Serial.write(ch);
  }
}
