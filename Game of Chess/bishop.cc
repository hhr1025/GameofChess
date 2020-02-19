#include "bishop.h"
#include <string>
#include <iostream>
#include <cmath>

using namespace std;


Bishop::Bishop(int c, int r, Colour colour):
Piece{c,r,colour}{}

Bishop::~Bishop(){}


string Bishop::getName(){
return piecename;
}

int Bishop:: getPower(){
	return power;
}


vector<pos> Bishop::Valid_moves(std::vector<std::vector<Piece*>> &board, Colour currentcolour){
	vector<pos> poses;
	int r = this->getRow();
	int c = this->getCol();
		for(int i = r-1, j = c-1; i >= 0 && j >= 0; i--, j--){
				if(board[i][j] != nullptr ){
					if(currentcolour != board[i][j]->getColour()){
					pos point = pos{j,i};
					poses.emplace_back(point);
					}break;                             
				}else{
					pos point = pos{j,i};
					poses.emplace_back(point);
				}
			}
		for(int i = r+1, j = c+1 ; i < 8 && j < 8; i++, j++){
				if(board[i][j] != nullptr ){
					if(currentcolour != board[i][j]->getColour()){
					pos point = pos{j,i};
					poses.emplace_back(point);
					}break;                             
				}else{
					pos point = pos{j,i};
					poses.emplace_back(point);
				}
		}
		for(int i = r-1, j = c+1; i >= 0 && j < 8; i--, j++){
				if(board[i][j] != nullptr ){
					if(currentcolour != board[i][j]->getColour()){
					pos point = pos{j,i};
					poses.emplace_back(point);
					}break;                             
				}else{
					pos point = pos{j,i};
					poses.emplace_back(point);
				}
		}
		for(int i = r+1, j = c-1; i < 8 && j >= 0; i++, j --){
				if(board[i][j] != nullptr ){
					if(currentcolour != board[i][j]->getColour()){
					pos point = pos{j,i};
					poses.emplace_back(point);
					}break;                             
				}else{
					pos point = pos{j,i};
					poses.emplace_back(point);
				}
		}
	return poses;
}

bool Bishop::isValidMove(int c_dest,int r_dest,std::vector<std::vector<Piece*>> &board){
	int c_orig = this->getCol();
	int r_orig = this->getRow();
	int Distance_row = r_orig - r_dest;
	int Distance_col = c_orig - c_dest;
	return (abs(Distance_row) == abs(Distance_col));
}




