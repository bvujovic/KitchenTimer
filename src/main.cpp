#include <Arduino.h>

const byte pinLed = LED_BUILTIN;

#include <TM1637Display.h>
TM1637Display display(A5, A4); // (CLK, DIO)

#include "ClickButton.h"
const byte pinBtnMin = A0;
ClickButton btnMin(pinBtnMin, LOW, CLICKBTN_PULLUP);
const byte pinBtnSec = A1;
ClickButton btnSec(pinBtnSec, LOW, CLICKBTN_PULLUP);
const byte pinBtnSS = A2;
ClickButton btnSS(pinBtnSS, LOW, CLICKBTN_PULLUP);
//todo mozda dodati funkciju merenja vremena - vreme se ne odbrojava nego ide "nagore". pokrece se npr na dugi SS klik

int sec = 0; // ukupan broj sekundi vremena koje se prikazuje -> minuti*60 + sekunde

#include "Blinky.h"
const byte pinBuzz = 11;
Blinky buzz(pinBuzz, true, 500, 2);

ulong msAlarm = 0; // vreme pocetka alarma; 0 - alarm nije postavljen
bool on = false;

void ledOn(bool on) { digitalWrite(pinLed, on); }

// Prikaz vremena (minuti i sekunde) na displeju.
void refreshDisplay()
{
  if (sec > 99 * 60 + 59) // 99:59 je najvise sto u teoriji displej moze da prikaze
    sec = 0;
  int s = sec % 60;       // sekunde
  int m = (sec - s) / 60; // minuti
  display.showNumberDecEx(m * 100 + s, 0b01000000, true);
}

const int TEST_DELAY = 2000;

void setup()
{
  pinMode(pinLed, OUTPUT);
  ledOn(false);
  pinMode(pinBuzz, OUTPUT);
  buzz.off();
  //B digitalWrite(pinBuzz, false);
  display.setBrightness(2);
  //B display.showNumberDecEx(0, 0b01000000, true); // inicijalni prikaz 00:00
  refreshDisplay();

  // for (size_t i = 80; i < 120; i += 10)
  // {
  //   display.showNumberDecEx(i, 0b01000000, true);
  //   delay(TEST_DELAY);
  // }
  // display.clear();
}

void loop()
{
  delay(10);

  // rad sa tasterima
  btnMin.Update();
  btnSec.Update();
  btnSS.Update();
  if (btnMin.clicks == 1)
    sec += 60;
  if (btnSec.clicks == 1)
    sec += 10;
  if (btnMin.clicks == 1 || btnSec.clicks == 1)
    refreshDisplay();

  if (btnMin.clicks == 1)
    buzz.on();
  if (btnSec.clicks == 1)
    buzz.off();

  //   msAlarm = millis() + btn.clicks * 60 * 1000UL;

  // if (msAlarm != 0 && millis() > msAlarm)
  // {
  //   buzz.blink();
  //   msAlarm = 0;
  // }
}