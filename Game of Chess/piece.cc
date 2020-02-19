#include "state.h"
#include "piece.h"
#include <cmath>

Piece::~Piece() {}

int Piece:: getRow(){
	return r;
}

int Piece:: getCol(){
	return c;
}

Colour Piece:: getColour(){
	return colour;
}

void Piece:: setRow(int r){
	this->r = r;
}

void Piece:: setCol(int c){
	this->c = c;
}

bool Piece:: nevermoved(){
	return nevermoved_boo;
}

void Piece:: setNeverMoved(){
	nevermoved_boo = false;
}

bool Piece::isalive(){
	return alive;
}

bool Piece::getEP(){
	return enpassant;
}

void Piece::setEPtrue(){
	enpassant = true;
}
void Piece::setEPfalse(){
	enpassant = false;
}




void Piece::setDead(){
	alive = false;
}

int Piece:: underAttack(int c_dest, int r_dest, std::vector<std::vector<Piece*>> &theBoard){
	int count = 0;
	int curr_r = r;
	int curr_c = c;
	Piece* temp = theBoard[curr_r][curr_c];
	theBoard[curr_r][curr_c] = nullptr;

 	// General check
	// check for Pawn

	if ((r_dest > 0) && (c_dest > 0)){
			if(theBoard[r_dest-1][c_dest-1]){
				if ((theBoard[r_dest-1][c_dest-1]->colour == Colour::Black) && (this->colour == Colour::White) && (theBoard[r_dest-1][c_dest-1]->getName() == "Pawn")) count++;
			}
		}
		if ((r_dest < 7) && (c_dest > 0)){
			if(theBoard[r_dest+1][c_dest-1]){
				if ((theBoard[r_dest+1][c_dest-1]->colour == Colour::White) && (this->colour == Colour::Black) && (theBoard[r_dest+1][c_dest-1]->getName() == "Pawn")) count++;
			}
		}
		if ((r_dest > 0) && (c_dest < 7)){
			if(theBoard[r_dest-1][c_dest+1]){
				if ((theBoard[r_dest-1][c_dest+1]->colour == Colour::Black) && (this->colour == Colour::White) && (theBoard[r_dest-1][c_dest+1]->getName() == "Pawn")) count++;
			}
		}
		if ((r_dest < 7) && (c_dest < 7)){
			if(theBoard[r_dest+1][c_dest+1]){
				if ((theBoard[r_dest+1][c_dest+1]->colour == Colour::White) && (this->colour == Colour::Black) && (theBoard[r_dest+1][c_dest+1]->getName() == "Pawn")) count++;
			}
		}


	//check for knight
	for (int i = 0; i <= 7; ++i){
		for (int j = 0; j <= 7; ++j){
			int Distance_row = i - r_dest;
			int Distance_col = j - c_dest;
			if (abs(Distance_row)*abs(Distance_col) == 2){
				if(theBoard[i][j]){
					if((theBoard[i][j]->colour != this->colour) && (theBoard[i][j]->getName() == "Knight")) count++;
				}
			}
		}
	}


	//check for rook and queen
		for (int i = r_dest + 1; i <= 7; ++i){
			if (theBoard[i][c_dest]){
				if (theBoard[i][c_dest]->colour == this->colour){
					break;
				}
				else{
					if ((theBoard[i][c_dest]->getName() == "Rook") || (theBoard[i][c_dest]->getName() == "Queen")){
						count++;
					}
					break;
				}
			}
		}

		for (int i = r_dest - 1; i >= 0 ; --i){
			if (theBoard[i][c_dest]){
				if (theBoard[i][c_dest]->colour == this->colour){
					break;
				}
				else{
					if ((theBoard[i][c_dest]->getName() == "Rook") || (theBoard[i][c_dest]->getName() == "Queen")){
						count++;
					}
					break;
				}
			}
		}

		for (int i = c_dest + 1; i <= 7; ++i){
			if (theBoard[r_dest][i]){
				if (theBoard[r_dest][i]->colour == this->colour){
					break;
				}
				else{
					if ((theBoard[r_dest][i]->getName() == "Rook") || (theBoard[r_dest][i]->getName() == "Queen")){
						count++;
					}
					break;
				}
			}
		}

		for (int i = c_dest - 1; i >= 0; --i){
			if (theBoard[r_dest][i]){
				if (theBoard[r_dest][i]->colour == this->colour){
					break;
				}
				else{
					if ((theBoard[r_dest][i]->getName() == "Rook") || (theBoard[r_dest][i]->getName() == "Queen")){
						count++;
					}
					break;
				}
			}
		}

		//check for bishop and queen
		for(int i = r_dest-1, j = c_dest-1; i >= 0 && j >= 0; i--, j--){
				if(theBoard[i][j]){
					if (theBoard[i][j]->colour == this->colour){
					break;
				}
				else{
					if ((theBoard[i][j]->getName() == "Bishop") || (theBoard[i][j]->getName() == "Queen")){
						count++;
				}
				break;
				}
			}
		}
		for(int i = r_dest+1, j = c_dest+1 ; i < 8 && j < 8; i++, j++){
				if(theBoard[i][j]){
					if (theBoard[i][j]->colour == this->colour){
					break;
				}
				else{
					if ((theBoard[i][j]->getName() == "Bishop") || (theBoard[i][j]->getName() == "Queen")){
						count++;
				}
				break;
				}
		}
	}
		for(int i = r_dest-1, j = c_dest+1; i >= 0 && j < 8; i--, j++){
				if(theBoard[i][j]){
					if (theBoard[i][j]->colour == this->colour){
					break;
				}
				else{
					if ((theBoard[i][j]->getName() == "Bishop") || (theBoard[i][j]->getName() == "Queen")){
						count++;
				}
				break;
				}
		}}
		for(int i = r_dest+1, j = c_dest-1; i < 8 && j >= 0; i++, j --){
				if(theBoard[i][j]){
					if (theBoard[i][j]->colour == this->colour){
					break;
				}
				else{
					if ((theBoard[i][j]->getName() == "Bishop") || (theBoard[i][j]->getName() == "Queen")){
						count++;
				}
				break;
				}
		}}

		//check for king
		if (r_dest > 0){
			if(theBoard[r_dest-1][c_dest]){
				if ((theBoard[r_dest-1][c_dest]->colour != this->colour) && (theBoard[r_dest-1][c_dest]->getName() == "King")) count++;
			}
		}
		if (r_dest < 7){
			if(theBoard[r_dest+1][c_dest]){
				if ((theBoard[r_dest+1][c_dest]->colour != this->colour) && (theBoard[r_dest+1][c_dest]->getName() == "King")) count++;
			}
		}
		if (c_dest > 0){
			if(theBoard[r_dest][c_dest-1]){
				if ((theBoard[r_dest][c_dest-1]->colour != this->colour) && (theBoard[r_dest][c_dest-1]->getName() == "King")) count++;
			}
		}
		if (c_dest < 7){
			if(theBoard[r_dest][c_dest+1]){
				if ((theBoard[r_dest][c_dest+1]->colour != this->colour) && (theBoard[r_dest][c_dest+1]->getName() == "King")) count++;
			}
		}
		if ((r_dest > 0) && (c_dest > 0)){
			if(theBoard[r_dest-1][c_dest-1]){
				if ((theBoard[r_dest-1][c_dest-1]->colour != this->colour) && (theBoard[r_dest-1][c_dest-1]->getName() == "King")) count++;
			}
		}
		if ((r_dest < 7) && (c_dest > 0)){
			if(theBoard[r_dest+1][c_dest-1]){
				if ((theBoard[r_dest+1][c_dest-1]->colour != this->colour) && (theBoard[r_dest+1][c_dest-1]->getName() == "King")) count++;
			}
		}
		if ((r_dest > 0) && (c_dest < 7)){
			if(theBoard[r_dest-1][c_dest+1]){
				if ((theBoard[r_dest-1][c_dest+1]->colour != this->colour) && (theBoard[r_dest-1][c_dest+1]->getName() == "King")) count++;
			}
		}
		if ((r_dest < 7) && (c_dest < 7)) {
			if(theBoard[r_dest+1][c_dest+1]){
				if ((theBoard[r_dest+1][c_dest+1]->colour != this->colour) && (theBoard[r_dest+1][c_dest+1]->getName() == "King")) count++;
			}
		}
		
	theBoard[curr_r][curr_c] =  temp;
	return count;
}
	
