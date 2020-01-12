#include <LiquidCrystal.h>
#include <virtuabotixRTC.h>
LiquidCrystal lcd(8, 7, 6, 5, 4, 3);
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
  pinMode(2, INPUT_PULLUP);
  myRTC.setDS1302Time(00, 54, 11, 5, 10, 1, 2020);

}

void loop() {
  int push;
  long duration, cm;
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  cm = microsecondsToCentimeters(duration);

  push = digitalRead(2);

  myRTC.updateTime();
  if(cm < 100 && push == HIGH){
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
  else if(push == LOW){
    lcd.clear();
    lcd.setCursor(2, 1);
    lcd.print("Now starting the");
    lcd.setCursor(0, 2);
    lcd.print("toothbrushing timer");
    delay(1000);
    lcd.clear();
    lcd.setCursor(8, 0);
    lcd.print("3...");
    delay(1000);
    lcd.setCursor(8, 1);
    lcd.print("2...");
    delay(1000);
    lcd.setCursor(8, 2);
    lcd.print("1...");
    delay(1000);
    lcd.setCursor(6, 3);
    lcd.print("!! GO !!");
    delay(1000);
    lcd.clear();
    countdown(3, 0, 8, 1);
    
  }
  else{
    lcd.clear();
    delay(1000);  
  }
}

long microsecondsToCentimeters(long microseconds){
  return microseconds / 29 / 2;
}

void countdown(int m, int s, int x, int y){
  while (1){
      if (s < 0){
        s = 59;
        m -= 1;
      }
      else if(m < 0){
        lcd.setCursor(5, y);
        lcd.print("Time's up!");
        delay(1000);
        break;
      }
      else{
        lcd.setCursor(x, y);
        lcd.print(m);
        lcd.print(".");
        lcd.print(s);
        delay(1000);
        lcd.clear();
        s -= 1;
      }
  }
}
