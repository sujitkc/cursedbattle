#include <stdlib.h>
#include <time.h>
#include <curses.h>
#include <iostream>
#include <algorithm>

#include "basiccpu.h"

using namespace std;

BasicCPU::BasicCPU(Board* b, GUIBoard* gb, Board* e, GUIBoard* ge) : CPU("Basic CPU", b, gb, e, ge) {}

