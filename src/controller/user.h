#ifndef USER_H
#define USER_H

#include <string>

#include "position.h"
#include "vessel.h"
#include "board.h"
#include "guiboard.h"
#include "gui.h"

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

class CPU : public User {
private: // attributes
  vector<Coordinates> attackedCoordinates;
private: // methods
  Position getPlacementPosition(Vessel *);
  
public: // methods
  CPU(Board*, GUIBoard*, Board*, GUIBoard*);
  virtual Coordinates getAttackCoordinates();
};

class Player : public User {
private: // methods
  Position getPlacementPosition(Vessel *);

public: // methods
  Player(Board*, GUIBoard*, Board*, GUIBoard*);
  virtual Coordinates getAttackCoordinates();
};
#endif
