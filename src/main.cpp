#include <Arduino.h>

const byte pinLed = LED_BUILTIN;

#include "ClickButton.h"
const byte pinBtn = 10;
ClickButton btn(pinBtn, LOW, CLICKBTN_PULLUP);

#include "Blinky.h"
const byte pinBuzz = 12;
Blinky buzz(pinBuzz, true, 500, 2);

ulong msAlarm = 0; // vreme pocetka alarma; 0 - alarm nije postavljen
bool on = false;

void ledOn(bool on) { digitalWrite(pinLed, on); }

void setup()
{
  pinMode(pinLed, OUTPUT);
  ledOn(false);
  pinMode(pinBuzz, OUTPUT);
  digitalWrite(pinBuzz, false);
}

void loop()
{
  delay(10);

  btn.Update();

  if (btn.clicks >= 1)
    msAlarm = millis() + btn.clicks * 60 * 1000UL;

  if (msAlarm != 0 && millis() > msAlarm)
  {
    buzz.blink();
    msAlarm = 0;
  }
}