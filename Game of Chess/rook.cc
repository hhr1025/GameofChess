#include "rook.h"
#include <string>
#include <iostream>
#include <cmath>

using namespace std;


Rook::Rook(int c, int r, Colour colour):
Piece{c,r,colour}{}

Rook::~Rook(){}

string Rook::getName(){
	return piecename;
}

int Rook::getPower(){
	return power;
}

vector<pos> Rook::Valid_moves(std::vector<std::vector<Piece*>> &board, Colour currentcolour){
		vector<pos> poses;
	int r = this->getRow();
	int c = this->getCol();
for(int i = c-1; i >= 0; i--){
			if(board[r][i] != nullptr ){
					if(currentcolour != board[r][i]->getColour()){
					pos point = pos{i,r};
					poses.emplace_back(point);
					}break;                             
				}else{pos point = pos{i,r};
					poses.emplace_back(point);
}
		}
		for(int i = c+1; i < 8; i++){
			if(board[r][i] != nullptr ){
					if(currentcolour != board[r][i]->getColour()){
					pos point = pos{i,r};
					poses.emplace_back(point);
					}break;                             
				}else {pos point = pos{i,r};
					poses.emplace_back(point);
}
		}
		for(int i = r-1; i >= 0; i--){
			if(board[i][c] != nullptr ){
					if(currentcolour != board[i][c]->getColour()){
					pos point = pos{c,i};
					poses.emplace_back(point);
					}break;                             
				}else {pos point = pos{c,i};
					poses.emplace_back(point);
}
		}
		for(int i = r+1; i < 8; i++){                  
			if(board[i][c] != nullptr ){
					if(currentcolour != board[i][c]->getColour()){
					pos point = pos{c,i};
					poses.emplace_back(point);
					}break;                             
				}else { pos point = pos{c,i};
		     poses.emplace_back(point);
}
		}
	return poses;
}

bool Rook::isValidMove(int c_dest,int r_dest,std::vector<std::vector<Piece*>> &board){
	int c_orig = this->getCol();
	int r_orig = this->getRow();
	int Distance_row = r_orig - r_dest;
	int Distance_col = c_orig - c_dest;
	return ((Distance_row == 0) || (Distance_col == 0));
}


