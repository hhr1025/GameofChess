#include <iostream>
#include <vector>
#include "observer.h"
#include "state.h"
#include "subject.h"
#include "window.h"
#include "graphicsdisplay.h"

using namespace std;

// Constructer constructs a window with default board
GraphicsDisplay::GraphicsDisplay() {
    xw.fillRectangle(0,0,800,800,Xwindow::White);
int size = 8;
    int width = 800/(size + 2);

    for(int i = 1; i <= size; ++i){
        for(int j = 1; j <= size; ++j){
           if ((i + j) % 2 == 0) xw.fillRectangle(i*width,j*width,width,width,Xwindow::Lbrown);
           else xw.fillRectangle(i*width,j*width,width,width,Xwindow::Dyellow);
        }
    }
    xw.fillRectangle(width-4,width-4,4,640+4,Xwindow::Black);
    xw.fillRectangle(width-4,width-4,640+4,4,Xwindow::Black);
    xw.fillRectangle(width-4,width+size*width,640+8,4,Xwindow::Black);
    xw.fillRectangle(width+size*width,width-4,4,640+8,Xwindow::Black);
    xw.drawString(40, 120, "8", Xwindow::Black);
    xw.drawString(40, 200, "7", Xwindow::Black);
    xw.drawString(40, 280, "6", Xwindow::Black);
    xw.drawString(40, 360, "5", Xwindow::Black);
    xw.drawString(40, 440, "4", Xwindow::Black);
    xw.drawString(40, 520, "3", Xwindow::Black);
    xw.drawString(40, 600, "2", Xwindow::Black);
    xw.drawString(40, 680, "1", Xwindow::Black);
    xw.drawString(120, 40, "a", Xwindow::Black);
    xw.drawString(200, 40, "b", Xwindow::Black);
    xw.drawString(280, 40, "c", Xwindow::Black);
    xw.drawString(360, 40, "d", Xwindow::Black);
    xw.drawString(440, 40, "e", Xwindow::Black);
    xw.drawString(520, 40, "f", Xwindow::Black);
    xw.drawString(600, 40, "g", Xwindow::Black);
    xw.drawString(680, 40, "h", Xwindow::Black);
    colours = vector<vector<int>> (8, vector<int>(8, Xwindow::Black)); 
    for(int i = 0; i < 8; ++i){
        for(int j = 0; j < 8; ++j){
           if ((i + j) % 2 == 0)  {
            colours[i][j] = Xwindow::White;
        }
      }
    }

} 

//Destructor
GraphicsDisplay::~GraphicsDisplay() {}



void GraphicsDisplay::notify(Subject <State> &whoNotified) {
    StateType pType = whoNotified.getState().type;
    Colour pColour = whoNotified.getState().colour;
    int r = whoNotified.getState().row; //get the (r,c) of the current cell
    int c = whoNotified.getState().column; //to switch on the textdisplay
    int curr_col = whoNotified.getState().column_dest;
    int curr_row = whoNotified.getState().row_dest;
    string pName = whoNotified.getState().name;
    int width = 800/10;
    if(pType == StateType:: NewPiece){
        if(pColour == Colour:: Black){
            colours[curr_row][curr_col] = Xwindow::Black;
            xw.fillRectangle(curr_col*width+width, curr_row*width+width, width, width, colours[curr_row][curr_col]); 
            if(pName == "King") {
                xw.drawBigString(curr_col*width+100, curr_row*width+140, "k", Xwindow::White);
            } 
            if(pName == "Queen") {
                xw.drawBigString(curr_col*width+100, curr_row*width+140, "q", Xwindow::White);
            }
            if(pName == "Rook") {
                xw.drawBigString(curr_col*width+100, curr_row*width+140, "r", Xwindow::White);
            }
            if(pName == "Knight") {
                xw.drawBigString(curr_col*width+100, curr_row*width+140, "n", Xwindow::White);
            }
            if(pName == "Bishop") {
               xw.drawBigString(curr_col*width+100, curr_row*width+140, "b", Xwindow::White);
            }
            if(pName == "Pawn") {
               xw.drawBigString(curr_col*width+100, curr_row*width+140, "p", Xwindow::White);
            }
        }
        else{
            colours[curr_row][curr_col] = Xwindow::White;
            xw.fillRectangle(curr_col*width+width, curr_row*width+width, width, width, colours[curr_row][curr_col]); 
            if(pName == "King") {
       xw.drawBigString(curr_col*width+100, curr_row*width+140, "K", Xwindow::Black);
            }
            if(pName == "Queen") {
       xw.drawBigString(curr_col*width+100, curr_row*width+140, "Q", Xwindow::Black);
            }
            if(pName == "Rook") {
       xw.drawBigString(curr_col*width+100, curr_row*width+140, "R", Xwindow::Black);
            }
            if(pName == "Knight"){

       xw.drawBigString(curr_col*width+100, curr_row*width+140, "N", Xwindow::Black);
         }
            if(pName == "Bishop") {
       xw.drawBigString(curr_col*width+100, curr_row*width+140, "B", Xwindow::Black);
            }
            if(pName == "Pawn") {
       xw.drawBigString(curr_col*width+100, curr_row*width+140, "P", Xwindow::Black);
            }
        }
    }
    else if (pType == StateType:: MovePiece){
        
        if(pColour == Colour:: Black){
      colours[curr_row][curr_col] = Xwindow::Black;
      xw.fillRectangle(curr_col*width+width, curr_row*width+width, width, width, colours[curr_row][curr_col]); 
            if(pName == "King") {
       xw.drawBigString(curr_col*width+100, curr_row*width+140, "k", Xwindow::White);
        }
            if(pName == "Queen") {
       xw.drawBigString(curr_col*width+100, curr_row*width+140, "q", Xwindow::White);
            }
            if(pName == "Rook") {
       xw.drawBigString(curr_col*width+100, curr_row*width+140, "r", Xwindow::White);
            }
            if(pName == "Knight") {
       xw.drawBigString(curr_col*width+100, curr_row*width+140, "n", Xwindow::White);
            }
            if(pName == "Bishop") {
       xw.drawBigString(curr_col*width+100, curr_row*width+140, "b", Xwindow::White);
            }
            if(pName == "Pawn") {
       xw.drawBigString(curr_col*width+100, curr_row*width+140, "p", Xwindow::White);
            }
        }
        else{
      colours[curr_row][curr_col] = Xwindow::White;
      xw.fillRectangle(curr_col*width+width, curr_row*width+width, width, width, colours[curr_row][curr_col]); 
            if(pName == "King") {
       xw.drawBigString(curr_col*width+100, curr_row*width+140, "K", Xwindow::Black);
            }
            if(pName == "Queen") {
       xw.drawBigString(curr_col*width+100, curr_row*width+140, "Q", Xwindow::Black);
            }
            if(pName == "Rook") {
       xw.drawBigString(curr_col*width+100, curr_row*width+140, "R", Xwindow::Black);
            }
            if(pName == "Knight"){

       xw.drawBigString(curr_col*width+100, curr_row*width+140, "N", Xwindow::Black);
         }
            if(pName == "Bishop") {
       xw.drawBigString(curr_col*width+100, curr_row*width+140, "B", Xwindow::Black);
            }
            if(pName == "Pawn") {
       xw.drawBigString(curr_col*width+100, curr_row*width+140, "P", Xwindow::Black);
            }
        }
             xw.drawBigString(c*width+100, r*width+140, " ", Xwindow::White);
        if((r % 2 == 1 && c % 2 == 0) || (r % 2 == 0 && c % 2 == 1)){
            colours[r][c] = Xwindow::Dyellow;
            xw.fillRectangle(c*width+width, r*width+width, width, width, colours[r][c]); 
        }
        else{
            colours[r][c] = Xwindow::Lbrown;
            xw.fillRectangle(c*width+width, r*width+width, width, width, colours[r][c]); 
        }
    }
    else //Remove piece
    {
      if((curr_row % 2 == 1 && curr_col % 2 == 0) || (curr_row % 2 == 0 && curr_col % 2 == 1)){
            colours[curr_row][curr_col] = Xwindow::Dyellow;
            xw.fillRectangle(curr_col*width+width, curr_row*width+width, width, width, colours[curr_row][curr_col]); 
        }
        else{
            colours[curr_row][curr_col] = Xwindow::Lbrown;
            xw.fillRectangle(curr_col*width+width, curr_row*width+width, width, width, colours[curr_row][curr_col]); 
        }
    }
}

