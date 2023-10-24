/*** 範例9.5.1(PWM範例-1) ***/
#include <wiring_private.h>     //暫存器位元名稱的定義

/***************************************************
 * setup & loop
 ***************************************************/
void setup() {}
void loop() {
  pin3PWM(31,5);     //freq=31Hz, duty cycle=5%
  delay(3000);
  pin3PWM(2000,50);  //freq=2000Hz, duty cycle=90%
  delay(3000);
}

/***************************************************
 * pin3PWM
 ***************************************************/
int pin3PWM(int freq, int dc)
{
float TOP;
int i, pre[6]={8,32,64,128,256,1024};

  pinMode(3, OUTPUT);
  if(dc==0)  {
    digitalWrite(3,LOW);  //若duty cycle=0%直接改用digitalWrite(3,LOW)
    return 1;
  }
  if(dc==100)  {
    digitalWrite(3,HIGH); //若duty cycle=100%直接改用digitalWrite(3,HIGH)
    return 1;
  }
  //根據目標頻率，計算適用的除頻倍率，並且設定OCR2A
  for(i=0;i<6;i++) {
    TOP=16000000/pre[i]/freq/2;                 //頻率公式
    if(TOP<255 && TOP>0) { OCR2A=TOP; break; }  //合法的TOP值
  }
  //設定正確的 CS22-CS20
  switch(i) {
    case 0:    //prescaler=8, CS=0102
      sbi(TCCR2B,CS21); break;
    case 1:    //prescaler=32, CS=0112
      sbi(TCCR2B,CS21); sbi(TCCR2B,CS20); break;
    case 2:    //prescaler=64, CS=1002
      sbi(TCCR2B,CS22); break;
    case 3:    //prescaler=128, CS=1012
      sbi(TCCR2B,CS22); sbi(TCCR2B,CS20); break;
    case 4:    //prescaler=256, CS=1102
      sbi(TCCR2B,CS22); sbi(TCCR2B,CS21); break;
    case 5:    //prescaler=1024, CS=1112
      sbi(TCCR2B,CS22); sbi(TCCR2B,CS21); sbi(TCCR2B,CS20); break;
    default:   //無可用的除頻倍率，設定失敗，傳回0
      return 0;
  }
  //設定 Phase correct PWM (mode 5)模式，WGM2[2:0]=1012
  sbi(TCCR2B,WGM22); sbi(TCCR2A,WGM20);
  OCR2B=OCR2A*dc/100;  //根據duty cycle，設定正確的OCR2B
  sbi(TCCR2A,COM2B1);  //設定OC2B的比較輸出模式=102        
  return 1;            //設定成功，傳回1
}
