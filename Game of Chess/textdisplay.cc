#include <iostream>
#include <vector>
#include <string>
#include "observer.h"
#include "state.h"
#include "subject.h"
#include "textdisplay.h"

using namespace std;



TextDisplay::TextDisplay(): 
	theDisplay{10, vector<char>(10, ' ')} {
    for (int r = 0; r < 8; ++r) { 
      for (int c = 0; c < 8; ++c) { 
          theDisplay[r][c] = '-';
      }
    }
    theDisplay[0][9] = '8';
    theDisplay[1][9] = '7';
    theDisplay[2][9] = '6';
    theDisplay[3][9] = '5';
    theDisplay[4][9] = '4';
    theDisplay[5][9] = '3';
    theDisplay[6][9] = '2';
    theDisplay[7][9] = '1';
    theDisplay[9][0] = 'a';
    theDisplay[9][1] = 'b';
    theDisplay[9][2] = 'c';
    theDisplay[9][3] = 'd';
    theDisplay[9][4] = 'e';
    theDisplay[9][5] = 'f';
    theDisplay[9][6] = 'g';
    theDisplay[9][7] = 'h';
}



void TextDisplay::notify(Subject <State> &whoNotified) {
    StateType pType = whoNotified.getState().type;
    Colour pColour = whoNotified.getState().colour;
    int r = whoNotified.getState().row; //get the (r,c) of the current cell
    int c = whoNotified.getState().column; //to switch on the textdisplay
    int curr_col = whoNotified.getState().column_dest;
    int curr_row = whoNotified.getState().row_dest;
    string pName = whoNotified.getState().name;
    if(pType == StateType:: NewPiece){
        if(pColour == Colour:: Black){
            if(pName == "King") theDisplay[curr_row][curr_col] = 'k';
            if(pName == "Queen") theDisplay[curr_row][curr_col] = 'q';
            if(pName == "Rook") theDisplay[curr_row][curr_col] = 'r';
            if(pName == "Knight") theDisplay[curr_row][curr_col] = 'n';
            if(pName == "Bishop") theDisplay[curr_row][curr_col] = 'b';
            if(pName == "Pawn") theDisplay[curr_row][curr_col] = 'p';
        }
        else{
            if(pName == "King") theDisplay[curr_row][curr_col] = 'K';
            if(pName == "Queen") theDisplay[curr_row][curr_col] = 'Q';
            if(pName == "Rook") theDisplay[curr_row][curr_col] = 'R';
            if(pName == "Knight") theDisplay[curr_row][curr_col] = 'N';
            if(pName == "Bishop") theDisplay[curr_row][curr_col] = 'B';
            if(pName == "Pawn") theDisplay[curr_row][curr_col] = 'P';
        }
    }
    else if (pType == StateType:: MovePiece){
      theDisplay[curr_row][curr_col] = theDisplay[r][c];
      theDisplay[r][c] = '-';
    }
    else
    {
        theDisplay[curr_row][curr_col] = '-';
    }
}




ostream &operator<<(ostream &out, const TextDisplay &td) {
    for (int r = 0; r < 10; ++r) { 
    	for (int c = 0; c < 10; ++c) { 
    	    out << td.theDisplay[r][c];
	    }
	    out << std::endl; 
    }
    return out;
}

