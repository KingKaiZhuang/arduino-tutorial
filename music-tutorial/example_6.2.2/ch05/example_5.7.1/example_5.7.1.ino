/*** 範例5.7.1(RGB全彩LED) ***/
const int Rpin=9, Gpin=10, Bpin=11;  //將接腳分別指定到PWM接腳9,10,11
int i,j,k;

void setup() {
  pinMode(Rpin,OUTPUT);
  pinMode(Gpin,OUTPUT);
  pinMode(Bpin,OUTPUT);
  randomSeed(analogRead(0));   //初始亂數產生種子
  color(255, 0 , 0 ); delay(1000);  //顯示紅光，並延遲1秒
  color( 0 ,255, 0 ); delay(1000);  //顯示綠光，並延遲1秒
  color( 0 , 0 ,255); delay(1000);  //顯示藍光，並延遲1秒
  color(255,255,255); delay(1000);  //顯示白光，並延遲1秒
}

void loop() {
  i=random(0,256);            //產生0-255亂數
  j=random(0,256);
  k=random(0,256);
  color(i,j,k); delay(1000);  //顯示燈光並延遲1秒
}

void color(int Rval, int Gval, int Bval) {
  analogWrite(Rpin, Rval);
  analogWrite(Gpin, Gval);
  analogWrite(Bpin, Bval);
}
