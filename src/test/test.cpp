#include <iostream>

#include "../utils/position.cpp"
using namespace std;

int main() {
  Position p1(Coordinates(2, 3), Position::TOEAST);
  p1 = Position(Coordinates(2, 3), Position::TOSOUTH);
  cout << "before rotating " << p1.toString() << endl;
  Position p2 = p1.rotateCW();
  cout << "after rotating " << p1.rotateCW().toString() << endl;
  cout << "after rotating " << p2.toString() << endl;
  return 0;
}
