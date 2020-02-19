#include "knight.h"
#include <string>
#include <iostream>
#include <cmath>

using namespace std;


Knight::Knight(int c, int r, Colour colour):
Piece{c,r,colour}{}

Knight::~Knight(){}


string Knight::getName(){
	return piecename;
}

int Knight:: getPower(){
	return power;
}

std::vector<pos> Knight::Valid_moves(std::vector<std::vector<Piece*>> &board, Colour currentcolour){
	vector<pos> poses;
	int r = this->getRow();
	int c = this->getCol();
	if(r-2 >= 0 && c-1 >= 0 ){
		if(board[r-2][c-1] && board[r-2][c-1] ->getColour() != this->getColour()){
			pos point = pos{c-1,r-2};
			poses.emplace_back(point);
		}else if(!board[r-2][c-1]){
			pos point = pos{c-1,r-2};
			poses.emplace_back(point);
		}
	}
	if(r-1 >= 0 && c-2 >= 0 ){
		if(board[r-1][c-2] && board[r-1][c-2] ->getColour() != this->getColour()){
			pos point = pos{c-2,r-1};
			poses.emplace_back(point);
		}
		else if(!board[r-1][c-2]){
			pos point = pos{c-2,r-1};
			poses.emplace_back(point);
		}
	}if(r+1 <8 && c-2 >= 0 ){
		if(board[r+1][c-2] && board[r+1][c-2] ->getColour() != this->getColour()){
			pos point = pos{c-2,r+1};
			poses.emplace_back(point);
		}
		else if(!board[r+1][c-2]){
			pos point = pos{c-2,r+1};
			poses.emplace_back(point);
		}
	}if(r+2 < 8 && c-1 >= 0 ){
		if(board[r+2][c-1] && board[r+2][c-1] ->getColour() != this->getColour()){
			pos point = pos{c-1,r+2};
			poses.emplace_back(point);
		}
		else if(!board[r+2][c-1]){
			pos point = pos{c-1,r+2};
			poses.emplace_back(point);
		}
	}if(r+2 < 8 && c+1 < 8 ){
		if(board[r+2][c+1] && board[r+2][c+1] ->getColour() != this->getColour()){
			pos point = pos{c+1,r+2};
			poses.emplace_back(point);
		}
		else if(!board[r+2][c+1]){
			pos point = pos{c+1,r+2};
			poses.emplace_back(point);
		}
	}if(r+1 < 8 && c+2 < 8 ){
		if(board[r+1][c+2] && board[r+1][c+2] ->getColour() != this->getColour()){
			pos point = pos{c+2,r+1};
			poses.emplace_back(point);
		}
		else if(!board[r+1][c+2]){
			pos point = pos{c+2,r+1};
			poses.emplace_back(point);
		}
	}if(r-2 >= 0 && c+1 < 8 ){
		if(board[r-2][c+1] && board[r-2][c+1] ->getColour() != this->getColour()){
			pos point = pos{c+1,r-2};
			poses.emplace_back(point);
		}
		else if(!board[r-2][c+1]){
			pos point = pos{c+1,r-2};
			poses.emplace_back(point);
		}
	}if(r-1 >= 0 && c+2 < 8 ){
		if(board[r-1][c+2] && board[r-1][c+2] ->getColour() != this->getColour()){
			pos point = pos{c+2,r-1};
			poses.emplace_back(point);
		}
		else if(!board[r-1][c+2]){
			pos point = pos{c+2,r-1};
			poses.emplace_back(point);
		}
	}return poses;
}

bool Knight::isValidMove(int c_dest,int r_dest,std::vector<std::vector<Piece*>> &board){
	int c_orig = this->getCol();
	int r_orig = this->getRow();
	int Distance_row = r_orig - r_dest;
	int Distance_col = c_orig - c_dest;
	return (abs(Distance_row)*abs(Distance_col) == 2);
}

