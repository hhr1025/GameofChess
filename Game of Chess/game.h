#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <vector>
#include <memory>
#include <cstddef>
#include "piece.h"
#include "king.h"
#include "state.h"

class TextDisplay;
class GraphicsDisplay;


class Game: public Subject<State> {
  Piece * whiteking = nullptr;
  Piece * blackking = nullptr;
  std::vector<std::vector<Piece*>> theBoard;  // The actual board.
  std::unique_ptr<TextDisplay> td; // The text display.
  std::unique_ptr<GraphicsDisplay> gd; // The text display.
  std::vector<std::shared_ptr<Piece>> White_Holds;//White's pieces
  std::vector<std::shared_ptr<Piece>> Black_Holds;//Black's pieces


 public:
   Game();
   ~Game();

   // standard initialization
  void init(); 
  // create the actual object (a piece), store the pointer to the object at theBoard[r][c]
  void setPiece(int c, int r, std::string name, Colour colour); 

   bool hasblackking();
   bool haswhiteking();
   //check if white king is under attack
   bool white_incheck();
   //check if black king is under attack
   bool black_incheck();

   //check if white player has a valid move in the next play
   // method is used to check checkmate and stalemate
  bool whiteCheckmate();

   //check if black player has a valid move in the next play
   // method is used to check checkmate and stalemate
  bool blackCheckmate();

  bool expose_king(int c_orig,int r_orig,int c_dest,int r_dest,Colour colour);
  bool isBlocked(int c_orig, int r_orig, int c_dest, int r_dest);
  void move(int c_orig,int r_orig,int c_dest,int r_dest);
  void checkStatus(Colour colour);



  // throw an exception if the movement is not legal (moving opponent's piece, not on the piece path, 
  // blocked by other pieces, capturing your own pieces or exposing your king)
  // if legal, if there is no opponent's piece at theBoard[r_dest][c_dest], swap the pointers
  // else, delete the opponent's piece
  // theBoard[r_dest][c_dest] now points at the object and theBoard[r][c] = nullptr
  void movePiece(int c_orig,int r_orig,int c_dest,int r_dest,Colour colour);

  //this method is for the deletion of a piece in the setup mode only (in main, - e1).
  void removePiece(int c, int r);

  void computer_promotion(int c_dest,int r_dest, Colour colour);

  void setBoardEP();

  void clearBoard();

  void attack_move(Colour colour);
  void defend_move(Colour colour);
  void random_move(Colour colour);
  void smart_move(Colour colour);
  
  

  friend std::ostream &operator<<(std::ostream &out, const Game &g);
};

#endif

