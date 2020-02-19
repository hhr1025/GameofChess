#ifndef _KING_H_
#define _KING_H_
#include <string>
#include "piece.h"
#include "subject.h"
#include "position.h"
class King: public Piece {
	std::string piecename = "King";
    int power = 100;

public:
  King(int c, int r, Colour colour);
  ~King();

  std::string getName() override;
  int getPower() override;
  std::vector<pos> Valid_moves(std::vector<std::vector<Piece*>> &board, Colour currentcolour)override;
  bool isValidMove(int c_dest,int r_dest,std::vector<std::vector<Piece*>> &board) override;


};

#endif

