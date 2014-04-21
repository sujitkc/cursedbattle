#ifndef GUIBOARD_H
#define GUIBOARD_H
#include <string>
#include <map>

#include "vessel.h"
#include "gui.h"
#include "position.h"
#include "modelexceptions.h"

using namespace std;
class GUIBoard {
public:
/*
  enum Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT
  };
*/
private:
  string name;
  Coordinates origin;
  static Coordinates size; // size in terms of the GUI real-estate
  Coordinates cursorCoordinates;
  GUI* gui;
  map<Vessel*, Position> vesselPositions;
public:
  GUIBoard(string n, GUI*, Coordinates c);
  void showCursor(bool);
  void draw();
  Coordinates getCursorCoordinates();
  void putc(char, Coordinates);
  void putCursor(Coordinates);
  void moveCursor(Position::Orientation);
  Coordinates boardToGUI(Coordinates);
  void eraseVessel(Vessel *);
  void drawVessel(Vessel *);
private:
  void drawHorizontalLine(Coordinates, const unsigned int, char);
  void drawVerticalLine(Coordinates, const unsigned int, char);
  void drawGrid();
  void drawBorders();
};
#endif
