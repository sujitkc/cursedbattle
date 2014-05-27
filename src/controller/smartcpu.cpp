#include <stdlib.h>
#include <time.h>
#include <curses.h>
#include <iostream>

#include <algorithm>

#include "user.h"
#include "board.h"
#include "vessel.h"

#include "gui.h"
#include "keyboard.h"

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

CPU::CPU(Board* b, GUIBoard* gb, Board* e, GUIBoard* ge) : User("CPU", b, gb, e, ge) {}

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

Player::Player(Board* b, GUIBoard* gb, Board* e, GUIBoard* ge) : User("Player", b, gb, e, ge) {}

// Interact with the human player to place the given vessel v.
// Start by placing the vessel at the top-left cell or whichever cell is next available to its
// east.
Position Player::getPlacementPosition(Vessel* v) {
  Coordinates c = Coordinates(0, 0);
  Position::Orientation o = Position::TOEAST;
  Position p = Position(c, o);
  v->setPosition(p);
  if(!(myBoard->isPositionAvailable(v, p))) {
    c = myBoard->nextAvailableCellToEast(v);
  }
  p = Position(c, o);
  v->setPosition(p);
  guiBoard->drawVessel(v);
  while(true) {
    int inp = (GUI::getInstance())->getKeyboard()->getKey();
    switch(inp) {
    case '\n':  // for ENTER
    case 'q':
      GUI::getInstance()->logEvent(name + " placing " + v->getName() + " at " + p.toString() + ".");
      return v->getPosition();
    case KEY_UP:
      try {
        Coordinates nc = myBoard->nextAvailableCellToNorth(v);
        p = Position(nc, v->getPosition().getOrientation());
        v->setPosition(p);
        guiBoard->drawVessel(v);
      }
      catch(InvalidCoordinatesException e) {
        GUI::getInstance()->logEvent("Can't move any further north.");  
      }
      break;
    case KEY_DOWN:
      try {
        Coordinates nc = myBoard->nextAvailableCellToSouth(v);
        p = Position(nc, v->getPosition().getOrientation());
        v->setPosition(p);
        guiBoard->drawVessel(v);
      }
      catch(InvalidCoordinatesException e) {
        GUI::getInstance()->logEvent("Can't move any further south.");  
      }
      break;
    case KEY_RIGHT:
      try {
        Coordinates nc = myBoard->nextAvailableCellToEast(v);
        p = Position(nc, v->getPosition().getOrientation());
        v->setPosition(p);
        guiBoard->drawVessel(v);
      }
      catch(InvalidCoordinatesException e) {
        GUI::getInstance()->logEvent("Can't move any further east.");  
      }
      break;
    case KEY_LEFT:
      try {
        Coordinates nc = myBoard->nextAvailableCellToWest(v);
        p = Position(nc, v->getPosition().getOrientation());
        v->setPosition(p);
        guiBoard->drawVessel(v);
      }
      catch(InvalidCoordinatesException e) {
        GUI::getInstance()->logEvent("Can't move any further west.");  
      }
      break;
    case 'r': // Rotate clockwise
    {
      p = v->getPosition().rotateCW();
      if(myBoard->isPositionAvailable(v, p)) {
        v->setPosition(p);
        guiBoard->drawVessel(v);
      }
      else {
        GUI::getInstance()->logEvent("Can't rotate clockwise. Position not available");
      }
      break;
    }
    case 'R': // Rotate counter-clockwise
    {
      p = v->getPosition().rotateCCW();
      if(myBoard->isPositionAvailable(v, p)) {
        v->setPosition(p);
        guiBoard->drawVessel(v);
      }
      else {
        GUI::getInstance()->logEvent("Can't rotate counter-clockwise. Position not available");
      }
      break;
    }
    default:
      GUI::getInstance()->logEvent("Not a valid command.");
      break; 
    }
  }
  GUI::getInstance()->logEvent("placing " + v->getName() + " at " + v->getPosition().toString());
  return v->getPosition();
}


// Interact with the human player to determine the cell on the CPU board that
// will be attacked next.
Coordinates Player::getAttackCoordinates() {
  enemyGUIBoard->showCursor(true);
  while(true) {
    int inp = (GUI::getInstance())->getKeyboard()->getKey();
    switch(inp) {
    case '\n':  // for ENTER
    case 'q':
      return enemyGUIBoard->getCursorCoordinates();
    case KEY_UP:
      try {
        enemyGUIBoard->moveCursor(Position::TONORTH);
      }
      catch(ActionNotAllowedException e) {
        GUI::getInstance()->logEvent("Can't move any further north.");  
      }
      break;
    case KEY_DOWN:
      try {
        enemyGUIBoard->moveCursor(Position::TOSOUTH);
      }
      catch(ActionNotAllowedException e) {
        GUI::getInstance()->logEvent("Can't move any further south.");  
      }
      break;
    case KEY_RIGHT:
      try {
        enemyGUIBoard->moveCursor(Position::TOEAST);
      }
      catch(ActionNotAllowedException e) {
        GUI::getInstance()->logEvent("Can't move any further east.");  
      }
      break;
    case KEY_LEFT:
      try {
        enemyGUIBoard->moveCursor(Position::TOWEST);
      }
      catch(ActionNotAllowedException e) {
        GUI::getInstance()->logEvent("Can't move any further west.");  
      }
      break;
    default:
      break; 
    }
  }
}
