#ifndef GUIBOARD_H
#define GUIBOARD_H

#include "guipanel.h"
#include "vessel.h"
#include "modelexceptions.h"

using namespace std;
class GUIBoard : public GUIPanel {
private:
  map<Vessel*, Position> vesselPositions;
public:
  GUIBoard(string n, GUI*, Coordinates c);
  void draw();
  void eraseVessel(Vessel *);
  void drawVessel(Vessel *);
  virtual void moveCursor(Position::Orientation);
protected:
  virtual Coordinates boardToGUI(Coordinates);
  void drawGrid();
};
#endif
