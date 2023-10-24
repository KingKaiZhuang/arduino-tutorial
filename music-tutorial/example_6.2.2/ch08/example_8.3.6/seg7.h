/*** seg7.h ***/
const byte seg7_digit[10]={ B11111100,  //數字0
							B01100000,  //數字1
							B11011010,  //數字2
							B11110010,  //數字3
							B01100110,  //數字4
							B10110110,  //數字5
							B10111110,  //數字6
							B11100100,  //數字7
							B11111110,  //數字8
							B11110110}; //數字9
int seg7x1_FirstPin;  //一位數七段顯示器的第一隻接腳
int seg7x4_FirstPin;  //四位數七段顯示器的第一隻接腳

/*** 一位數七段顯示器相關函式 ***/
//--- 初始化一位數七段顯示器8隻連續的接腳
void seg7x1_init(int pin) {
  seg7x1_FirstPin=pin;  //設定一位數七段顯示器的第一隻接腳
  for(int i=0; i<8; i++) pinMode(seg7x1_FirstPin+i, OUTPUT);
}

//--- 一位數七段顯示器顯示數字
void seg7x1_show(int num) {
byte mask;

  for(int i=0; i<8; i++)  {
    mask=B10000000>>i;  //將1右移到正確的位置
    if(seg7_digit[num] & mask) digitalWrite(seg7x1_FirstPin+i, HIGH);
    else digitalWrite(seg7x1_FirstPin+i, LOW);
  }
}

/*** 四位數七段顯示器相關函式 ***/
//--- 初始化四位數七段顯示器12隻連續的接腳
void seg7x4_init(int pin) {
  seg7x4_FirstPin=pin;  //設定四位數七段顯示器的第一隻接腳
  for(int i=0; i<12; i++) pinMode(seg7x4_FirstPin+i, OUTPUT);
}

//--- 四位數七段顯示器顯示數字
void seg7x4_show(int digit, int num) {
byte mask;

  //先關掉四顆七段顯示器
  for(int i=8; i<12; i++) digitalWrite(seg7x4_FirstPin+i, HIGH);
  //再致能指定的七段顯示器
  switch(digit) {
    case 0: digitalWrite(seg7x4_FirstPin+8, LOW); break; //致能第0顆
    case 1: digitalWrite(seg7x4_FirstPin+9, LOW); break; //致能第1顆
    case 2: digitalWrite(seg7x4_FirstPin+10,LOW); break; //致能第2顆
    case 3: digitalWrite(seg7x4_FirstPin+11,LOW); break; //致能第3顆
  }
  //顯示數字
  for(int i=0; i<8; i++)  {
    mask=B10000000>>i;
    if(seg7_digit[num] & mask) digitalWrite(seg7x4_FirstPin+i, HIGH);
    else digitalWrite(seg7x4_FirstPin+i, LOW);
  }
}


