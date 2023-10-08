#define seg7_a 2

int seg7_digit[8]={B10000000, B01000000, B00000010 , B00001000, B00010000, B00100000, B00000010, B00000100 };
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
  digitalWrite(digits[3], LOW);
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
   delay(100);
 }
}

