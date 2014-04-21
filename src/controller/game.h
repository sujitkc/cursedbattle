#ifndef GAME_H
#define GAME_H

#include "guiboard.h"
#include "user.h"

class Game {
private:
  User* player;
  User* cpu;
  Board* playerBoard;
  Board* cpuBoard;
 
  GUI* gui;
  GUIBoard* playerGUIBoard;
  GUIBoard* cpuGUIBoard;

private:
  void saveLog();

public:
  Game();
  ~Game();
  void run();
};
#endif //GAME_H
