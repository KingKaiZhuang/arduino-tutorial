boolean state = false;
boolean buttonUp = true;

void setup() {
  // put your setup code here, to run once:
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
  pinMode(7,INPUT);
  digitalWrite(7,HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(7) != HIGH && buttonUp == true){
    state = !state;
    digitalWrite(13,state);
    buttonUp = false;
  }else if(digitalRead(7) == HIGH && buttonUp != true){
    buttonUp = true;
  }
}
