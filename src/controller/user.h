#ifndef USER_H
#define USER_H

#include <string>

#include "position.h"
#include "vessel.h"
#include "board.h"
#include "guiboard.h"

using namespace std;

class User {
protected: // attributes
  const string name;

  Board* myBoard;
  Board* enemyBoard;

  GUIBoard* guiBoard;
  GUIBoard* enemyGUIBoard;

  Vessel* aircraftCarrier;
  Vessel* destroyer;
  Vessel* cruiser;
  Vessel* submarine;
  Vessel* patrol;

protected: // methods
  virtual void placeVessel(Vessel *);
  virtual Position getPlacementPosition(Vessel *) = 0;
  
public: // methods
  User(const string, Board *, GUIBoard*, Board*, GUIBoard*);
  ~User();
  string getName();
  virtual Coordinates getAttackCoordinates() = 0;
  void placeAllVessels();
  AttackResult takeTurn();
};
#endif
