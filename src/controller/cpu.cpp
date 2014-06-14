#include <stdlib.h>
#include <time.h>
#include <curses.h>
#include <iostream>
#include <algorithm>

#include "cpu.h"

using namespace std;

CPU::CPU(const string n, Board* b, GUIBoard* gb, Board* e, GUIBoard* ge) : User(n, b, gb, e, ge) {}

Position CPU::getPlacementPosition(Vessel* v) {
  Position p;
  srand(time(NULL));
  while(true) {
    const int x = rand() % 10;
    const int y = rand() % 10;
    Coordinates c(x, y);

    const int o = rand() % 4;
    switch(o) {
    case 0:
      p = Position(c, Position::TONORTH);
      break;
    case 1:
      p = Position(c, Position::TOEAST);
      break;
    case 2:
      p = Position(c, Position::TOSOUTH);
      break;
    case 3:
      p = Position(c, Position::TOWEST);
      break;
    }
    if(myBoard->isPositionAvailable(v, p)) {
      GUI::getInstance()->logEvent(name + " placing " + v->getName() + " at " + p.toString() + ".");
      return p;
    } 
  }
}

// Randomly select a coordinates to be attacked.
// Make sure that this cell hasn't been attacked earlier.
Coordinates CPU::getAttackCoordinates() {
  while(true) {
    const int x = rand() % 10;
    const int y = rand() % 10;
    Coordinates c(x, y);
    // if the newly generated point hasn't been attacked so far,
    // attack it.
    if(find ( attackedCoordinates.begin(),
              attackedCoordinates.end(),
              c
            ) == attackedCoordinates.end()) {
      attackedCoordinates.push_back(c);
      return c;
    }
  }
}

bool CPU::isAttacked(Coordinates c) {
  if(std::find(attackedCoordinates.begin(), attackedCoordinates.end(), c) == attackedCoordinates.end()) {
    return false;
  }
  return true;
}
