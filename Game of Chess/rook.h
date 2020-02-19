#ifndef _ROOK_H_
#define _ROOK_H_
#include <string>
#include "piece.h"
#include "state.h"
#include "position.h"

class Rook: public Piece {
	std::string piecename = "Rook";
    int power = 5;

public:
    Rook(int c, int r, Colour colour);
    ~Rook();

    int getPower() override;
    std::string getName() override;
  std::vector<pos> Valid_moves(std::vector<std::vector<Piece*>> &board, Colour currentcolour)override;
  bool isValidMove(int c_dest,int r_dest,std::vector<std::vector<Piece*>> &board) override;

};

#endif

