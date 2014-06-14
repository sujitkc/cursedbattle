#ifndef BOARD_H
#define BOARD_H

#include <vector>

#include "position.h"
#include "vessel.h"
#include "modelexceptions.h"

class AttackResult {
public:
  enum State {
    MISS,
    HIT,
    SUNK,
    ALLSUNK
  };
private:
  State state;
  Coordinates coordinates;
  Vessel* vessel;
public:
  AttackResult(const State, Coordinates, Vessel*);
  State getState();
  Coordinates getCoordinates();
  Vessel* getVessel();
  virtual AttackResult& operator = (AttackResult);
};

using namespace std;

class Vessel;
class Board {
public:
  static Coordinates getSize();
private:
  vector<Vessel*> vessels;
public:
  Vessel* getVesselAtCoordinates(const Coordinates);
  void placeVessel(Vessel*);
  bool isPositionAvailable(Vessel* v, Position);
  AttackResult attack(const Coordinates);

  Coordinates nextCellToNorth(Coordinates);
  Coordinates nextCellToEast(Coordinates);
  Coordinates nextCellToSouth(Coordinates);
  Coordinates nextCellToWest(Coordinates);
  
  Coordinates nextAvailableCellToNorth(Vessel*);
  Coordinates nextAvailableCellToEast(Vessel*);
  Coordinates nextAvailableCellToSouth(Vessel*);
  Coordinates nextAvailableCellToWest(Vessel*);
  bool isWithinBoard(Coordinates);
private:
  bool allSunk();
};
#endif
