#ifndef MODELEXCEPTIONS_h
#define MODELEXCEPTIONS_h

#include "exception.h"

class ActionNotAllowedException : public Exception {
public:
  ActionNotAllowedException(string, string);
};

class InvalidCoordinatesException : public Exception {
public:
  InvalidCoordinatesException(string, string);
};
#endif
