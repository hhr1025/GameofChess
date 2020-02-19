#ifndef _BISHOP_H_
#define _BISHOP_H_
#include <string>
#include "piece.h"
#include "state.h"
#include "position.h"
class Bishop: public Piece {
	std::string piecename = "Bishop";
    int power = 3;


public:
    Bishop(int c, int r, Colour colour);
    ~Bishop();
    int getPower() override;
    std::string getName() override;
  std::vector<pos> Valid_moves(std::vector<std::vector<Piece*>> &board, Colour currentcolour)override;
  bool isValidMove(int c_dest,int r_dest,std::vector<std::vector<Piece*>> &board) override;

};

#endif

