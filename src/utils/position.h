#ifndef POSITION_H
#define POSITION_H
#include <string>

#include "exception.h"

using namespace std;

class Coordinates {
private:
  int x;
  int y;

public:
  Coordinates();
  Coordinates(const int, const int);
  int getx();
  int gety();
  void setx(const int);
  void sety(const int);
  bool operator == (const Coordinates&);
  Coordinates& operator = (const Coordinates&);
  Coordinates operator + (const Coordinates&);
  Coordinates operator - (const Coordinates&);
  bool operator < (const Coordinates&);
  string toString();
};

class Position {
public:
  enum Orientation {
    TONORTH,
    TOEAST,
    TOSOUTH,
    TOWEST
  };

private:
  Coordinates coordinates;
  Orientation orientation;

public:
  Position();
  Position(Coordinates, Orientation);
  int getx();
  int gety();
  void setx(const int);
  void sety(const int);
  Coordinates getCoordinates();
  Orientation getOrientation();
  bool operator == (const Position&);
  Position& operator = (const Position&);
  Position rotateCW();
  Position rotateCCW();
  string toString();
};
#endif
