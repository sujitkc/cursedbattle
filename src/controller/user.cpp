#include <stdlib.h>
#include <time.h>
#include <iostream>


#include "user.h"

using namespace std;
User::User(const string n, Board* b, GUIBoard* gb, Board* e, GUIBoard* ge)
  : name(n), myBoard(b), guiBoard(gb), enemyBoard(e), enemyGUIBoard(ge) {
  aircraftCarrier = new AircraftCarrier(myBoard);
  destroyer       = new Destroyer(myBoard)      ;
  cruiser         = new Cruiser(myBoard)        ;
  submarine       = new Submarine(myBoard)      ;
  patrol          = new Patrol(myBoard)         ;
}

User::~User() {
  delete aircraftCarrier;
  delete destroyer      ;
  delete cruiser        ;
  delete submarine      ;
  delete patrol         ;
}

string User::getName() { return name; }

void User::placeAllVessels() {
  placeVessel(aircraftCarrier);
  placeVessel(destroyer)      ;
  placeVessel(cruiser)        ;
  placeVessel(submarine)      ;
  placeVessel(patrol)         ;
}

void User::placeVessel(Vessel* v) {
  Position p = getPlacementPosition(v);
  v->setPosition(p);
  myBoard->placeVessel(v);
}

AttackResult User::takeTurn() {
  Coordinates c = getAttackCoordinates();
  AttackResult result = enemyBoard->attack(c);
  switch(result.getState()) {
  case AttackResult::MISS:
    enemyGUIBoard->putc('M', c);
    GUI::getInstance()->logEvent(name + " attacked at " + c.toString() + "; result : MISS.");
    break;
  case AttackResult::HIT:
    enemyGUIBoard->putc('H', c);
    GUI::getInstance()->logEvent(name + " attacked at " + c.toString() + "; result : HIT.");
    break;
  case AttackResult::SUNK:
  case AttackResult::ALLSUNK:
    Vessel* v = enemyBoard->getVesselAtCoordinates(c);
    enemyGUIBoard->drawVessel(v);
    GUI::getInstance()->logEvent(name + " attacked at " + c.toString() + "; result : SANK " + v->getName());
  }
  return result;
}
