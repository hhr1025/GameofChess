#ifndef _PAWN_H_
#define _PAWN_H_
#include <string>
#include "piece.h"
#include "state.h"
#include "position.h"

class Pawn: public Piece {
	std::string piecename = "Pawn";
    int power = 1;

public:
    Pawn(int c, int r, Colour colour);
    ~Pawn();

    int getPower() override;
    std::string getName() override;
  std::vector<pos> Valid_moves(std::vector<std::vector<Piece*>> &board, Colour currentcolour)override;
  bool isValidMove(int c_dest,int r_dest,std::vector<std::vector<Piece*>> &board) override;


};

#endif

