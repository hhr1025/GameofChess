#ifndef _PIECE_H_
#define _PIECE_H_
#include <string>
#include <vector>
#include "state.h"
#include "position.h"

class Piece { 

    int c, r; //if the piece needs to know about its location
    Colour colour = Colour::NoColour;
    bool nevermoved_boo = true;
    bool alive = true;
    bool enpassant = false;

    

public:
    Piece(int c, int r, Colour colour):c{c},r{r},colour{colour}{};
    virtual ~Piece();
    virtual int getPower() = 0;
    virtual std:: string getName()=0;
    virtual std::vector<pos> Valid_moves(std::vector<std::vector<Piece*>> &board, Colour currentcolour)=0;
    virtual bool isValidMove(int c_dest,int r_dest,std::vector<std::vector<Piece*>> &board)=0;

    int getRow();
    int getCol();
    void setRow(int r);
    void setCol(int c);
    Colour getColour();
    bool isalive();
    void setDead(); 

    bool nevermoved();
    void setNeverMoved();    
    bool getEP();
    void setEPtrue();
    void setEPfalse();
    
    
    

    int underAttack(int c_dest, int r_dest, std::vector<std::vector<Piece*>> &theBoard);
   
  

};

#endif

