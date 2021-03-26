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
//todo mozda dodati funkciju merenja vremena - vreme se ne odbrojava nego ide "nagore". pokrece se npr na dugi SS klik

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
    tim.startStop(millis());
  if (btnSS.clicks == -1) // dugi klik na Start/Stop dugme resetuje vreme na 00:00
    tim.resetSec();
  if (btnSS.clicks == 2) // dvostruki klik na Start/Stop dugme prebacuje odbrojavanje <-> brojanje
  {
    tim.toggleCountUpDown();
    ledOn(!tim.getCountDown());
  }

  if (tim.refresh(millis())) // refresh displeja i pustanje zvuka ako je doslo vreme za to
    buzz.blink();
}