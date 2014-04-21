#ifndef VESSEL_H
#define VESSEL_H

#include <string>
#include <vector>
#include <map>

#include "position.h"
#include "exception.h"

using namespace std;
class Board;

class Vessel {
public:
  enum State {
    NOTPLACED,
    AFLOAT,
    SUNK
  };

  enum CoordinatesState {
    NOTHIT,
    HIT
  };
private:
  const string name;
  State state;
  Board* board;
  vector<CoordinatesState> coordinatesStates;
protected:
  const unsigned int length;
  Position position;
public:
  Vessel(string, Board*, const unsigned int);
  virtual unsigned int getLength();
  State getState();
  string getName();
  Board* getBoard();
  Position getPosition();
  vector<Coordinates> computeCoordinates(const Position);
  vector<Coordinates> getAllCoordinates();

  void setPosition(Position);

  CoordinatesState getCoordinatesState(const Coordinates);
  bool hasCoordinates(const Coordinates c);
  void place();
  void hit(const Coordinates);

private:
  bool isSunk();
  unsigned int coordinatesIndex(const Coordinates);
};

class AircraftCarrier : public Vessel {
public:
  AircraftCarrier(Board*);
};

class Destroyer : public Vessel {
public:
  Destroyer(Board*);
};

class Cruiser : public Vessel {
public:
  Cruiser(Board*);
};

class Submarine : public Vessel {
public:
  Submarine(Board*);
};

class Patrol : public Vessel {
public:
  Patrol(Board*);
};
#endif
