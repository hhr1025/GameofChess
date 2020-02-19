#ifndef _QUEEN_H_
#define _QUEEN_H_
#include <string>
#include "piece.h"
#include "state.h"
#include "position.h"
class Queen: public Piece {
	std::string piecename = "Queen";
    int power = 10;

public:
    Queen(int c, int r, Colour colour);
    ~Queen();

    int getPower() override;
    std::string getName() override;
  std::vector<pos> Valid_moves(std::vector<std::vector<Piece*>> &board, Colour currentcolour)override;
  bool isValidMove(int c_dest,int r_dest,std::vector<std::vector<Piece*>> &board) override;

};

#endif 

