/*** 範例7.5.3(4x4薄膜鍵盤使用PCINT) ***/
int Row[4]={4,5,6,7};    //依序指定列接腳
int Col[4]={8,9,10,11};  //依序指定行接腳
char keymap[4][4] = {    //宣告4x4鍵盤的對應值
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};
volatile unsigned long now, pre=0; //使用在ISR的時間變數
int i,j,row,col;

void setup() {
  Serial.begin(9600);
  for(i=0; i<=3; i++) {
    pinMode(Row[i],INPUT_PULLUP); //設定Row接腳為INPUT_PULLUP
    pinMode(Col[i],OUTPUT);       //設定Col接腳為OUTPUT
    digitalWrite(Col[i],LOW);     //設定Col接腳的輸出值為LOW
  }
  PCICR |= 0b00000100;  // 致能PCINT2中斷
  PCMSK2|= 0b11110000;  // 致能D4,D5,D6,D7接腳
}

void loop() {
  //You can do anything.
}

ISR(PCINT2_vect) {
  now=millis();                          //取得現在的時間
  if((now-pre)<200) { pre=now; return; } //去彈跳的關鍵
  for(i=0;i<=3;i++) {  //掃描row，決定哪個row被按下
    if(digitalRead(Row[i])==LOW) { row=i; break; } //記錄列編號後就終止
  }
  for(j=0;j<=3;j++) digitalWrite(Col[j],HIGH); //掃描前，將所有的col寫成H
  for(j=0;j<=3;j++) {  //掃描col，決定哪個col被按下
    digitalWrite(Col[j],LOW);           //將col寫成L
    if(digitalRead(Row[row])==LOW) { 
      col=j;                            //記錄col編號
      Serial.println(keymap[row][col]); //印出鍵值
      break;                            //終止迴圈
    }
    else digitalWrite(Col[j],HIGH);     //將col恢復成H
  }
  for(j=0;j<=3;j++) digitalWrite(Col[j],LOW);  //掃描後，將所有的col寫成L
  pre=now;                              //儲存中斷時間
}
