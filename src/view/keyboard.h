#ifndef KEYBOARD_D
#define KEYBOARD_D

class Keyboard {
	WINDOW* window; 
public:
	Keyboard(WINDOW* w);
	int getKey();	
};
#endif
