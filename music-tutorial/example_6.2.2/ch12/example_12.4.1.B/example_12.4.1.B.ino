/*** 範例12.4.1.B(SPI範例-1 for UNO_B) ***/
#include <SPI.h>
char buf[50];                 //宣告50個字元的緩衝區
volatile int index=0, flag=0; //重置index,flag為0

/***************************************************
 * setup
 ***************************************************/
void setup () {
  Serial.begin(9600);    //設定串列埠傳輸速率為9600 bps
  pinMode(MISO,OUTPUT);  //設定MISO接腳為OUTPUT
  SPCR |= _BV(SPE);      //啟用SPI在slave模式
  SPI.attachInterrupt(); //啟用SPI中斷
}

/***************************************************
 * loop
 ***************************************************/
void loop() {
  if(flag==1) {        //如果flag==1，就印出完整字串
    buf[index]=NULL;   //最後填入字串結束字元
    Serial.print(buf); //印出完整字串
    index=0; flag=0;   //重置index,flag為0
  }
}

/***************************************************
 * SPI傳輸完成中斷服務程式
 ***************************************************/
ISR(SPI_STC_vect) {
  char ch=SPDR;            //從SPI資料暫存器SPDR抓取字元
  if(index<sizeof(buf)) {
    buf[index++]=ch;       //將讀取到的字元存進buf
    if(ch=='\n') flag=1;   //如果是換行字元，flag=1
  }
}
