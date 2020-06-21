#include <iostream>
#include <string>
#include <fstream>

#include "cpu.h"
#include "smartcpu.h"
#include "basiccpu.h"
#include "player.h"
#include "gui.h"
#include "listpanel.h"
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
  Level level    = Game::selectLevel();
  if(level == BASIC) {
    cpu          = new BasicCPU(cpuBoard, cpuGUIBoard, playerBoard, playerGUIBoard)   ;
  }
  else {
    cpu          = new SmartCPU(cpuBoard, cpuGUIBoard, playerBoard, playerGUIBoard)   ;
  }
  playerGUIBoard->draw();
  cpuGUIBoard->draw();
  gui->printInstructions();
}

Game::~Game() {
  delete player        ;
  delete cpu           ;
  delete playerBoard   ;
  delete cpuBoard      ;
  
  delete playerGUIBoard;
  GUIBoard* cpuGUIBoard;
}

Game::Level Game::selectLevel() {
  GUI::getInstance()->clear();
  GUI::getInstance()->showCursor(false);
  vector<string> levels;
  levels.push_back("BASIC    - work hard to lose");
  levels.push_back("ADVANCED - work hard to win");
  ListPanel listPanel("Select Level", GUI::getInstance(), Coordinates(40, 20), levels);
  listPanel.draw();
  while(true) {
    int inp = (GUI::getInstance())->getKeyboard()->getKey();
    const unsigned int selectedIndex = listPanel.getSelectedIndex();
    switch(inp) {
    case '\n':  // for ENTER
    case 'q':
      GUI::getInstance()->clear();
      switch(selectedIndex) {
      case 0:
        return BASIC;
      case 1:
      default:
        return ADVANCED;
      }
      break;
    case KEY_UP:
      listPanel.selectPreviousIndex();
      break;
    case KEY_DOWN:
      listPanel.selectNextIndex();
      break;
    default:
      break; 
    }
  }
}

// Run the game.
// - Both players place their vessels.
// - Get into the loop where each user takes its turn beginning with the player.
// - Break out when all the enemy vessels of current user are sunk.
void Game::run() {
  player->placeAllVessels();
  cpu->placeAllVessels();
  string winner = "";
  while(true) {
    try {
      AttackResult result = player->takeTurn();
      if(result.getState() == AttackResult::ALLSUNK) {
        winner = player->getName();
        break;
      }
      result = cpu->takeTurn();
      if(result.getState() == AttackResult::ALLSUNK) {
        winner = cpu->getName();
        break;
      }
    }
    catch(ActionNotAllowedException e) {
    }
  }
//  (GUI::getInstance())->clear();
  (GUI::getInstance())->logEvent("Game over: " + winner + " wins! Press a key to continue.");
  int inp = (GUI::getInstance())->getKeyboard()->getKey();
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
