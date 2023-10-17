#define seg7_a 2
#define Vin A0

int seg7_digit[10]={0xfc, 0x60, 0xda, 0xf2, 0x66, 0xb6, 0xbe, 0xe4, 0xfe, 0xf6};
int digits[4]={10,11,12,13};

void setup() {
  for(int i=0; i<8; i++)
  {
    pinMode(seg7_a+i, OUTPUT);
    digitalWrite(seg7_a+i, LOW);
  }
  for(int i=0; i<4; i++){
    pinMode(digits[i], OUTPUT);
    digitalWrite(digits[i], HIGH);
  }
  Serial.begin(9600);
  digitalWrite(digits[0], HIGH);
  digitalWrite(digits[1], HIGH);
  digitalWrite(digits[2], HIGH);
  digitalWrite(digits[3], HIGH);

}
void show(int val){
  int mask0 = 0x80;
  int mask;
  for(int i=0; i<8; i++){
    mask = mask0 >> i;
    if(val&mask) digitalWrite(seg7_a+i, HIGH);
    else digitalWrite(seg7_a+i, LOW);
  }
}
void loop() {
  int d,x,t0;
  float vr = analogRead(Vin)*5.0/1024;
  Serial.println(vr);
  
  // for(int x1=0;x1 < 10000;x1++){
  //  t0 = millis();
  //  while(millis()-t0 < 100){
      x = vr * 1000;
      // 千位數
      d = x / 1000;
      show(seg7_digit[d]);
      digitalWrite(9, HIGH);
      digitalWrite(10,LOW);
      

      delay(5);
      digitalWrite(10,HIGH);
      // 百位數
      x %= 1000;
      d = x /100;
      show(seg7_digit[d]);
      digitalWrite(11,LOW);
      delay(5);
      digitalWrite(11,HIGH);
      // 十位數
      x %= 100;
      d = x / 10;
      show(seg7_digit[d]);
      digitalWrite(12,LOW);
      delay(5);
      digitalWrite(12,HIGH);
      // 個位數
      x %= 10;
      d = x / 1;
      show(seg7_digit[d]);
      digitalWrite(13,LOW);
      delay(5);
      digitalWrite(13,HIGH);      
  //  }
  // }
}