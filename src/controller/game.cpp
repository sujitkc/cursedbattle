#include <iostream>
#include <string>
#include <fstream>

#include "user.h"
#include "board.h"
#include "vessel.h"
#include "gui.h"
#include "game.h"

using namespace std;
Game::Game() {
  playerBoard    = new Board();
  cpuBoard       = new Board()                            ;

  GUI* gui       = GUI::getInstance()                     ;
  Coordinates c1(10, 2);
  Coordinates c2(80, 2);
  playerGUIBoard = new GUIBoard(string("Player"), gui, c1);
  cpuGUIBoard    = new GUIBoard(string("Machine"), gui, c2)   ;
  player         = new Player(playerBoard, playerGUIBoard, cpuBoard, cpuGUIBoard);
  cpu            = new CPU(cpuBoard, cpuGUIBoard, playerBoard, playerGUIBoard)   ;
  playerGUIBoard->draw();
  cpuGUIBoard->draw();
}

Game::~Game() {
  delete player        ;
  delete cpu           ;
  delete playerBoard   ;
  delete cpuBoard      ;
  
  delete playerGUIBoard;
  GUIBoard* cpuGUIBoard;
}

// Run the game.
// - Both players place their vessels.
// - Get into the loop where each user takes its turn beginning with the player.
// - Break out when all the enemy vessels of current user are sunk.
void Game::run() {
  player->placeAllVessels();
  cpu->placeAllVessels();

  while(true) {
    AttackResult result = player->takeTurn();
    if(result.getState() == AttackResult::ALLSUNK) {
      (GUI::getInstance())->logEvent("Game over: " + player->getName() + " wins! Press a key to continue.");
      int inp = (GUI::getInstance())->getKeyboard()->getKey();
      break;
    }
    result = cpu->takeTurn();
    if(result.getState() == AttackResult::ALLSUNK) {
      (GUI::getInstance())->logEvent("Game over: " + cpu->getName() + " wins! Press a key to continue.");
      int inp = (GUI::getInstance())->getKeyboard()->getKey();
      break;
    }
  }
  GUI::getInstance()->showCursor(true);
  saveLog();
  GUI::getInstance()->shutdown();
}

void Game::saveLog() {
  ofstream fout;
  fout.open("../game.log");
  vector<string> logMessages = GUI::getInstance()->getAllLogMessage();
  for(unsigned int i = 0; i < logMessages.size(); i++) {
    fout << logMessages[i] << endl;
  }
  fout.close();
}
