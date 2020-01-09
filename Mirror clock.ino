#include <LiquidCrystal.h>
#include <virtuabotixRTC.h>
LiquidCrystal lcd(8, 7, 6, 5, 4, 2);
int clk = 11;
int dat = 12;
int rst = 13;
int trig = 10;
int echo = 9;
virtuabotixRTC myRTC(clk, dat, rst);

void setup() {
  lcd.begin(20, 4);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  myRTC.setDS1302Time(00, 00, 12, 4, 9, 1, 2020);

}

void loop() {
  long duration, cm;
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  cm = microsecondsToCentimeters(duration);

  myRTC.updateTime();
  if(cm < 100){
    lcd.clear();
    lcd.setCursor(6, 0);
    lcd.print(myRTC.dayofmonth);
    lcd.print(".");
    lcd.print(myRTC.month);
    lcd.print(".");
    lcd.print(myRTC.year);
    lcd.setCursor(6, 2);
    lcd.print(myRTC.hours);
    lcd.print(".");
    lcd.print(myRTC.minutes);
    lcd.print(".");
    lcd.print(myRTC.seconds);
    delay(1000);
  }
  else{
    lcd.clear();
    delay(1000);  
  }
}

long microsecondsToCentimeters(long microseconds){
  return microseconds / 29 / 2;
}
