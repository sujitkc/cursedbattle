#include <curses.h>
#include <string>

#include "guipanel.h"

using namespace std;
GUIPanel::GUIPanel(string n, GUI* g, Coordinates o, Coordinates sz) : name (n), gui(g), origin (o), size (sz) {}

void GUIPanel::drawHorizontalLine(Coordinates coord, const unsigned int len, char c) {
  int i;
  for(unsigned int i = 0; i < len; i++) {
    gui->putc(c, coord + Coordinates(i, 0));
  }
}

void GUIPanel::drawVerticalLine(Coordinates coord, const unsigned int len, char c) {
  for(unsigned int i = 0; i < len; i++) {
    gui->putc(c, coord + Coordinates(0, i));
  }
}

void GUIPanel::drawBorders() {
  int width = size.getx();
  int height = size.gety();
  drawHorizontalLine(origin + Coordinates(-1, 0), width, '=');
  drawHorizontalLine(origin + Coordinates(-1, size.gety()), width, '=');
  drawVerticalLine(origin + Coordinates(-1, 0), height + 1, '+');
  drawVerticalLine(origin + Coordinates(size.getx() - 1, 0), height + 1, '+');
}

Coordinates GUIPanel::getCursorCoordinates() {
  return cursorCoordinates;
}

void GUIPanel::putc(char c, Coordinates coord) {
  Coordinates guiCoord = boardToGUI(coord);
  gui->putc(c, guiCoord); 
}

void GUIPanel::putCursor(Coordinates c) {
  gui->putCursor(boardToGUI(c));
  cursorCoordinates = c;
}

void GUIPanel::showCursor(bool c) {
  if(!(boardToGUI(cursorCoordinates) == gui->getCursorCoordinates())) {
    gui->putCursor(boardToGUI(cursorCoordinates));
  }
  gui->showCursor(c);
}

void GUIPanel::draw() {
  gui->printMessage(name, origin + Coordinates(0, - 1));
  drawBorders();
}
