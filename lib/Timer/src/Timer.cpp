#include "Timer.h"

Timer::Timer()
{
  display = new TM1637Display(A5, A4); // (CLK, DIO)
  display->setBrightness(2);
}

void Timer::addSec(int x)
{
  sec += x;
  sec = constrain(sec, 0, MAX_SEC);
}

void Timer::startStop(unsigned long ms)
{
  if (!(isCountDown && sec == 0))
  {
    isRunning = !isRunning;
    msStart = ms;
  }
}

bool Timer::refresh(unsigned long ms)
{
  displayTime();

  if (!isRunning)
    return false;

  bool res = false;        // rezultat metoda - da li je vreme za alarm
  if (ms > msStart + 1000) // istekla sekunda?
  {
    sec = sec + (isCountDown ? -1 : +1);
    msStart += 1000;
    if (isCountDown && sec == 0)
    {
      isRunning = false;
      res = true;
      displayTime();
    }
  }

  return res;
}

void Timer::displayTime()
{
  if (lastSec != sec) // vreme se prikazuje samo kad se sec promenilo u odnosu na poslednji prikaz
  {
    int s = sec % 60;       // sekunde
    int m = (sec - s) / 60; // minuti
    display->showNumberDecEx(m * 100 + s, 0b01000000, true);
    lastSec = sec;
  }
}

void Timer::toggleCountUpDown(unsigned long ms)
{
  isCountDown = !isCountDown;
  if (!isCountDown) // ako se sada broji 0, 1, 2...
  {
    // vreme se resetuje i brojanje odmah krece
    sec = 0;
    msStart = ms;
    isRunning = true;
  }
}
