#ifndef CPU_H
#define CPU_H

#include <string>

#include "user.h"

class CPU : public User {
protected: // attributes
  vector<Coordinates> attackedCoordinates;
protected: // methods
  Position getPlacementPosition(Vessel *);
  bool isAttacked(Coordinates);  
public: // methods
  CPU(const string, Board*, GUIBoard*, Board*, GUIBoard*);
  virtual Coordinates getAttackCoordinates();
};
#endif
