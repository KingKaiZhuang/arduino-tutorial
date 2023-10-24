/*** 範例12.4.1.A(SPI範例-1 for UNO_A) ***/
#include <SPI.h>
char msg[]="This is SPI communication\n";

/***************************************************
 * setup
 ***************************************************/
void setup() {
  Serial.begin(9600);     //設定串列埠傳輸速率為9600 bps
  SPI.begin();            //初始化SPI的硬體設定並設成master模式
  SPI.setClockDivider(SPI_CLOCK_DIV8); //設定SPI除頻倍率為8
}

/***************************************************
 * loop
 ***************************************************/
void loop() {  
char ch;
  digitalWrite(SS,LOW);   //拉降SS為L，致能Slave
  //---列印並使用SPI送出字串
  for(int i=0;ch=msg[i];i++) {  
      SPI.transfer(ch);
      Serial.print(ch);
  }
  digitalWrite(SS,HIGH);  //拉升SS為H，停用Slave
  delay(5000);            //延遲5000ms=5s
}
