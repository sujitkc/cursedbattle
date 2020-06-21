#ifndef SEGMENT_H
#define SEGMENT_H

#include <string>

#include "position.h"

using namespace std;
class Segment {
private:
  Position position;
  unsigned int length;
public:
  Segment(Position, unsigned int);
  Position getPosition();
  unsigned int getLength();
  void incrementLength();
  Coordinates getPreviousCell();
  Coordinates getNextCell();
  string toString();
};
#endif
