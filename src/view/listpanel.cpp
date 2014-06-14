#include <curses.h>
#include <string>

#include "listpanel.h"

using namespace std;

ListPanel::ListPanel(string n, GUI* g, Coordinates o, vector<string> i) : GUIPanel(n, g, o, ListPanel::computeSize(i)), items(i), selectedIndex (0) {}

Coordinates ListPanel::boardToGUI(Coordinates c) {
  return Coordinates(
    c.getx() + origin.getx() + 1,
    c.gety() + origin.gety() + 1
  );
}

void ListPanel::draw() {
  GUIPanel::draw();
  for(unsigned int i = 0; i < items.size(); i++) {
    if(i == selectedIndex) {
      writeItemAtIndex(i, true);
    }
    else {
      writeItemAtIndex(i, false);
    }
  }
}

unsigned int ListPanel::getSelectedIndex() { return selectedIndex; }

void ListPanel::writeItemAtIndex(const unsigned int index, const bool highlight) {
  if(highlight == true) {
    attron(A_UNDERLINE);
  }
  else {
    attroff(A_UNDERLINE);
  }
  string item = items[index];
  for(unsigned int i = 0; i < item.size(); i++) {
    putc(item[i], Coordinates(i, index));
  }
  attroff(A_UNDERLINE);
}

void ListPanel::selectNextIndex() {
  writeItemAtIndex(selectedIndex, false);
  if(selectedIndex == items.size() - 1) {
    selectedIndex = 0;
  }
  else {
    selectedIndex++;
  }
  writeItemAtIndex(selectedIndex, true);
}

void ListPanel::selectPreviousIndex() {
  writeItemAtIndex(selectedIndex, false);
  if(selectedIndex == 0) {
    selectedIndex = items.size() - 1;
  }
  else {
    selectedIndex--;
  }
  writeItemAtIndex(selectedIndex, true);
}

// Compute the size of the panel depending on the items.
// width based on the length of the longest string.
// height based on the number of strings.
Coordinates ListPanel::computeSize(vector<string> it) {
  unsigned int width = 3;
  for(unsigned int i = 0; i < it.size(); i++) {
    if(it[i].size() > width - 3) {
      width = it[i].size() + 3;
    }
  }
  unsigned int height = it.size() + 2;
  return Coordinates(width, height);
}
