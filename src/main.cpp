#include <iostream>

#include "game.h"

using namespace std;
int main() {
  Game g;
  try {
    g.run();
  }
  catch(Exception e) {
    cerr << e.getSource() << " " << e.getMessage() << endl;
  }
  return 0;
}
