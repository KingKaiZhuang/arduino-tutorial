/*** 範例9.5.2(PWM範例-2) ***/
#include <wiring_private.h>
volatile int ISR_cnt, Soft_pin, Soft_dc; 

/***************************************************
 * setup & loop
 ***************************************************/
void setup() { 
  softPWM_init();
}

void loop() {
int i;
  for(i=0; i<=30; i+=2)
    { softPWM(13,i); delay(200); }
  for(i=30; i>=0; i-=2)
    { softPWM(13,i); delay(200); }
}

/***************************************************
 * softPWM_init
 ***************************************************/
void softPWM_init()
{
   //---step1:初始暫存器
   TCCR2A=0; TCCR2B=0; TCNT2=0;
   //---step2:設定CTC模式
   sbi(TCCR2A,WGM21); 
   //---step3:設定預先除頻倍率prescaler與TOP值
   sbi(TCCR2B,CS21);  sbi(TCCR2B,CS20);  //prescaler=32
   OCR2A=64;                             //設定TOP=64
   //---step4:致能對應的中斷
   sbi(TIMSK2, OCIE2A);
   //---其它變數
   ISR_cnt=99; Soft_pin=-1; Soft_dc=0;
}

/***************************************************
 * softPWM
 ***************************************************/
void softPWM(int pin, int dc)
{
  pinMode(pin,OUTPUT);
  Soft_pin=pin; Soft_dc=dc;  //設定pin腳與duty cycle
  ISR_cnt=0;                 //ISR_cnt計數值重置為0
}

/***************************************************
 * Timer2的COMPA中斷服務程式
 ***************************************************/
ISR(TIMER2_COMPA_vect)
{
  ISR_cnt=++ISR_cnt%100;
  //前dc個中斷輸出HIGH，後(100-dc)個中斷輸出LOW
  if(ISR_cnt==0) digitalWrite(Soft_pin,HIGH);
  if(ISR_cnt==Soft_dc) digitalWrite(Soft_pin,LOW);
}
