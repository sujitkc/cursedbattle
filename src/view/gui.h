#ifndef GUI_H
#define GUI_H

#include <curses.h>
#include <vector>

#include "position.h"
#include "keyboard.h"

using namespace std;
class GUI {
private:
  static GUI* gui;
private:
  WINDOW* window;
  Keyboard *keyboard;
  vector<string> logMessages;
private:
  // privatised for singleton pattern
  GUI();

  void gameOver();
  void printInstructions(vector<string>, Coordinates);
  void printPlacementInstructions();
  void printAttackInstructions();

public:
  ~GUI();
  static GUI* getInstance();
  Keyboard* getKeyboard();
  void clear();
  void draw();
  void putc(char, Coordinates);
  void printMessage(string, Coordinates);
  void putCursor(Coordinates);
  void printInstructions();
  void logEvent(string);
  Coordinates getCursorCoordinates();
  void showCursor(bool);
  vector<string> getAllLogMessage();
  void shutdown();
};
#endif
