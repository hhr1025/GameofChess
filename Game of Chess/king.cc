
#include "king.h"
#include <string>
#include <iostream>
#include <cmath>

using namespace std;


King::King(int c, int r, Colour colour):
Piece{c,r,colour}{}

King::~King(){}

string King::getName(){
	return piecename;
}

int King:: getPower(){
	return power;
}

std::vector<pos> King::Valid_moves(std::vector<std::vector<Piece*>> &board, Colour currentcolour){
	vector<pos> poses;
	int r = this->getRow();
	int c = this->getCol();
	Colour colour = this->getColour();
	if(r > 0) {
		if (!board[r-1][c]){
			pos point = pos{c,r-1};
			poses.emplace_back(point);
		}
		else{
			if (board[r-1][c]->getColour() != currentcolour){
				pos point = pos{c,r-1};
				poses.emplace_back(point);
			}
		}
	}
	if (r < 7) {
		if (!board[r+1][c]){
			pos point = pos{c,r+1};
			poses.emplace_back(point);
		}
		else{
			if (board[r+1][c]->getColour() != currentcolour){
				pos point = pos{c,r+1};
				poses.emplace_back(point);
			}
		}
	}
	if (c > 0) {
		if (!board[r][c-1]){
			pos point = pos{c-1,r};
			poses.emplace_back(point);
		}
		else{
			if (board[r][c-1]->getColour() != currentcolour){
				pos point = pos{c-1,r};
				poses.emplace_back(point);
			}
		}
	}
	if (c < 7) {
		if (!board[r][c+1]){
			pos point = pos{c+1,r};
			poses.emplace_back(point);
		}
		else{
			if (board[r][c+1]->getColour() != currentcolour){
				pos point = pos{c+1,r};
				poses.emplace_back(point);
			}
		}
	}
	if ((r > 0) && (c > 0)){
		if (!board[r-1][c-1]){
			pos point = pos{c-1,r-1};
			poses.emplace_back(point);
		}
		else{
			if (board[r-1][c-1]->getColour() != currentcolour){
				pos point = pos{c-1,r-1};
				poses.emplace_back(point);
			}
		}
	}
	if ((r < 7) && (c > 0)){
		if (!board[r+1][c-1]){
			pos point = pos{c-1,r+1};
			poses.emplace_back(point);
		}
		else{
			if (board[r+1][c-1]->getColour() != currentcolour){
				pos point = pos{c-1,r+1};
				poses.emplace_back(point);
			}
		}
	}
	if ((r > 0) && (c < 7)) {
		if (!board[r-1][c+1]){
			pos point = pos{c+1,r-1};
			poses.emplace_back(point);
		}
		else{
			if (board[r-1][c+1]->getColour() != currentcolour){
				pos point = pos{c+1,r-1};
				poses.emplace_back(point);
			}
		}
	}
	if ((r < 7) && (c < 7)) {
		if (!board[r+1][c+1]){
			pos point = pos{c+1,r+1};
			poses.emplace_back(point);
		}
		else{
			if (board[r+1][c+1]->getColour() != currentcolour){
				pos point = pos{c+1,r+1};
				poses.emplace_back(point);
			}
		}
	}
	if (this->nevermoved()) { // && (! this->underAttack(c,r,board))
		if ((!board[r][1]) && (!board[r][2]) && (!board[r][3]) && (board[r][0])){
			if ((board[r][0]->getColour() == colour) && (board[r][0]->getName() == "Rook") && (board[r][0]->nevermoved())){
				pos point = pos{2,r};
				poses.emplace_back(point);
			}
		}
		if ((!board[r][5])&&(!board[r][6])&&(board[r][7])){
			if ((board[r][7]->getColour() == colour) && (board[r][7]->getName() == "Rook") && (board[r][7]->nevermoved())) {
				pos point = pos{6,r};
				poses.emplace_back(point);
			}
		}
	}	
	return poses;
}

bool King::isValidMove(int c_dest,int r_dest,std::vector<std::vector<Piece*>> &board){
	int c_orig = this->getCol();
	int r_orig = this->getRow();
	int Distance_row = r_orig - r_dest;
	int Distance_col = c_orig - c_dest;
	//cout << r_orig << r_dest << c_orig << c_dest << endl;
	if ((abs(Distance_row) <= 1 && abs(Distance_col) <= 1)){
		return true;
	} 
	//king never moved, king not in check, parallel move
	if (this->nevermoved() && (! this->underAttack(c_orig ,r_orig ,board)) && (r_orig  == r_dest)){ // 
		if (c_dest == 2) {
			// Check 01234:Piece,nullptr,nullptr,nullptr,king
			if ((!board[r_orig][1])&&(!board[r_orig][2])&&(!board[r_orig][3])&&(board[r_orig][0])&&
			//check if there is an unmoved rook at the end
				(board[r_orig][0]->getColour() == this->getColour()) && (board[r_orig][0]->getName() == "Rook") && (board[r_orig][0]->nevermoved()))
				return true;
		}
		if (c_dest == 6) {
			// Check 01234:Piece,nullptr,nullptr,nullptr,king
			if ((!board[r_orig][5])&&(!board[r_orig][6])&&(board[r_orig][7])&&
			//check if there is an unmoved rook at the end
				(board[r_orig][7]->getColour() == this->getColour()) && (board[r_orig][7]->getName() == "Rook") && (board[r_orig][0]->nevermoved()))
				return true;
		}
	}
	return false;
}



