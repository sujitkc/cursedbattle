#ifndef LISTPANEL_H
#define LISTPANEL_H

#include "guipanel.h"

using namespace std;
class ListPanel : public GUIPanel {
private:
  vector<string> items;
  unsigned int selectedIndex;
public:
  ListPanel(string, GUI*, Coordinates, vector<string>);
  void draw();
  unsigned int getSelectedIndex();
  void selectNextIndex();
  void selectPreviousIndex();
private:
  virtual Coordinates boardToGUI(Coordinates);
  void writeItemAtIndex(const unsigned int, const bool);

  static Coordinates computeSize(vector<string>);
};
#endif
