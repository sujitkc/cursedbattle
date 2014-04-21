#include <iostream>
#include <stdio.h>
#include <memory.h>

#include "position.h"

using namespace std;

Coordinates::Coordinates() : x(0), y(0) {}
Coordinates::Coordinates(const int ax, const int ay) : x(ax), y(ay) {}
int Coordinates::getx() { return x; }
int Coordinates::gety() { return y; }
void         Coordinates::setx(const int ax) { x = ax; }
void         Coordinates::sety(const int ay) { y = ay; }

bool Coordinates::operator == (const Coordinates& c) { return (x == c.x && y == c.y); }
Coordinates& Coordinates::operator = (const Coordinates& c) { x = c.x ; y = c.y; return *this; }
Coordinates Coordinates::operator + (const Coordinates& c) { return Coordinates(x + c.x, y + c.y); }
Coordinates Coordinates::operator - (const Coordinates& c) { return Coordinates(x - c.x, y - c.y); }
bool Coordinates::operator < (const Coordinates& c) { return (x * x + y * y) < (c.x * c.x + c.y * c.y); }

string Coordinates::toString() {
  string s = "(";
  char strx[10];
  memset(strx, 10, 0);
  sprintf(strx, "%d", x);
  s += string(strx) + string(", ");
  char stry[10];
  memset(stry, 10, 0);
  sprintf(stry, "%d", y);
  s += string(stry) + string(")");
  return s;  
}

Position::Position() : coordinates(Coordinates(0, 0)), orientation(Position::TONORTH) {}
Position::Position(Coordinates c, Orientation o) : coordinates(c), orientation(o) {}
int Position::getx() { return coordinates.getx(); }
int Position::gety() { return coordinates.gety(); }
void         Position::setx(const int ax) { coordinates.setx(ax); }
void         Position::sety(const int ay) { coordinates.sety(ay); }
Coordinates Position::getCoordinates() { return coordinates; }
Position::Orientation Position::getOrientation() { return orientation; }
bool Position::operator == (const Position& p) { return (coordinates == p.coordinates && orientation == p.orientation); }
Position& Position::operator = (const Position& p) { coordinates = p.coordinates ; orientation = p.orientation; return *this; }

Position Position::rotateCW() {
  switch(orientation) {
  case TONORTH:
    return Position(coordinates, TOEAST);
  case TOEAST:
    return Position(coordinates, TOSOUTH);
  case TOSOUTH:
    return Position(coordinates, TOWEST);
  case TOWEST:
    return Position(coordinates, TONORTH);
  default:
    char stro[10];
    sprintf(stro, "%d", orientation);
    throw Exception("Position::rotateCW", "Invalid orientation " + string(stro));
  }
}

Position Position::rotateCCW() {
  switch(orientation) {
  case TONORTH:
    return Position(coordinates, TOWEST);
  case TOEAST:
    return Position(coordinates, TONORTH);
  case TOSOUTH:
    return Position(coordinates, TOEAST);
  case TOWEST:
    return Position(coordinates, TOSOUTH);
  default:
    char stro[10];
    sprintf(stro, "%d", orientation);
    throw Exception("Position::rotateCCW", "Invalid orientation " + string(stro));
  }
}

string Position::toString() {
  string s = "(";
  s += coordinates.toString() + ", ";

  switch (orientation) {
  case TONORTH:
    return s + "N)";
  case TOEAST:
    return s + "E)";
  case TOSOUTH:
    return s + "S)";
  case TOWEST:
    return s + "W)";
  }
  return s;
}


