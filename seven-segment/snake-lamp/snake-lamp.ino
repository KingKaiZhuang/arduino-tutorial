#define seg7_a 2

int seg7_digit[8]={B11111010, B00111110, B11110110, B11011110, B01111010, B10011100, B11110110, B10001110};
int digits[4]={10,11,12,13};
void setup() {
  // put your setup code here, to run once:
  for(int i=0; i<8; i++)
  {
    pinMode(seg7_a+i, OUTPUT);
    digitalWrite(seg7_a+i, LOW);
  }
  for(int i=0; i<4; i++){
     pinMode(digits[i], OUTPUT);
    digitalWrite(digits[i], HIGH);
  }
  digitalWrite(digits[0], LOW);
}
void show(int val){
  int mask0 = B10000000;
  int mask;
  for(int i=0; i<8; i++){
    mask = mask0 >> i;
    if(val&mask) digitalWrite(seg7_a+i, HIGH);
    else digitalWrite(seg7_a+i, LOW);
  }
}
void loop() {
  // put your main code here, to run repeatedly:
 for(int i=0; i<8; i++){
   show(seg7_digit[i]);
   delay(1000);
 }
}

