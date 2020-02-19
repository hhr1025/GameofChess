#include "pawn.h"
#include <string>
#include <iostream>
#include <cmath>

using namespace std;


Pawn::Pawn(int c, int r, Colour colour):
Piece{c,r,colour}{}

Pawn::~Pawn(){}


string Pawn::getName(){
	return piecename;
}

int Pawn::getPower(){
	return power;
}

bool Pawn::isValidMove(int c_dest,int r_dest,std::vector<std::vector<Piece*>> &board){
	int c_orig = this->getCol();
	int r_orig = this->getRow();
	Colour currentcolour = this->getColour();
	int Distance_row = r_orig - r_dest;
	int Distance_col = c_orig - c_dest;
	//cout << r_orig << r_dest << c_orig << c_dest << endl;
	if(currentcolour == Colour::Black){
		if ((Distance_row == -1) && (Distance_col == 0) && (board[r_dest][c_dest] == nullptr)) return true;
		if (this->nevermoved() && (Distance_row == -2) && (Distance_col == 0) && 
			(board[r_dest-1][c_dest] == nullptr) && (board[r_dest][c_dest] == nullptr)) return true;
		if ((Distance_row == -1) && (abs(Distance_col) == 1) && (board[r_dest][c_dest] != nullptr)) {
			if (board[r_dest][c_dest]->getColour() == Colour::White) return true;
		}
		//en passant
		if ((Distance_row == -1) && (abs(Distance_col) == 1) && (board[r_dest][c_dest] == nullptr) && (board[r_orig][c_dest] != nullptr)) {
			if ((board[r_orig][c_dest]->getColour() == Colour::White) && (board[r_orig][c_dest]->getName() == "Pawn") 
				&& board[r_orig][c_dest]->getEP()) {
				return true;
			}
		}
		return false;
	}
	else{
		if ((Distance_row == 1) && (Distance_col == 0) && (board[r_dest][c_dest] == nullptr)) return true;
		if (this->nevermoved() && (Distance_row == 2) && (Distance_col == 0) && 
			(board[r_dest+1][c_dest] == nullptr) && (board[r_dest][c_dest] == nullptr)) return true;
		if ((Distance_row == 1) && (abs(Distance_col) == 1) && (board[r_dest][c_dest] != nullptr)) {
			if (board[r_dest][c_dest]->getColour() == Colour::Black) return true;
		}
		//en passant
		if ((Distance_row == 1) && (abs(Distance_col) == 1) && (board[r_dest][c_dest] == nullptr) && (board[r_orig][c_dest] != nullptr)) {
			if ((board[r_orig][c_dest]->getColour() == Colour::Black) && (board[r_orig][c_dest]->getName() == "Pawn") 
				&& board[r_orig][c_dest]->getEP()) {
				return true;
			}
		}
		return false;
	}
}


std::vector<pos> Pawn::Valid_moves(std::vector<std::vector<Piece*>> &board, Colour currentcolour){
		vector<pos> poses;
	int r = this->getRow();
	int c = this->getCol();
			if(this->nevermoved() == true){
				if(currentcolour == Colour::Black){
					if((r+2 < 8) && (!board[r+2][c]) && (!board[r+1][c])) {
					pos point = pos{c,r+2};
			        poses.emplace_back(point);
					}
				}
				if(currentcolour == Colour::White){
					if(r-2 >= 0 && (!board[r-2][c]) && (!board[r-1][c])) {
					pos point = pos{c,r-2};
			        poses.emplace_back(point);
					}
				}
			}
			if(currentcolour == Colour::White){
				if((r-1 >= 0) && (!board[r-1][c])) {
						pos point = pos{c,r-1};
				        poses.emplace_back(point);
				}
				if((r-1 >= 0 && c-1 >= 0) && ((board[r-1][c-1]) && board[r-1][c-1]->getColour() != currentcolour)){
					    pos point = pos{c-1,r-1};
				        poses.emplace_back(point);
				}
				if((r-1 >= 0 && c+1 < 8) && ((board[r-1][c+1]) && board[r-1][c+1]->getColour() != currentcolour)){
					    pos point = pos{c+1,r-1};
				        poses.emplace_back(point);
				}
				//en passant
				if((r-1 >= 0 && c-1 >= 0) && (board[r][c-1])) {
					if ( (board[r][c-1]->getColour() == Colour::Black) && (board[r][c-1]->getName() == "Pawn") && board[r][c-1]->getEP()) {
					    pos point = pos{c-1,r-1};
				        poses.emplace_back(point);
				}}
				if((r-1 >= 0 && c+1 < 8) && (board[r][c+1])) {
					if ( (board[r][c+1]->getColour() == Colour::Black) && (board[r][c+1]->getName() == "Pawn") && board[r][c+1]->getEP()) {
					    pos point = pos{c+1,r-1};
				        poses.emplace_back(point);
				}}
				}

		   if(currentcolour == Colour::Black){
				if((r+1 < 8) && (!board[r+1][c])) {
						pos point = pos{c,r+1};
				        poses.emplace_back(point);
				}if((r+1 < 8 && c+1 < 8) && ((board[r+1][c+1]) && board[r+1][c+1]->getColour() != currentcolour)) {
	 					pos point = pos{c+1,r+1};
				        poses.emplace_back(point);
				}
				if(r+1 < 8 && c-1 >= 0 && ((board[r+1][c-1]) && board[r+1][c-1]->getColour() != currentcolour)) {
	 					pos point = pos{c-1,r+1};
				        poses.emplace_back(point);
				}
				//en passant
				if((r+1 < 8 && c-1 >= 0) && (board[r][c-1])) {
					if ( (board[r][c-1]->getColour() == Colour::White) && (board[r][c-1]->getName() == "Pawn") && board[r][c-1]->getEP()) {
					    pos point = pos{c-1,r+1};
				        poses.emplace_back(point);
				}}
				if((r+1 < 8 && c+1 < 8) && (board[r][c+1])) {
					if ( (board[r][c+1]->getColour() == Colour::White) && (board[r][c+1]->getName() == "Pawn") && board[r][c+1]->getEP()) {
					    pos point = pos{c+1,r+1};
				        poses.emplace_back(point);
				}}
		}
	return poses;
}


