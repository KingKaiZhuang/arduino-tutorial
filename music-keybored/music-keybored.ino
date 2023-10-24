#include "music.h"
int Row[4] = {4,5,6,7};
int Col[4] = {8,9,10,11};
#define Buzzer 3
char keymap[4][4] = {
  {C4,D4,E4,E5},
  {F4,G4,A4,F5},
  {B4,C5,D5,G5},
  {0,B3,0,A5}
}

void setup() {
  // put your setup code here, to run once:
  for(int i=0;i<=3,i++){
    pinMode(Row[i],INPUT_PULLUP);
    pinMode(Col[i],OUTPUT);
    digitalWrite(Col[i],HIGH);
  }
  pinMode(Buzzer,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0;i<4;i++){
    digitalWrite(col[i],LOW);
    for(int j=0;j<4;j++){
      if(digitalRead(Row[j]==LOW)){
        tone(Buzzer,keymap[i][j],50);
      }
    }
    digitalWrite(Col[i],HIGH);
  }
}
