#include <time.h>
#include <iostream>
#include <algorithm>

#include "vessel.h"
#include "board.h"

using namespace std;
AttackResult::AttackResult(const AttackResult::State s, Coordinates c, Vessel* v)
  : state(s), coordinates(c), vessel(v) {}

AttackResult& AttackResult::operator = (AttackResult a){
  state       = a.state;
  coordinates = a.coordinates;
  vessel      = a.vessel;
  return *this;
}

AttackResult::State AttackResult::getState() { return state; }
Coordinates AttackResult::getCoordinates() { return coordinates; }

Coordinates Board::getSize() { return Coordinates(10, 10); }
// Set the position of vessel v to position p if the preconditions are met.
// Preconditions:
// - v belongs to this board.
// - v has already been placed.
void Board::placeVessel(Vessel* v) {
  if(v->getBoard() != this) {
    throw ActionNotAllowedException("Board::placeVessel", "Vessel doesn't belong to this board.");
  }
  if(std::find(vessels.begin(), vessels.end(), v) != vessels.end()) {
    throw ActionNotAllowedException("Board::placeVessel", "Vessel already placed.");
  }
  v->place();
  vessels.push_back(v);
}

// Tells if the position p is available for placing vessel v.
// Requires:
// - the vessel v should belong to this board.
// - the vessel v hasn't already been placed.
bool Board::isPositionAvailable(Vessel* v, Position p) {
  if(v->getBoard() != this) {  // if the vessel doesn't belong this board.
    return false;
  }
  if(std::find(vessels.begin(), vessels.end(), v) != vessels.end()) { // if the vessel has already been placed.
    return false;
  }
  vector<Coordinates> allCoordinates = v->computeCoordinates(p);
  for(unsigned int i = 0; i < allCoordinates.size(); i++) {
    Coordinates c = allCoordinates[i];
    if(!isWithinBoard(c)) {
      return false;
    }
    if(getVesselAtCoordinates(c) != NULL) {
      return false;
    }
  }
  return true;
}

// Tell if the given coordinates c are within the limits of the board.
bool Board::isWithinBoard(Coordinates c) {
  return
    ((0 <= c.getx()) && (c.getx() <= Board::getSize().getx() - 1))
    &&
    ((0 <= c.gety()) && (c.gety() <= Board::getSize().gety() - 1));
}

// Give the cell immediately to the north of the given coordinates c
// if it exists. Otherwise throw InvalidCoordinatesException.
// If the cell is at the northernmost(topmost) cell of a given column,
// return the southernmost (lowermost) cell of the column immediately
// to the west (left).
Coordinates Board::nextCellToNorth(Coordinates c) {
  if(c == Coordinates(0, 0)) {
    throw InvalidCoordinatesException(
      "Board::nextCellToNorth",
      "Past the top-left end of the board");
  }
  if(c.gety() == 0) {
    return Coordinates(c.getx() - 1, Board::getSize().gety() - 1);
  }
  return Coordinates(c.getx(), c.gety() - 1);
}

// Give the cell immediately to the east of the given coordinates c
// if it exists. Otherwise throw InvalidCoordinatesException.
// If the cell is at the easternmost(rightmost) cell of a given row,
// return the westernmost (leftmost) cell of the row immediately
// to the south (below).
Coordinates Board::nextCellToEast(Coordinates c) {
  Coordinates bottomRightCornerCell = Board::getSize() + Coordinates(-1, -1);
  if(c == bottomRightCornerCell) {
    throw InvalidCoordinatesException(
      "Board::nextCellToEast",
      "Past the bottom-right end of the board");
  }
  if(c.getx() == bottomRightCornerCell.getx()) {
    return Coordinates(0, c.gety() + 1);
  }
  return Coordinates(c.getx() + 1, c.gety());
}

// Give the cell immediately to the south of the given coordinates c
// if it exists. Otherwise throw InvalidCoordinatesException.
// If the cell is at the southernmost(lowermost) cell of a given column,
// return the southernmost (topmost) cell of the column immediately
// to the right (right).
Coordinates Board::nextCellToSouth(Coordinates c) {
  Coordinates bottomRightCornerCell = Board::getSize() + Coordinates(-1, -1);
  if(c == bottomRightCornerCell) {
    throw InvalidCoordinatesException(
      "Board::nextCellToSouth",
      "Past the bottom-right end of the board"
    );
  }
  if(c.gety() == bottomRightCornerCell.gety()) {
    return Coordinates(c.getx() + 1, 0);
  }
  return Coordinates(c.getx(), c.gety() + 1);
}

// Give the cell immediately to the west (left) of the given coordinates c
// if it exists. Otherwise throw InvalidCoordinatesException.
// If the cell is at the westernmost(leftmost) cell of a given row,
// return the easternmost (rightmost) cell of the row immediately
// to the north (top).
Coordinates Board::nextCellToWest(Coordinates c) {
  if(c == Coordinates(0, 0)) {
    throw InvalidCoordinatesException(
      "Board::nextCellToWest",
      "Past the top-left end of the board"
    );
  }
  if(c.getx() == 0) {
    return Coordinates(Board::getSize().getx() - 1, c.gety() - 1);
  }
  return Coordinates(c.getx() - 1, c.gety());
}

// Return the next cell to the north that available to v to be placed
// there.
// Precondition: v mustn't have already been placed.
Coordinates Board::nextAvailableCellToNorth(Vessel* v) {
  Position p = v->getPosition();
  while(true) {
    Coordinates nextCell = nextCellToNorth(p.getCoordinates());
    Position nextPos = Position(nextCell, p.getOrientation());
    if(isPositionAvailable(v, nextPos)) {
      return nextCell;
    }
    else {
      p = nextPos;
    }
  }
}
  
Coordinates Board::nextAvailableCellToEast(Vessel* v) {
  Position p = v->getPosition();
  while(true) {
    Coordinates nextCell = nextCellToEast(p.getCoordinates());
    Position nextPos = Position(nextCell, p.getOrientation());
    if(isPositionAvailable(v, nextPos)) {
      return nextCell;
    }
    else {
      p = nextPos;
    }
  }
}
  
Coordinates Board::nextAvailableCellToSouth(Vessel* v) {
  Position p = v->getPosition();
  while(true) {
    Coordinates nextCell = nextCellToSouth(p.getCoordinates());
    Position nextPos = Position(nextCell, p.getOrientation());
    if(isPositionAvailable(v, nextPos)) {
      return nextCell;
    }
    else {
      p = nextPos;
    }
  }
}  

Coordinates Board::nextAvailableCellToWest(Vessel* v) {
  Position p = v->getPosition();
  while(true) {
    Coordinates nextCell = nextCellToWest(p.getCoordinates());
    Position nextPos = Position(nextCell, p.getOrientation());
    if(isPositionAvailable(v, nextPos)) {
      return nextCell;
    }
    else {
      p = nextPos;
    }
  }
}  

// Return true if all the vessels in this board have been sunk.
bool Board::allSunk() {
  for(unsigned int i = 0; i < vessels.size(); i++) {
    if(vessels[i]->getState() != Vessel::SUNK) {
      return false;
    }
  }
  return true;
}

// Return the vessel to which the coordinates c belongs.
// Return NULL if c belongs to none of the vessels.
Vessel* Board::getVesselAtCoordinates(const Coordinates c) {
  for(vector<Vessel*>::iterator i = vessels.begin(); i != vessels.end(); i++) {
    if((*i)->hasCoordinates(c)) {
      return (*i);
    }
  }
  return NULL;
}

AttackResult Board::attack(const Coordinates c) {
  Vessel* v = getVesselAtCoordinates(c);
  if(v == NULL) {   // No vessel at c
    return AttackResult(AttackResult::MISS, c, NULL);
  }
  v->hit(c);
  if(allSunk()) {   // If all vessels are sunk. Game over for this board, basically.
    return AttackResult(AttackResult::ALLSUNK, c, v);
  }
  if(v->getState() == Vessel::SUNK) { // v is sunk.
    return AttackResult(AttackResult::SUNK, c, v);
  }
  return AttackResult(AttackResult::HIT, c, v);  // Otherwise, just a hit.
}
