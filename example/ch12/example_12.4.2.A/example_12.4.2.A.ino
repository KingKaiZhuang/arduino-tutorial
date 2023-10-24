/*** 範例12.4.2.A(SPI範例-2 for UNO_A) ***/
#include <SPI.h>
#define ButtonPin 2
volatile byte value=0, flag=0; 

/***************************************************
 * setup
 ***************************************************/
void setup() {
  Serial.begin(9600);        //設定串列埠傳輸速率為9600 bps
  randomSeed(analogRead(0)); //指定產生隨機亂數的種子
  //---設定外部中斷
  pinMode(ButtonPin,INPUT_PULLUP);
  EIMSK |= _BV(INT0);   //致能INT0
  EICRA |= _BV(ISC01);  //將觸發模式設為FALLING(ISC01=1,ISC00=0)
  EICRA &= ~_BV(ISC00);
  //---設定SPI
  SPI.begin();          //初始化SPI的硬體設定並設成master模式
  SPI.setClockDivider(SPI_CLOCK_DIV8); //設定SPI除頻倍率為8
}

/***************************************************
 * loop
 ***************************************************/
void loop() {  
  if(flag==1) {
    Serial.println(value);  //印出數值
    digitalWrite(SS,LOW);   //拉降SS為L，致能Slave
    SPI.transfer(value);    //使用SPI送出數值
    digitalWrite(SS,HIGH);  //拉升SS為H，停用Slave
    delay(500);             //避免連續觸發
    flag=0;
  }
}

/***************************************************
 * INT0中斷服務程式 
 ***************************************************/
ISR(INT0_vect) {
  value=random(0,256);      //產生0-255的亂數
  flag=1;
}
