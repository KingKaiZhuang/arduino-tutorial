/*** 範例7.1.2(中斷) ***/
#include "DHT.h"
#define DHTPIN 6
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  pinMode(2,INPUT_PULLUP);   //設定接腳2為INPUT，並啟用內建的上拉電阻
  pinMode(13,OUTPUT);        //設定板載LED為輸出模式
  digitalWrite(13,LOW);      //初始LED為不亮的狀態
  dht.begin();
  attachInterrupt(digitalPinToInterrupt(2),my_ISR,FALLING);  //中斷設置
}

void loop() {
  //You can do anything.
}

void my_ISR() {
  Serial.println("hi");
  digitalWrite(13,!digitalRead(13));  //反轉板載Led的狀態
  measureTemperatureAndHumidity(); 
}

void measureTemperatureAndHumidity() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.println(" *F");
}
