#ifndef _GRAPHICSDISPLAY_H_
#define _GRAPHICSDISPLAY_H_
#include "window.h"
#include "observer.h"
#include <vector>
#include <iostream>
 
class Piece;
 
class GraphicsDisplay: public Observer <State> {
   
    Xwindow xw; //window to display
    std::vector<std::vector<int>> colours; //colours for each cell
 
    public:
    GraphicsDisplay(); //constructor

    ~GraphicsDisplay(); //destructor
    void notify(Subject<State> &whoNotified) override; //notifies the xw
 
};
 
#endif

