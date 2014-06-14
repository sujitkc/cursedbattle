#include <stdlib.h>
#include <fstream>
#include <time.h>
#include <algorithm>

#include "vessel.h"
#include "board.h"
#include "smartcpu.h"

using namespace std;

SmartCPU::SmartCPU(Board* b, GUIBoard* gb, Board* e, GUIBoard* ge) : CPU("Smart CPU", b, gb, e, ge) {
  startingPositions.push_back(Position(Coordinates(0, 0), Position::TOSOUTH));
  startingPositions.push_back(Position(Coordinates(1, 0), Position::TOSOUTH));
  startingPositions.push_back(Position(Coordinates(2, 0), Position::TOSOUTH));
  startingPositions.push_back(Position(Coordinates(3, 0), Position::TOSOUTH));
  startingPositions.push_back(Position(Coordinates(4, 0), Position::TOSOUTH));
  startingPositions.push_back(Position(Coordinates(5, 0), Position::TOSOUTH));
  startingPositions.push_back(Position(Coordinates(6, 0), Position::TOSOUTH));
  startingPositions.push_back(Position(Coordinates(7, 0), Position::TOSOUTH));
  startingPositions.push_back(Position(Coordinates(8, 0), Position::TOSOUTH));
  startingPositions.push_back(Position(Coordinates(9, 0), Position::TOSOUTH));
  startingPositions.push_back(Position(Coordinates(0, 0), Position::TOEAST));
  startingPositions.push_back(Position(Coordinates(0, 1), Position::TOEAST));
  startingPositions.push_back(Position(Coordinates(0, 2), Position::TOEAST));
  startingPositions.push_back(Position(Coordinates(0, 3), Position::TOEAST));
  startingPositions.push_back(Position(Coordinates(0, 4), Position::TOEAST));
  startingPositions.push_back(Position(Coordinates(0, 5), Position::TOEAST));
  startingPositions.push_back(Position(Coordinates(0, 6), Position::TOEAST));
  startingPositions.push_back(Position(Coordinates(0, 7), Position::TOEAST));
  startingPositions.push_back(Position(Coordinates(0, 8), Position::TOEAST));
  startingPositions.push_back(Position(Coordinates(0, 9), Position::TOEAST));
}

// Algorithm:
// If there exist hit-and-not-sunk segments which are extensible,
// - select the longest.
// - return the attackable cell on either end.
// If extensible hit-and-not-sunk segments don't exist, then
// use the basic CPU's random algorithm:
// - Randomly select a coordinates to be attacked.
// - Make sure that this cell hasn't been attacked earlier.
Coordinates SmartCPU::getAttackCoordinates() {
  vector<Segment> extensibleSegments = filterExtensibleSegments(getHitSegments());
  if(extensibleSegments.size() != 0) {
    Coordinates attackedCell;
    Segment s = getLongestExtensibleSegment(extensibleSegments);
    if(canBeAttacked(s.getPreviousCell())) {
      attackedCell = s.getPreviousCell();
    }
    else {
      attackedCell = s.getNextCell();
    }
    attackedCoordinates.push_back(attackedCell);
    return attackedCell;
  }
  else {
    return CPU::getAttackCoordinates();
  }
}

// Of all the extensible hit-and-not-sunk segments, pick one of the longest ones.
Segment SmartCPU::getLongestExtensibleSegment(vector<Segment> hitSegments) {
  Segment max(Position(Coordinates(0, 0), Position::TOSOUTH), 0);
  for(unsigned int i = 0; i < hitSegments.size(); i++) {
    if(max.getLength() <= hitSegments[i].getLength()) {
      max = hitSegments[i];
    }
  }
  return max;
}

// Return the list of all the segments which are hit and not sunk on the enemy board.
vector<Segment> SmartCPU::getHitSegments() {
  vector<Segment> hitSegments;
  for(unsigned int i = 0; i < startingPositions.size(); i++) {
      vector<Segment> restOfIt;
      if(isHitNotSunk(startingPositions[i].getCoordinates())) {
        restOfIt.push_back(Segment(startingPositions[i], 0)); //state a new hit-segment
        cellHit(restOfIt, startingPositions[i]);
      }
      else {
        cellNotHit(restOfIt, startingPositions[i]);
      }
      hitSegments.insert(hitSegments.end(), restOfIt.begin(), restOfIt.end());
  }
/*
  ofstream fout;
  fout.open("../segments.txt");
  for(unsigned int i = 0; i < hitSegments.size(); i++) {
    fout << hitSegments[i].toString() << endl;
  }
  fout.close();
*/
  return hitSegments;
}

// Return true if the cell is a valid one and hasn't been attacked.
bool SmartCPU::canBeAttacked(Coordinates c) {
  if(!enemyBoard->isWithinBoard(c)) return false;
  if(isAttacked(c))                 return false;
  return true;
}

// If a segment has an attackable cell on either end, it is extensible.
bool SmartCPU::isExtensible(Segment s) {
    if(canBeAttacked(s.getPreviousCell())) return true;
    if(canBeAttacked(s.getNextCell()))     return true;
}

// Out of the list of hit and not sunk segments, filter out those which are
// extensible.
vector<Segment> SmartCPU::filterExtensibleSegments(vector<Segment> segments) {
  vector<Segment> extensibleSegments;
  for(unsigned int i = 0; i < segments.size(); i++) {
    if(isExtensible(segments[i])) {
      extensibleSegments.push_back(segments[i]);
    }
  }
  return extensibleSegments;
}

// Return true if the given cell has been hit (i.e. has been attacked and there's a vessel there),
// but the vessel there hasn't sunk.
bool SmartCPU::isHitNotSunk(Coordinates coord) {
  if(!isAttacked(coord)) {
    return false;
  }
  Vessel *v = enemyBoard->getVesselAtCoordinates(coord);
  if(v == NULL) {
    return false;
  }
  if(v->getState() == Vessel::SUNK) {
    return false;
  }
  return true;
}

// If exploring a column (orientation = TOSOUTH), then return true if at the last row.
// If exploring a row (orientation = TOEAST), then return true if at the last column.
bool SmartCPU::isLastPosition(Position p) {
  Coordinates c = p.getCoordinates();
  switch(p.getOrientation()) {
  case Position::TOSOUTH:
    return c.gety() == enemyBoard->getSize().gety();  // if last row
  case Position::TOEAST:
    return c.getx() == enemyBoard->getSize().getx();  // if last column
  }
}

// If exploring a column (orientation = TOSOUTH), then return position to the south
// If exploring a row (orientation = TOEAST), then return position to the east.
Position SmartCPU::getNextPosition(Position p) {
  Coordinates nextCell = p.getCoordinates();
  switch(p.getOrientation()) {
  case Position::TOSOUTH:
    nextCell = p.getCoordinates() + Coordinates(0, 1); // next cell to the south
    break;
  case Position::TOEAST:
    nextCell = p.getCoordinates() + Coordinates(1, 0); // next cell to the east
    break;
  }
  return  Position(nextCell, p.getOrientation());
}

// State function when not in hit-segment.
void SmartCPU::cellNotHit(vector<Segment>& segments, Position pos) {
  if(isLastPosition(pos)) {
    return;
  }
  Position nextPos = getNextPosition(pos);
  if(isHitNotSunk(nextPos.getCoordinates())) { // going to enter a new hit-segment
    segments.push_back(Segment(nextPos, 0)); //state a new hit-segment
    cellHit(segments, nextPos); // transition to cellHit state.
  }
  else {
    cellNotHit(segments, nextPos);
  }
}

// State function when in hit-segment.
void SmartCPU::cellHit(vector<Segment>& segments, Position pos) {
  segments[segments.size() - 1].incrementLength();
  if(isLastPosition(pos)) {
    return;
  }
  Coordinates nextCell = pos.getCoordinates();
  Position nextPos = getNextPosition(pos);
  if(isHitNotSunk(nextPos.getCoordinates())) {  // continuing in the current hit-segment.
    cellHit(segments, nextPos); // continue in the cellHit state
  }
  else {
    cellNotHit(segments, nextPos);  // exit the hit-segment
  }
}
