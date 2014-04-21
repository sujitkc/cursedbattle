#include <curses.h>
#include <string>

#include "board.h"
#include "guiboard.h"

using namespace std;
Coordinates GUIBoard::size = (Coordinates(40, 20)); // size in terms of GUI real-estate
GUIBoard::GUIBoard(string n, GUI* g, Coordinates c) : name (n), gui(g), origin (c) {}

void GUIBoard::drawHorizontalLine(Coordinates coord, const unsigned int len, char c) {
  int i;
  for(unsigned int i = 0; i < len; i++) {
    gui->putc(c, coord + Coordinates(i, 0));
  }
}

void GUIBoard::drawVerticalLine(Coordinates coord, const unsigned int len, char c) {
  for(unsigned int i = 0; i < len; i++) {
    gui->putc(c, coord + Coordinates(0, i));
  }
}

void GUIBoard::drawGrid() {
  int numCols = Board::getSize().getx() - 1;
  int numRows = Board::getSize().gety() - 1;
  int width = size.getx();
  int height = size.gety();
  for(unsigned int i = 0; i < numRows; i++) {
    drawHorizontalLine(origin + Coordinates(0, 2 * (i + 1)), width - 1, '-');
  }
  for(unsigned int i = 0; i < numCols; i++) {
    drawVerticalLine(origin + Coordinates(4 * (i + 1) - 1, 1), height - 1, '|');
  }
}

void GUIBoard::drawBorders() {
  int width = size.getx();
  int height = size.gety();
  drawHorizontalLine(origin + Coordinates(-1, 0), width, '=');
  drawHorizontalLine(origin + Coordinates(-1, size.gety()), width, '=');
  drawVerticalLine(origin + Coordinates(-1, 0), height + 1, '+');
  drawVerticalLine(origin + Coordinates(size.getx() - 1, 0), height + 1, '+');
}

Coordinates GUIBoard::boardToGUI(Coordinates c) {
  return Coordinates(
    4 * (c.getx()) + origin.getx() + 1,
    2 * (c.gety()) + origin.gety() + 1
  );
}

Coordinates GUIBoard::getCursorCoordinates() {
  return cursorCoordinates;
}

void GUIBoard::putc(char c, Coordinates coord) {
  Coordinates guiCoord = boardToGUI(coord);
  gui->putc(c, guiCoord); 
}

void GUIBoard::drawVessel(Vessel* v) {
  if(vesselPositions.find(v) == vesselPositions.end()) {
    vesselPositions[v] = v->getPosition();
  }
  if(!(v->getPosition() == vesselPositions[v])) {
    eraseVessel(v);
    vesselPositions[v] = v->getPosition();
  }
  Position p = v->getPosition();
  Coordinates coord;
  unsigned int len = v->getLength();
  for(unsigned int i = 0; i < len; i++) {
    // Where to put the character
    if(p.getOrientation() == Position::TONORTH) {
      coord = p.getCoordinates() + Coordinates(0, -i);
    }
    else if(p.getOrientation() == Position::TOEAST) {
      coord = p.getCoordinates() + Coordinates(i, 0);
    }
    else if(p.getOrientation() == Position::TOSOUTH) {
      coord = p.getCoordinates() + Coordinates(0, i);
    }
    else if(p.getOrientation() == Position::TOWEST) {
      coord = p.getCoordinates() + Coordinates(-i, 0);
    }
   // What character to put?
    char c;
    if(v->getState() == Vessel::SUNK) {
      c = 'X';
    }
    else if(v->getCoordinatesState(coord) == Vessel::HIT) {
      c = 'H';
    }
    else {
      c = v->getName().c_str()[0];
    }
    putc(c, coord);
  }
  putCursor(p.getCoordinates());
}

void GUIBoard::eraseVessel(Vessel* v) {
  Position p = vesselPositions[v];
  Coordinates coord;
  unsigned int len = v->getLength();
  for(unsigned int i = 0; i < len; i++) {
    // What character to put?
    char c = ' ';

    // Where to put the character
    if(p.getOrientation() == Position::TONORTH) {
      coord = p.getCoordinates() + Coordinates(0, -i);
    }
    else if(p.getOrientation() == Position::TOEAST) {
      coord = p.getCoordinates() + Coordinates(i, 0);
    }
    else if(p.getOrientation() == Position::TOSOUTH) {
      coord = p.getCoordinates() + Coordinates(0, i);
    }
    else if(p.getOrientation() == Position::TOWEST) {
      coord = p.getCoordinates() + Coordinates(-i, 0);
    }
    putc(c, coord);
  }
}

void GUIBoard::putCursor(Coordinates c) {
  gui->putCursor(boardToGUI(c));
  cursorCoordinates = c;
}

void GUIBoard::showCursor(bool c) {
  if(!(boardToGUI(cursorCoordinates) == gui->getCursorCoordinates())) {
    gui->putCursor(boardToGUI(cursorCoordinates));
  }
  gui->showCursor(c);
}

void GUIBoard::moveCursor(Position::Orientation dir) {
  switch(dir) {
  case Position::TONORTH:
    if(cursorCoordinates.gety() == 0) {
      throw ActionNotAllowedException("GUIBoard::moveCursor", "Already at the top of the board; can't move any further north.");
    }
    cursorCoordinates = cursorCoordinates + Coordinates(0, -1);
    break;
  case Position::TOEAST:
     if(cursorCoordinates.getx() == Board::getSize().getx() - 1) {
      throw ActionNotAllowedException("GUIBoard::moveCursor", "Already at the right end of the board; can't move any further east.");
    }
    cursorCoordinates = cursorCoordinates + Coordinates(1, 0);
    break;
  case Position::TOSOUTH:
      if(cursorCoordinates.gety() == Board::getSize().gety() - 1) {
      throw ActionNotAllowedException("GUIBoard::moveCursor", "Already at the bottom of the board; can't move any further south.");
    }
    cursorCoordinates = cursorCoordinates + Coordinates(0, 1);
   break;
  case Position::TOWEST:
       if(cursorCoordinates.getx() == 0) {
      throw ActionNotAllowedException("GUIBoard::moveCursor", "Already at the left end of the board; can't move any further west.");
    }
    cursorCoordinates = cursorCoordinates + Coordinates(-1, 0);
   break;
  }
  putCursor(cursorCoordinates);
}

void GUIBoard::draw() {
  gui->printMessage(name, origin + Coordinates(0, - 1));
  drawBorders();
  drawGrid();
  refresh();
}
