/*** 範例6.2.2 (無源蜂鳴器) ***/
#include "music.h"  //載入音樂定義檔
#define Buzzer 4    //指定蜂鳴器的接腳為 pin 4
#define S140  140
//定義音高,XX表結束
int pitch[46]=
{A4, B4, A4, B4, A4, G4, A4, B4, A4, G4, A4, G4, E4, D4, E4, G4, D4, 0, E4, A4, E4, G4, G4, E4, A4, G4, A4, G4, E4, G4, G4, E4, D4, D4, D4, D4, E4, G4, E4, E4, D4, A3, E4, D4, 0, XX}; //望春風
//定義節拍
float tempo[45]={
T4,T4,T8,T8,T8,T8,T8,T8,T8,T8,T4,T8,T8,T4,T4,T4,T4,T8,T8,T8,T8,T8,T8,T8,T8,T8,T8,T8,T8,T8,T8,T8,T8,T8,T8,T8,T8,T4,T4,T4,T4,T4}; //望春風

void setup() {
  pinMode(Buzzer,OUTPUT);       //設定蜂鳴器接腳為輸出模式
}

void loop() {
 play();
 delay(2000);
}

void play() {
int i, T1time, duration;
  T1time=4*60000/66;          //計算全音符T1的時間(ms)
  for(i=0;;i++) {
    if(pitch[i]==9999) return;   //判斷結尾       
    duration=T1time*tempo[i];    //計算節拍時間(ms)
    tone(Buzzer,pitch[i],duration/2);  //演奏一半，聽起來更自然
    delay(duration/2);                //停頓一半，才不會所有的音都連在一起
  }
}