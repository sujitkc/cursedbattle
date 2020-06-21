#ifndef GUIPANEL_H
#define GUIPANEL_H
#include <string>
#include <map>

#include "gui.h"
#include "position.h"

using namespace std;
class GUIPanel {
protected:
  string name;
  Coordinates origin;
  Coordinates size; // size in terms of the GUI real-estate
  Coordinates cursorCoordinates;
  GUI* gui;
public:
  GUIPanel(string n, GUI*, Coordinates, Coordinates);
  void showCursor(bool);
  void draw();
  Coordinates getCursorCoordinates();
  void putc(char, Coordinates);
  void putCursor(Coordinates);
protected:
  void drawHorizontalLine(Coordinates, const unsigned int, char);
  void drawVerticalLine(Coordinates, const unsigned int, char);
  void drawBorders();
  virtual Coordinates boardToGUI(Coordinates) = 0;
};
#endif
