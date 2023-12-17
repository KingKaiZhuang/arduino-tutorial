#define led 13
#define Btn 2
#define deBounceTime 200
#define btnPressed 1
#define btnReset 0
volatile int cnt=0;
volatile unsigned long now=0,pre=0;
volatile int btnState;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led,OUTPUT);
  pinMode(Btn,INPUT_PULLUP);
  digitalWrite(led,LOW);
  EIMSK = 0x01;
  EICRA = 0x02;
  btnState = btnReset;
}

void loop() {
  // put your main code here, to run repeatedly:
  if(btnState==btnPressed){
    digitalWrite(led, !digitalRead(led));
    cnt++;
    Serial.println(cnt);
    btnState = btnReset;
  }
}

ISR(INT0_vect){
  now = millis();
  if(now-pre<deBounceTime) { pre = now; return;}
  pre = now;
  btnState = btnPressed;
}
