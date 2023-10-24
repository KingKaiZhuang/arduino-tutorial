/*** 範例6.1.1(4x4薄膜鍵盤) ***/
int Row[4]={4,5,6,7};    //指定列的接腳
int Col[4]={8,9,10,11};  //指定行的接腳
char keymap[4][4] = {    //設定4x4鍵盤的對應值
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};
int i,j;

void setup() {
  Serial.begin(9600);
  for(i=0; i<=3; i++) {
    pinMode(Row[i], INPUT_PULLUP); //設定Row接腳，並啟用內建的上拉電阻
    pinMode(Col[i], OUTPUT);
    digitalWrite(Col[i], HIGH);    //設定Col接腳的初始值為HIGH
  }
}

void loop() {
  for(i=0;i<4;i++) {                  //Col依序寫入0
    digitalWrite(Col[i],LOW);
    for(j=0;j<4;j++) {                //Row掃描讀取
      if(digitalRead(Row[j])==LOW) {  //判斷是否為0
        Serial.println(keymap[j][i]); //=0，印出對應的鍵值
        delay(200);                   //適當的延遲，避免連續顯示
        break;
      }
    }
    digitalWrite(Col[i],HIGH);        //恢復原來Col的高電位
  }
}
