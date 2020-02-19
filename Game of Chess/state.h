#ifndef STATE_H
#define STATE_H
#include <string>

enum class StateType { NewPiece, RemovePiece, MovePiece };
enum class Colour { NoColour, Black, White };


struct State {
  int column,row;
  int column_dest,row_dest;
  std::string name;
  StateType type;  // See above
  Colour colour;   // What colour was the new piece?  (NOT what is my colour)
};

#endif

