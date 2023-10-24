/*** 範例8.3.5(Timer範例-1) ***/
#define LedPin 13    //Uno板上內建LED的接腳固定為D13
int i=0;

/***************************************************
 * setup
 ***************************************************/
void setup() {
  Serial.begin(9600);        //設定串列埠傳輸速率為9600 bps
  pinMode(LedPin,OUTPUT);    //設定LED接腳為OUTPUT
  digitalWrite(LedPin,LOW);  //初始LED為熄滅的狀態
  setupTimer1();             //設定定時器Timer1
}

/***************************************************
 * loop
 ***************************************************/
void loop() {
  Serial.println(i);  i=++i%100;  //循環印出0-99
  delay(400);                     //延遲400ms
}

/***************************************************
 * Timer1的COMPA中斷服務程式，每1秒產生一次中斷
 ***************************************************/
ISR(TIMER1_COMPA_vect) {
  digitalWrite(LedPin,!digitalRead(LedPin)); //反轉LED現在的狀態
}
/***************************************************
 * 設定定時器
 ***************************************************/
void setupTimer1() {
  //---step1:初始暫存器
   TCCR1A=0;              //設定初始值為0
   TCCR1B=0;
   TCNT1=0;

  //---step2:設定CTC模式
   TCCR1B |= _BV(WGM12);  //將1左移3個位元，進行位元OR邏輯運算

  //---step3:設定預先除頻倍數prescaler與正確的TOP上限值
  //在prescaler=256，TOP=62500的設定下，Timer1會固定每一秒產生一次中斷
   TCCR1B |= _BV(CS12);   //prescaler=256
   OCR1A=62500;           //設定TOP=62500

  //---step4:致能對應的中斷
   TIMSK1 |= _BV(OCIE1A); //致能輸出比較中斷A
}
