#include "modelexceptions.h"

ActionNotAllowedException::ActionNotAllowedException(string s, string m) : Exception(s, m) {}
InvalidCoordinatesException::InvalidCoordinatesException(string s, string m) : Exception(s, m) {}

