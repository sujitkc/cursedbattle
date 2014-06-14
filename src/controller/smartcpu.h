#ifndef SMARTCPU_H
#define SMARTCPU_H

#include <string>
#include <vector>

#include "cpu.h"
#include "position.h"
#include "segment.h"

using namespace std;
class SmartCPU : public CPU {
private:
  vector<Position> startingPositions;
public: // methods
  SmartCPU(Board*, GUIBoard*, Board*, GUIBoard*);
  virtual Coordinates getAttackCoordinates();

private:
  Segment getLongestExtensibleSegment(vector<Segment>);
  vector<Segment> getHitSegments();
  bool canBeAttacked(Coordinates);
  bool isExtensible(Segment);
  vector<Segment> filterExtensibleSegments(vector<Segment>);
  bool isHitNotSunk(Coordinates);
  bool isLastPosition(Position);
  Position getNextPosition(Position);
  void cellNotHit(vector<Segment>&, Position);
  void cellHit(vector<Segment>&, Position);
};
#endif
