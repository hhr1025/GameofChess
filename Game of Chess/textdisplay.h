#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>
#include "observer.h"
#include "state.h"

class Cell;

class TextDisplay: public Observer<State>  {
  std::vector<std::vector<char>> theDisplay;

 public:
  TextDisplay();


  void notify(Subject <State> &whoNotified) override;

  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif

