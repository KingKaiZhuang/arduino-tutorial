/*** 範例11.4.1(I2C範例-1) ***/
#include <Wire.h>

/***************************************************
 * setup
 ***************************************************/
void setup() {
  Serial.begin(9600);    //設定串列埠傳輸速率為9600 bps
  Wire.begin();          //將本裝置初始成master
  Serial.println("I2C Slave Scanning ...");
  for(byte addr=8;addr<120;addr++) {  //從位址8開始掃瞄到位址119
    Wire.beginTransmission(addr);     //開始傳送資料到指定的slave位址
    if(Wire.endTransmission()==0) {   //假如有回傳ACK就顯示其位址
      Serial.print("Find slave at: 0X"); 
      Serial.println(addr, HEX);
    }
  }
  Serial.println("End ...");  
}

/***************************************************
 * loop
 ***************************************************/
void loop() {
  //empty
}
