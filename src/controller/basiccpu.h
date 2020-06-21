#ifndef BASICCPU_H
#define BASICCPU_H

#include <string>

#include "cpu.h"

class BasicCPU : public CPU {
public: // methods
  BasicCPU(Board*, GUIBoard*, Board*, GUIBoard*);
};
#endif
