#include <curses.h>

#include "keyboard.h"

Keyboard::Keyboard(WINDOW* w) : window(w) {}

int Keyboard::getKey() {
  noecho();
  cbreak();
  keypad(window, TRUE);
  return wgetch(window);
}
