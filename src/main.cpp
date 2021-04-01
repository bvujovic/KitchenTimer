#include <Arduino.h>
const byte pinLed = LED_BUILTIN;

#include "Timer.h"
Timer tim;

#include "ClickButton.h"
const byte pinBtnMin = A0;
ClickButton btnMin(pinBtnMin, LOW, CLICKBTN_PULLUP);
const byte pinBtnSec = A1;
ClickButton btnSec(pinBtnSec, LOW, CLICKBTN_PULLUP);
const byte pinBtnSS = A2;
ClickButton btnSS(pinBtnSS, LOW, CLICKBTN_PULLUP);

#include "Blinky.h"
const byte pinBuzz = 11;
Blinky buzz(pinBuzz, true, 333, 2);

ulong msAlarm = 0; // vreme pocetka alarma; 0 - alarm nije postavljen
bool on = false;

void ledOn(bool on) { digitalWrite(pinLed, on); }

void setup()
{
  pinMode(pinLed, OUTPUT);
  ledOn(false);
  pinMode(pinBuzz, OUTPUT);
  buzz.off();
  tim.refresh(0);
}

void loop()
{
  delay(10);
  ulong ms = millis();

  btnMin.Update();
  btnSec.Update();
  btnSS.Update();
  if (btnMin.clicks == 1) // min dugme dodaje 1 minut
    tim.addSec(60);
  if (btnMin.clicks == -1) // min dugme, dugi klik dodaje 10 minuta
    tim.addSec(10 * 60);
  if (btnSec.clicks == 1) // sec dugme dodaje 10 sekundi
    tim.addSec(10);
  if (btnSS.clicks == 1) // klik na Start/Stop dugme pokrece/zaustavlja odbrojavanje
    tim.startStop(ms);
  if (btnSS.clicks == -1) // dugi klik na Start/Stop dugme resetuje vreme na 00:00
    tim.resetSec();
  if (btnSS.clicks == 2) // dvostruki klik na Start/Stop dugme prebacuje odbrojavanje <-> brojanje
  {
    tim.toggleCountUpDown(ms);
    ledOn(!tim.getCountDown());
  }

  if (tim.refresh(ms)) // refresh displeja i pustanje zvuka ako je doslo vreme za to
    buzz.blink();
}