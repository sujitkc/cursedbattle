#include <curses.h>
#include <string>

#include "listpanel.h"

using namespace std;

ListPanel::ListPanel(string n, GUI* g, Coordinates o, vector<string> i) : GUIPanel(n, g, o, Coordinates(40, 20), ListPanel::computeSize(i)), items(i) {}

Coordinates ListPanel::boardToGUI(Coordinates c) {
  return Coordinates(
    c.getx() + origin.getx() + 1,
    c.gety() + origin.gety() + 1
  );
}

void ListPanel::draw() {
  GUIPanel::draw();
}

Coordinates ListPanel::computeSize(vector<string> it) {
  unsigned int maxWidth = 2;
  for(unsigned int i = 0; i < it.size(); i++) {
    if(it[i].size() > maxWidth - 2) {
      maxWidth = it[i].size() + 2;
    }
  }
  unsigned int maxHeight = it.size + 2;
  return Coordinates(maxWidth, maxHeight);
}
