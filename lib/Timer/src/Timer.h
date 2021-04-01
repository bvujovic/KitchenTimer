#pragma once

#include <Arduino.h>
#include <TM1637Display.h>

// Objekat ove klase vodi racuna o protoku preostalog vremena tajmera i prikazu tog vremena na TM1637.
class Timer
{
private:
  int sec = 0;                      // ukupan broj sekundi vremena koje se prikazuje -> minuti*60 + sekunde
  int lastSec = -1;                 // vreme koje je poslednje prikazano na displeju
  const int MAX_SEC = 99 * 60 + 59; // 99:59 je najvise sto u teoriji displej moze da prikaze
  bool isRunning = false;           // true - tajmer radi, false - tajmer je pauziran
  bool isCountDown = true;          // true - sekunde se odbrojavaju (idu ka 0), false - brojanje od 0 navise
  unsigned long msStart;            // vreme pocetka brojanja/odbrojavanja
  TM1637Display *display;

  void displayTime(); // prikaz vremena na TM1637

public:
  Timer();
  bool getCountDown() { return isCountDown; }
  // Vreme koje ce tajmer odbrojavati u sekundama.
  int getSec() { return sec; }
  // Resetovanje vremena na 00:00, tj. postavljanje broja sekundi na 0.
  void resetSec()
  {
    sec = 0;
    isRunning = false;
  }
  // Dodavanje vremena u sekundama na zadato vreme tajmera.
  void addSec(int s);
  // Pokretanje ili zaustavljanje tajmera.
  void startStop(unsigned long ms);
  // Prikaz vremena (minuti i sekunde) na displeju. Vraca true ukoliko je vreme tajmera doslo do 0.
  bool refresh(unsigned long ms);
  // Prebacivanje modova odbrojavanje <-> brojanje
  void toggleCountUpDown(unsigned long ms);
};
