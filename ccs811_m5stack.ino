#include <M5Stack.h>
#include "Adafruit_CCS811.h"

Adafruit_CCS811 ccs;

void playBeep() {
  M5.Speaker.beep();
  delay(100);
  M5.Speaker.mute();
}

void setup() {
  // put your setup code here, to run once:
  M5.begin();
  M5.Power.begin();
  M5.Lcd.setTextSize(3);
  M5.Lcd.println("Start!");
  
  pinMode(21, INPUT_PULLUP);
  pinMode(22, INPUT_PULLUP);

  pinMode(19, OUTPUT);
  digitalWrite(19, LOW);
  delay(50);

  delay(100);

  M5.Speaker.begin();
  M5.Speaker.setVolume(1);
  playBeep();
  delay(1000);

  if(!ccs.begin()){
    M5.Lcd.println("Failed to start sensor! Please check your wiring.");
    playBeep();
    delay(500);
    playBeep();
    while(1);
  }

  M5.Lcd.println("Success ccs.begin().");
  while(!ccs.available());
  ccs.readData();
  M5.Lcd.println("ccs.available().");

  playBeep();
  delay(500);
  M5.Lcd.fillScreen(BLACK);
}

void loop() {
  // put your main code here, to run repeatedly:

  if(ccs.available()){
    if(!ccs.readData()){
      //M5.Lcd.fillScreen(BLACK);
      M5.Lcd.setCursor(30, 30);
      M5.Lcd.print("CO2: ");
      M5.Lcd.print(ccs.geteCO2());
      M5.Lcd.print("ppm    ");
      M5.Lcd.setCursor(30, 60);
      M5.Lcd.print("TVOC: ");
      M5.Lcd.print(ccs.getTVOC());
      M5.Lcd.print("ppb   ");
      if (ccs.geteCO2() >= 3000) {
        playBeep();
        delay(200);
        playBeep();
        delay(200);
        playBeep();
        delay(200);
        playBeep();
        delay(200);
        playBeep();
      } else if (ccs.geteCO2() >= 2000) {
        playBeep();
        delay(300);
        playBeep();
        delay(300);
        playBeep();
      }
    }
    else{
      M5.Lcd.println("ERROR!");
      playBeep();
      delay(500);
      playBeep();
      while(1);
    }
  }
  digitalWrite(19, HIGH);
  delay(1*1000-100);
  digitalWrite(19, LOW);
  delay(100);
}
