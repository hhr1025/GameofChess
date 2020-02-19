#ifndef _KNIGHT_H_
#define _KNIGHT_H_
#include <string>
#include "piece.h"
#include "state.h"
#include "position.h"

class Knight: public Piece {
    std::string piecename = "Knight";
    int power = 4;

public:
    Knight(int c, int r, Colour colour);
    ~Knight();

    int getPower() override;
    std::string getName() override;
  std::vector<pos> Valid_moves(std::vector<std::vector<Piece*>> &board, Colour currentcolour)override;
  bool isValidMove(int c_dest,int r_dest,std::vector<std::vector<Piece*>> &board) override;

};

#endif

