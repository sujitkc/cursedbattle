#include <stdlib.h>
#include <time.h>
#include <curses.h>
#include <iostream>
#include <algorithm>

#include "player.h"

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
