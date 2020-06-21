#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "guiboard.h"
#include "user.h"

class Game {
public:
  enum Level {
    BASIC,
    ADVANCED
  };

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
  static Level selectLevel();
public:
  Game();
  ~Game();
  void run();
};
#endif //GAME_H
