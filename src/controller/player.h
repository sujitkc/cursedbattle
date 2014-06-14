#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "user.h"

class Player : public User {
private: // methods
  Position getPlacementPosition(Vessel *);

public: // methods
  Player(Board*, GUIBoard*, Board*, GUIBoard*);
  virtual Coordinates getAttackCoordinates();
};
#endif
