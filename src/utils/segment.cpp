#include <stdio.h>

#include "segment.h"

Segment::Segment(Position p, const unsigned int l) : position(p), length(l) {}

Position Segment::getPosition()         { return position; }
unsigned int Segment::getLength()       { return length; }
void Segment::incrementLength() { length++; }

Coordinates Segment::getPreviousCell() {
  switch(position.getOrientation()) {
  case Position::TOSOUTH:
    return position.getCoordinates() + Coordinates(0, -1);
  case Position::TOEAST:
    return position.getCoordinates() + Coordinates(-1, 0);
  }
}

Coordinates Segment::getNextCell() {
  switch(position.getOrientation()) {
  case Position::TOSOUTH:
    return position.getCoordinates() + Coordinates(0, length);
  case Position::TOEAST:
    return position.getCoordinates() + Coordinates(length, 0);
  }
}

string Segment::toString() {
  char strlength[10];
  sprintf(strlength, "%u", length);
  return "(" + position.toString() + ", " + strlength + ")";
}
