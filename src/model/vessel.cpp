#include <algorithm>
#include <vector>
#include <map>
#include <string>

#include "vessel.h"
#include "board.h"
#include "modelexceptions.h"
#include "position.h"

using namespace std;

Vessel::Vessel(string n, Board* b, const unsigned int l) : name(n), board(b), length(l), state(Vessel::NOTPLACED) {
  for(unsigned int i = 0; i < length; i++) {
    coordinatesStates.push_back(Vessel::NOTHIT);
  }
}

Vessel::State Vessel::getState()    { return state;    }
Board*        Vessel::getBoard()    { return board;    }
string        Vessel::getName()     { return name;     }
unsigned int  Vessel::getLength()   { return length;   }
Position      Vessel::getPosition() { return position; }

// Given a position, return the set of coordinates which the vessel would occupy if
// occupying that position.
// Note: p needn't be the position that vessel is currently occupying. It could be
// any valid on the board.
vector<Coordinates> Vessel::computeCoordinates(Position p) {
  vector<Coordinates> coord;
  for(unsigned int i = 0; i < length; i++) {
    switch(p.getOrientation()) {
    case Position::TONORTH:
      coord.push_back(Coordinates(p.getCoordinates().getx()    , p.getCoordinates().gety() - i));
      break;
    case Position::TOEAST:
      coord.push_back(Coordinates(p.getCoordinates().getx() + i, p.getCoordinates().gety())    );
      break;
    case Position::TOSOUTH:
      coord.push_back(Coordinates(p.getCoordinates().getx()    , p.getCoordinates().gety() + i));
      break;
    case Position::TOWEST:
      coord.push_back(Coordinates(p.getCoordinates().getx() - i, p.getCoordinates().gety())    );
      break;
    }
  }
  return coord;
}

// return all the coordinates belonging to this vessel.
vector<Coordinates> Vessel::getAllCoordinates() { 
  return computeCoordinates(position);
}

// Set the position of the vessel to p.
// Precondition: Vessel shouldn't already have been placed.
void Vessel::setPosition(Position p) {
  if(state != NOTPLACED) {
    throw ActionNotAllowedException(
      "Vessel::setPosition",
      "The position of a vessel already placed can't be set again."
    );
  }
  position = p;
}

// Set the position of this vessel to position p if the preconditions are met.
// Preconditions:
// - The vessel hasn't been placed already.
// - The position p is available.
//
void Vessel::place() {
  if(getState() != NOTPLACED) {
    throw new Exception("Vessel::place", "Failed. Vessel " + name + " already placed.");
  }
  if(!board->isPositionAvailable(this, position)) {
    throw new Exception("Vessel::place", "Failed. Infeasible position.");
  }

  state = AFLOAT;
}

// Return the index of coordinates c w.r.t to the first coordinate occupied by this
// vessel.
// If c doesn't belong to this vessel, throw an InvalidCoordinatesException.
unsigned int Vessel::coordinatesIndex(Coordinates c) {
  vector<Coordinates> allCoordinates = getAllCoordinates();
  for(unsigned int i = 0; i < allCoordinates.size(); i++) {
    if(allCoordinates[i] == c) {
      return i;
    }
  }
  throw InvalidCoordinatesException(
    "Vessel::coordinatesIndex",
    "The given coordinates don't belong to the this vessel."
  );
}

// Return the state of the point specified by c.
// Throw an exception if the point doesn't belong to the vessel.
Vessel::CoordinatesState Vessel::getCoordinatesState(const Coordinates c) {
  try {
    unsigned int i = coordinatesIndex(c);
    return coordinatesStates[i];
  }
  catch(InvalidCoordinatesException e) {
   throw InvalidCoordinatesException(
    "Vessel::getCoordinatesState",
    e.getMessage()
   );
  }

}

// Return true if coordinate c is contained within the vessel.
bool Vessel::hasCoordinates(const Coordinates c) {
  try {
    coordinatesIndex(c);
    return true;
  }
  catch(InvalidCoordinatesException e) {
    return false;
  }
}
// Change the coordinateState at c to HIT if the preconditions are met.
// Preconditions:
// - If the vessel is not afloat
// - If the coordinates c isn't contained within the vessel.
void Vessel::hit(const Coordinates c) {
  if(state != AFLOAT) {
    throw ActionNotAllowedException("Vessel::hit", "The vessel is not in a state wherein it can be hit.");
  }
  if(!hasCoordinates(c)) {
    throw InvalidCoordinatesException("Vessel::hit", "The given coordinates don't belong to the this vessel.");
  }
  coordinatesStates[coordinatesIndex(c)] = HIT;

  // change state to SUNK if all coordinates have been hit.
  for(unsigned int i = 0; i < length; i++) {
    if(coordinatesStates[i] == NOTHIT) {
      return;
    }
  }
  state = SUNK;
}

AircraftCarrier::AircraftCarrier(Board* b) : Vessel ("Aircraft Carrier", b, 5) {}

Destroyer::Destroyer(Board* b) : Vessel("Destroyer", b, 4) {}

Cruiser::Cruiser(Board* b)     : Vessel("Cruiser", b, 3) {}

Submarine::Submarine(Board* b) : Vessel("Submarine", b, 3) {}

Patrol::Patrol(Board* b)       : Vessel("Patrol", b, 2) {}
