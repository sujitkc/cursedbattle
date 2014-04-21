#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>                  /*  for sleep()  */
#include <curses.h>
#include <string>

#include "gui.h"

using namespace std;

void GUI::printInstructions(vector<string> instructions, Coordinates origin) {
  for(unsigned int i = 0; i < instructions.size(); i++) {
    mvaddstr(origin.gety() + i, origin.getx(), instructions[i].c_str());
  }
}

void GUI::printPlacementInstructions() {
  vector<string> instructions;
  instructions.push_back(	"Placement Instructions:");
  instructions.push_back("-----------------------");
  instructions.push_back(	" * A - Aircraft Carrier; D - Destroyer;");
  instructions.push_back(	" * C - Cruiser; S - Submarine; P - Patrol.");
  instructions.push_back(	" * Use arrow keys to navigate to the desired position.");
  instructions.push_back(	" * Press 'r' to change the orientation of the vessel.");
  instructions.push_back(	" * Press ENTER to commit the position of the vessel.");
  instructions.push_back(	" * NOTE: Once committed, the vessel position can't be changed.");
  Coordinates origin(5, 23);
  printInstructions(instructions, origin);
}

void GUI::printAttackInstructions() {
  vector<string> instructions;
  instructions.push_back("Attack Instructions:");
  instructions.push_back("--------------------");
  instructions.push_back(" * Use arrow keys to navigate to the desired position.");
  instructions.push_back(" * Press ENTER to attack the current position.");
  instructions.push_back(" * H - Hit; M - Miss; X - Sink");
  Coordinates origin(70, 23);
  printInstructions(instructions, origin);
}

void GUI::printInstructions() {
  printPlacementInstructions();
  printAttackInstructions();
}

GUI::GUI() {
    /*  Initialize ncurses  */

  if ( (window = initscr()) == NULL ) {
    fprintf(stderr, "Error initialising ncurses.\n");
    exit(EXIT_FAILURE);
  }

  keyboard = new Keyboard(window);
  printInstructions();
}

GUI* GUI::gui = NULL;
GUI* GUI::getInstance() {
  if(gui == NULL) {
    gui = new GUI();
  }
  return gui;
}

GUI::~GUI() {
  delwin(window);
  endwin();
  refresh();
}

Keyboard* GUI::getKeyboard() { return keyboard; }

void GUI::putc(char c, Coordinates coord) {
  char s[2];
  sprintf(s, "%c", c);
  string m = string(s);
  printMessage(m, coord);
}

void GUI::printMessage(string m, Coordinates c) {
  mvaddstr(c.gety(), c.getx(), m.c_str());
}

void GUI::putCursor(Coordinates c) {
  move(c.gety(), c.getx());
}

void GUI::showCursor(bool c) {
  if(c == true) {
    curs_set(1);
  }
  else {
    curs_set(0);
  }
}

Coordinates GUI::getCursorCoordinates() {
  int x, y;
  getyx(window, y, x);
  return Coordinates(x, y);
}

void GUI::logEvent(string m) {
  Coordinates coord = getCursorCoordinates();
  Coordinates c = Coordinates(20, 35);
  string emptyMessage = "                                                                      ";
  printMessage(emptyMessage, c);
  printMessage(m, c);
  putCursor(coord);
  logMessages.push_back(m);
}

vector<string> GUI::getAllLogMessage() { return logMessages; }

void GUI::shutdown() {
  delwin(window);
  endwin();
  refresh();

}
