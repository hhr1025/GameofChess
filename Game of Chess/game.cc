#include <iostream>
#include <vector>
#include <string>
#include <vector>
#include "piece.h"
#include "king.h"
#include "queen.h"
#include "bishop.h"
#include "rook.h"
#include "knight.h"
#include "pawn.h"
#include "state.h"
#include "game.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"

using namespace std;

// Destructor
Game::~Game(){
}



Game::Game(){
  for(int r = 0; r < 8; r++){
    theBoard.emplace_back();
    for (int c = 0; c < 8; c++){
      Piece * pieceptr = nullptr;
      theBoard.back().emplace_back(pieceptr);
    }
  }
   td = std::make_unique<TextDisplay>();
   TextDisplay * tdcopy = td.get(); 
   attach(tdcopy);
   gd = std::make_unique<GraphicsDisplay>();
   GraphicsDisplay * gdcopy = gd.get(); 
   attach(gdcopy);
}

void Game::clearBoard(){
  for(int r = 0; r < 8; r++){
    for (int c = 0; c < 8; c++){
      if (theBoard[r][c]) removePiece(c, r);
    }
  }
  White_Holds.clear();
  Black_Holds.clear();
}


void Game::init(){
  for (int r = 0; r < 8; r++){
    for (int c = 0; c < 8; c++){
      if ((r == 0) && (c == 0))  {setPiece(c,r,"rook",Colour::Black);}
      if ((r == 0) && (c == 1))  {setPiece(c,r,"knight",Colour::Black);}
      if ((r == 0) && (c == 2))  {setPiece(c,r,"bishop",Colour::Black);}
      if ((r == 0) && (c == 3))  {setPiece(c,r,"queen",Colour::Black);}
      if ((r == 0) && (c == 4))  {setPiece(c,r,"king",Colour::Black);}
      if ((r == 0) && (c == 5))  {setPiece(c,r,"bishop",Colour::Black);}
      if ((r == 0) && (c == 6))  {setPiece(c,r,"knight",Colour::Black);}
      if ((r == 0) && (c == 7))  {setPiece(c,r,"rook",Colour::Black);}
        if (r == 1)                {setPiece(c,r,"pawn",Colour::Black);}
        if ((r == 7) && (c == 0))  {setPiece(c,r,"rook",Colour::White);}
      if ((r == 7) && (c == 1))  {setPiece(c,r,"knight",Colour::White);}
      if ((r == 7) && (c == 2))  {setPiece(c,r,"bishop",Colour::White);}
      if ((r == 7) && (c == 3))  {setPiece(c,r,"queen",Colour::White);}
        if ((r == 7) && (c == 4))  {setPiece(c,r,"king",Colour::White);}
        if ((r == 7) && (c == 5))  {setPiece(c,r,"bishop",Colour::White);}
      if ((r == 7) && (c == 6))  {setPiece(c,r,"knight",Colour::White);}
        if ((r == 7) && (c == 7))  {setPiece(c,r,"rook",Colour::White);}
        if (r == 6)                {setPiece(c,r,"pawn",Colour::White);}
    }
  }
}

 void Game::setPiece(int c, int r, string name, Colour colour){
    if (name == "king"){
      if ((colour == Colour::Black) && (blackking)){
          string message = "Can't have two kings for Black.";
          throw message;
      }
      else if ((colour == Colour::White) && (whiteking)){
        string message = "Can't have two kings for White.";
        throw message;
      }
    }
    if (theBoard[r][c]) removePiece(c, r);
    shared_ptr<Piece> ownerptr;
    if (name == "king"){
      ownerptr = make_shared<King>(c,r,colour);
      theBoard[r][c] = ownerptr.get();
      if (colour == Colour::Black) {
        blackking = theBoard[r][c];
        State pState{ c, r, c, r, "King", StateType::NewPiece, colour};
        setState(pState);
      }
      else {
        whiteking = theBoard[r][c];
        State pState{ c, r, c, r,"King", StateType::NewPiece, colour};
        setState(pState);
      }
    }
    else if(name == "queen"){
      ownerptr = make_shared<Queen>(c,r,colour);
      State pState{ c, r, c, r, "Queen", StateType::NewPiece, colour};
      setState(pState);
    }
    else if(name == "pawn"){
      if ((r == 0) || (r == 7)){
        string message = "Pawn can't be at the first row or the last row.";
        throw message;
      }
      ownerptr = make_shared<Pawn>(c,r,colour);
      State pState{ c, r, c, r, "Pawn", StateType::NewPiece, colour};
      setState(pState);
    }
    else if(name == "knight"){
      ownerptr = make_shared<Knight>(c,r,colour);
      State pState{ c, r, c, r, "Knight", StateType::NewPiece, colour};
      setState(pState);
    }
    else if(name == "bishop"){
      ownerptr = make_shared<Bishop>(c,r,colour);
      State pState{ c, r, c, r, "Bishop", StateType::NewPiece, colour};
      setState(pState);
    }
    else {
      ownerptr = make_shared<Rook>(c,r,colour);
      State pState{ c, r, c, r, "Rook", StateType::NewPiece, colour};
      setState(pState);
    }
    if (colour == Colour::Black) {
      Black_Holds.emplace_back(ownerptr);
    //  cout << "Black has " << Black_Holds.size()<< endl;
    }
    else {
      White_Holds.emplace_back(ownerptr);
    //  cout << "Whtie has " << White_Holds.size()<< endl;
    }
    theBoard[r][c] = ownerptr.get();
    notifyObservers();
} 


bool Game::hasblackking(){
  return blackking;
}

bool Game::haswhiteking(){
  return whiteking;
}

bool Game::white_incheck(){
  int c = whiteking->getCol();
  int r = whiteking->getRow();
  return whiteking->underAttack(c,r,theBoard);
}
bool Game::black_incheck(){
  int c = blackking->getCol();
  int r = blackking->getRow();
  return blackking->underAttack(c,r,theBoard);
}



bool Game::whiteCheckmate(){
  int piece_count = White_Holds.size();
 // cout << "Piece count is " << piece_count << endl;
  for (int i = 0; i < piece_count; ++i){
    if (White_Holds.at(i)->isalive()){
    int c_orig = White_Holds.at(i)->getCol();
    int r_orig = White_Holds.at(i)->getRow();
    vector<pos> move_vector = White_Holds.at(i)->Valid_moves(theBoard,Colour::White);
    int move_count = move_vector.size();
    for (int j = 0; j < move_count; j++){
      int c_dest = move_vector.at(j).col;
      int r_dest = move_vector.at(j).row;
    // cout << "Checking white" << White_Holds.at(i)->getName()<< " at " << c_orig << " " << r_orig << endl;
    //  cout << "c_dest is " << c_dest << " r_dest is " << r_dest << endl;
    //  cout << "c_dest is " << c_dest << "r_dest is " << r_dest  << endl;
      if (!expose_king(c_orig, r_orig,c_dest,r_dest,Colour::White)) return false;
    }
  }
  }
 // return false;
  return true;
}

bool Game::blackCheckmate(){
  int piece_count = Black_Holds.size();
 // cout << "Piece count is " << piece_count << endl;
  for (int i = 0; i < piece_count; ++i){
    if (Black_Holds.at(i)->isalive()){
    int c_orig = Black_Holds.at(i)->getCol();
    int r_orig = Black_Holds.at(i)->getRow();
    vector<pos> move_vector = Black_Holds.at(i)->Valid_moves(theBoard,Colour::Black);
    int move_count = move_vector.size();
    for (int j = 0; j < move_count; j++){
      int c_dest = move_vector.at(j).col;
      int r_dest = move_vector.at(j).row;
      //cout << "Checking black" << Black_Holds.at(i)->getName()<< " at " << c_orig << " " << r_orig << endl;
      //cout << "c_dest is " << c_dest << " r_dest is " << r_dest << endl;
      if (!expose_king(c_orig, r_orig,c_dest,r_dest,Colour::Black)) return false;
    }
    }
  }
  //return false;
  return true;
}

bool Game::expose_king(int c_orig,int r_orig,int c_dest,int r_dest,Colour colour){
  Piece * tempptr = theBoard[r_dest][c_dest];
  theBoard[r_dest][c_dest] = theBoard[r_orig][c_orig];
  theBoard[r_dest][c_dest]->setRow(r_dest);
  theBoard[r_dest][c_dest]->setCol(c_dest);
  theBoard[r_orig][c_orig] = nullptr;
  bool ret;
  if (colour == Colour::Black){
    ret = black_incheck();
  }
  else{
    ret = white_incheck();
  }
  theBoard[r_orig][c_orig] = theBoard[r_dest][c_dest];
  theBoard[r_orig][c_orig]->setRow(r_orig);
  theBoard[r_orig][c_orig]->setCol(c_orig);
  theBoard[r_dest][c_dest] = tempptr;
  return ret;
}

// check if there is any piece from (r_orig, c_orig) to (r_dest, c_dest) 
// the path needs to be consisted of only nullptrs (not including the origin and destination)
bool Game::isBlocked(int c_orig, int r_orig, int c_dest, int r_dest){ 
  //N
  if ((c_dest == c_orig) && (r_dest < r_orig)){
    for (int i = r_orig - 1; i > r_dest ; --i){
      if (theBoard[i][c_orig]) return true;
    }
  }
  //S
  if ((c_dest == c_orig) && (r_dest > r_orig)){
    for (int i = r_orig + 1; i < r_dest ; ++i){
      if (theBoard[i][c_orig]) return true;
    }
  }
  //W
  if ((r_dest == r_orig) && (c_dest < c_orig)){
    for (int i = c_orig - 1; i > c_dest ; --i){
      if (theBoard[r_orig][i]) return true;
    }
  }
  //E
  if ((r_dest == r_orig) && (c_dest > c_orig)){
    for (int i = c_orig + 1; i < c_dest ; ++i){
      if (theBoard[r_orig][i]) return true;
    }
  }
  //NW
  if ((c_dest < c_orig) && (r_dest < r_orig) && (abs(c_dest - c_orig) == abs(c_dest - c_orig))) {
    for (int i = r_orig - 1, j = c_orig - 1; i > r_dest && j > c_dest ; --i, --j){
      if (theBoard[i][j]) return true;
    }
  }
  //NE
  if ((c_dest > c_orig) && (r_dest < r_orig) && (abs(c_dest - c_orig) == abs(c_dest - c_orig))) {
    for (int i = r_orig - 1, j = c_orig + 1; i > r_dest && j < c_dest ; --i, ++j){
      if (theBoard[i][j]) return true;
    }
  }
  //SE
  if ((c_dest < c_orig) && (r_dest > r_orig) && (abs(c_dest - c_orig) == abs(c_dest - c_orig))) {
    for (int i = r_orig + 1, j = c_orig - 1; i < r_dest && j > c_dest ; ++i, --j){
      if (theBoard[i][j]) return true;
    }
  }
  //SW
  if ((c_dest > c_orig) && (r_dest > r_orig) && (abs(c_dest - c_orig) == abs(c_dest - c_orig))) {
    for (int i = r_orig + 1, j = c_orig + 1; i < r_dest && j < c_dest ; ++i, ++j){
      if (theBoard[i][j]) return true;
    }
  }
  return false;
}

void Game::setBoardEP(){
  for(int r = 0; r < 8; r++){
    for (int c = 0; c < 8; c++){
      if (theBoard[r][c]) theBoard[r][c]->setEPfalse();
    }
  }
}

void Game::move(int c_orig,int r_orig,int c_dest,int r_dest){
  //cout << c_orig << r_orig << c_dest << r_dest << endl;
  if ((theBoard[r_dest][c_dest] == nullptr) && (theBoard[r_orig][c_orig]->getName() == "Pawn") && (c_orig != c_dest)) {
    removePiece(c_dest,r_orig);       
  }
  if(theBoard[r_dest][c_dest] != nullptr){
    removePiece(c_dest,r_dest);       
  }
  theBoard[r_dest][c_dest] = theBoard[r_orig][c_orig]; 
  theBoard[r_orig][c_orig] = nullptr; 
  theBoard[r_dest][c_dest]->setRow(r_dest);  
  theBoard[r_dest][c_dest]->setCol(c_dest);
  theBoard[r_dest][c_dest]->setNeverMoved();
  State pState{c_orig,r_orig,c_dest,r_dest,theBoard[r_dest][c_dest]->getName(), StateType:: MovePiece, theBoard[r_dest][c_dest]->getColour()};
  setState(pState);
  notifyObservers();
  if (theBoard[r_dest][c_dest]->getName() == "Pawn"){
    //promotion
    if (r_dest == 0 || r_dest == 7) throw true;
    //en passant
    if (abs(r_dest-r_orig) == 2) theBoard[r_dest][c_dest]->setEPtrue();
  }
  if (theBoard[r_dest][c_dest]->getName() == "King"){
    if (c_dest == c_orig + 2){
      theBoard[r_dest][c_dest-1] = theBoard[r_dest][c_dest+2]; 
      move(c_dest+1,r_dest,c_dest-1,r_dest);
    }
    if (c_dest == c_orig - 2){
      theBoard[r_dest][c_dest+1] = theBoard[r_dest][c_dest-2]; 
      move(c_dest-2,r_dest,c_dest+1,r_dest);
    }
  }
}


void Game::checkStatus(Colour colour){
  if (colour == Colour::White){
    if (blackCheckmate() && black_incheck()){
        cout << "Checkmate! White wins!" << endl;
        throw Colour::White;
    }
    else if (blackCheckmate() && !black_incheck()){
        cout << "Stalemate!"<< endl;
        throw Colour::NoColour;
    }
    else if (black_incheck()){
      cout << "Black is in check." << endl;
    }
    else{
      return;
    }
  }
  else{
    if (whiteCheckmate() && white_incheck()){
        cout << "Checkmate! Black wins!" << endl;
        throw Colour::Black;
    }
    else if (whiteCheckmate() && ! white_incheck()){
        cout << "Stalemate!"<< endl;
        throw Colour::NoColour;
    }
    else if (white_incheck()){
      cout << "White is in check." << endl;
    }
    else{
      return;
    }
  }
}


 void Game::movePiece(int c_orig,int r_orig,int c_dest,int r_dest,Colour colour){
  //check if there is a piece at the original location
  if (! theBoard[r_orig][c_orig]){
    string message = "There is no piece there. Make a valid move:";
    throw message;
  }
  //check if (c_orig,r_orig) == (c_dest, r_dest)
  if ((c_orig == c_dest) && (r_orig == r_dest)){
    string message = "You gotta move. Make a valid move"; 
    throw message;
  }
  //check if colour = currentcolour
  if(colour != theBoard[r_orig][c_orig]->getColour()){
    string message = "That's not your piece. Make a valid move";     
    throw message;  
  }
  //check if you have one of your pieces at your destination location
  if ((theBoard[r_dest][c_dest])&&(colour == theBoard[r_dest][c_dest]->getColour())) {
    string message = "You already have a piece there. Make a valid move";    
    throw message;  
  }
  //check if it is a legit move
  if (!theBoard[r_orig][c_orig]->isValidMove(c_dest, r_dest,theBoard)){
    string message = "That piece doesn't move like that. Make a valid move";    
    throw message; 
  }
  //check if  blocked
  if (isBlocked(c_orig, r_orig, c_dest, r_dest)){
    string message = "Your piece is blocked. Make a valid move";    
    throw message; 
  }
  //check if it is gonna expose the king
  if (expose_king(c_orig,r_orig,c_dest,r_dest,colour)){
    string message = "Can't leave your king in check";
    throw message;
  }
  setBoardEP();
  move(c_orig, r_orig,c_dest,r_dest);
  checkStatus(colour);
}


void Game::removePiece(int c, int r){
    if (! theBoard[r][c]){
      string message = "There is no piece there";
      throw message;
    }
    if (theBoard[r][c]->getName() == "King"){
      if (theBoard[r][c]->getColour() == Colour::White) whiteking = nullptr;
      if (theBoard[r][c]->getColour() == Colour::Black) blackking = nullptr;
    }
    theBoard[r][c]->setDead();
    State pState{c,r,c,r,theBoard[r][c]->getName(),StateType:: RemovePiece,theBoard[r][c]->getColour()};
    setState(pState);
    notifyObservers();
    theBoard[r][c] = nullptr;
}


void Game::computer_promotion(int c_dest,int r_dest, Colour colour){
  int promotion_piece = rand() % 8;
  if (promotion_piece == 0){
    setPiece(c_dest,r_dest,"knight",colour); 
  }
  else if (promotion_piece == 1){
    setPiece(c_dest,r_dest,"rook",colour); 
  }
  else if (promotion_piece == 2){
    setPiece(c_dest,r_dest,"bishop",colour); 
  }
  else{
    setPiece(c_dest,r_dest,"queen",colour); 
  }
}

void Game::random_move(Colour colour){
srand((unsigned)time(NULL));  
if(colour == Colour::Black){
  int piece_count = Black_Holds.size();
  int random_piece = rand() % piece_count;
  for (int i = 0; i < piece_count; ++i){
    int piece_index = (i + random_piece) % piece_count;
    if (Black_Holds[piece_index]->isalive()){
      int r_orig = Black_Holds[piece_index]->getRow();
      int c_orig = Black_Holds[piece_index]->getCol();
      vector<pos> move_vector = Black_Holds[piece_index]->Valid_moves(theBoard,Colour::Black);
      int move_count = move_vector.size();
      if (move_count != 0){
      int random_pos = rand() % move_count;
      for (int j = 0; j < move_count; j++){
        int move_index = (j + random_pos) % move_count;
        int c_dest = move_vector.at(move_index).col;
        int r_dest = move_vector.at(move_index).row;
        if (!expose_king(c_orig, r_orig,c_dest,r_dest,Colour::Black)){
          try{
            move(c_orig, r_orig,c_dest,r_dest);
          }
          catch(bool promotion){
            computer_promotion(c_dest,r_dest,colour);
          }
          checkStatus(colour);
          return;
          }
        }
    }}
  }
}
else{
  int piece_count = White_Holds.size();
  int random_piece = rand() % piece_count;
  for (int i = 0; i < piece_count; ++i){
    int piece_index = (i + random_piece) % piece_count;
    if (White_Holds[piece_index]->isalive()){
      int r_orig = White_Holds[piece_index]->getRow();
      int c_orig = White_Holds[piece_index]->getCol();
      vector<pos> move_vector = White_Holds[piece_index]->Valid_moves(theBoard,Colour::White);
      int move_count = move_vector.size();
      if (move_count != 0){
      int random_pos = rand() % move_count;
      for (int j = 0; j < move_count; j++){
        int move_index = (j + random_pos) % move_count;
        int c_dest = move_vector.at(move_index).col;
        int r_dest = move_vector.at(move_index).row;
        if (!expose_king(c_orig, r_orig,c_dest,r_dest,Colour::White)){
          try{
            move(c_orig, r_orig,c_dest,r_dest);
          }
          catch(bool promotion){
            computer_promotion(c_dest,r_dest,colour);
          }
          checkStatus(colour);
          return;
        }
      }
    }}
  }
}
}

void Game::attack_move(Colour colour){
  srand((unsigned)time(NULL));  
  if(colour == Colour::Black){
    int piece_count = Black_Holds.size();
    int random_piece = rand() % piece_count;
    for (int i = 0; i < piece_count; ++i){
    int piece_index = (i + random_piece) % piece_count;
    if (Black_Holds[piece_index]->isalive()){
      int c_orig = Black_Holds[piece_index]->getCol();
      int r_orig = Black_Holds[piece_index]->getRow();
      auto positions = theBoard[r_orig][c_orig]->Valid_moves(theBoard,colour);
      int move_count = positions.size();
      if (move_count != 0){
      int random_pos = rand() % move_count;
      for (int j = 0; j < move_count; j++){
        int move_index = (j + random_pos) % move_count;
        int c_dest = positions.at(move_index).col;
        int r_dest = positions.at(move_index).row;
        if(theBoard[r_dest][c_dest] && (!expose_king(c_orig, r_orig,c_dest ,r_dest ,colour))) {
          try{
            move(c_orig, r_orig,c_dest,r_dest);
          }
          catch(bool promotion){
            computer_promotion(c_dest,r_dest,colour);
          }
          checkStatus(colour);
          return;
        }
      }
    }}}
  }
  else{
    int piece_count = White_Holds.size();
    int random_piece = rand() % piece_count;
    for (int i = 0; i < piece_count; ++i){
    int piece_index = (i + random_piece) % piece_count;
    if (White_Holds[piece_index]->isalive()){
      int c_orig = White_Holds[piece_index]->getCol();
      int r_orig = White_Holds[piece_index]->getRow();
      auto positions = theBoard[r_orig][c_orig]->Valid_moves(theBoard,colour);
      int move_count = positions.size();
      if (move_count != 0){
      int random_pos = rand() % move_count;
      for (int j = 0; j < move_count; j++){
        int move_index = (j + random_pos) % move_count;
        int c_dest = positions.at(move_index).col;
        int r_dest = positions.at(move_index).row;
        if(theBoard[r_dest][c_dest] && (!expose_king(c_orig, r_orig,c_dest ,r_dest ,colour))) {
          try{
            move(c_orig, r_orig,c_dest,r_dest);
          }
          catch(bool promotion){
            computer_promotion(c_dest,r_dest,colour);
          }
          checkStatus(colour);
          return;
        }
      }
    }}}
  }
  random_move(colour);
}



void Game::defend_move(Colour colour){
  srand((unsigned)time(NULL));  
  if(colour == Colour::Black){
    int piece_count = Black_Holds.size();
    int random_piece = rand() % piece_count;
    for (int i = 0; i < piece_count; ++i){
    int piece_index = (i + random_piece) % piece_count;
    if (Black_Holds[piece_index]->isalive()){
      int c_orig = Black_Holds[piece_index]->getCol();
      int r_orig = Black_Holds[piece_index]->getRow();
      auto positions = theBoard[r_orig][c_orig]->Valid_moves(theBoard,colour);
      int move_count = positions.size();
      if (move_count != 0){
      int random_pos = rand() % move_count;
      for (int j = 0; j < move_count; j++){
        int move_index = (j + random_pos) % move_count;
        int c_dest = positions.at(move_index).col;
        int r_dest = positions.at(move_index).row;
        if( theBoard[r_orig][c_orig]->underAttack(c_orig,r_orig,theBoard) && (!expose_king(c_orig, r_orig,c_dest ,r_dest ,colour))
          && !theBoard[r_orig][c_orig]->underAttack(c_dest,r_dest,theBoard) ) {
          try{
            move(c_orig, r_orig,c_dest,r_dest);
          }
          catch(bool promotion){
            computer_promotion(c_dest,r_dest,colour);
          }
          checkStatus(colour);
          return;
        }
      }
    }}}
  }
  else{
    int piece_count = White_Holds.size();
    int random_piece = rand() % piece_count;
    for (int i = 0; i < piece_count; ++i){
    int piece_index = (i + random_piece) % piece_count;
    if (White_Holds[piece_index]->isalive()){
      int c_orig = White_Holds[piece_index]->getCol();
      int r_orig = White_Holds[piece_index]->getRow();
      auto positions = theBoard[r_orig][c_orig]->Valid_moves(theBoard,colour);
      int move_count = positions.size();
      if (move_count != 0){
      int random_pos = rand() % move_count;
      for (int j = 0; j < move_count; j++){
        int move_index = (j + random_pos) % move_count;
        int c_dest = positions.at(move_index).col;
        int r_dest = positions.at(move_index).row;
        if( theBoard[r_orig][c_orig]->underAttack(c_orig,r_orig,theBoard) && (!expose_king(c_orig, r_orig,c_dest ,r_dest ,colour))
          && !theBoard[r_orig][c_orig]->underAttack(c_dest,r_dest,theBoard) ) {
          try{
            move(c_orig, r_orig,c_dest,r_dest);
          }
          catch(bool promotion){
            computer_promotion(c_dest,r_dest,colour);
          }
          checkStatus(colour);
          return;
        }
      }
    }}}
  }
  random_move(colour);
}
void Game::smart_move(Colour colour){
  int max_power = 0;
  int max_holds_index = -1;
  int threat = 300;
  int max_pos = -1;
  int max_col = -1;
  int max_row = -1;
  auto curr_holds = Black_Holds;
  if(colour == Colour::White){
    curr_holds = White_Holds;
  }
  int lenth = curr_holds.size();
  for(int i = 0; i < lenth; ++i){
    if(curr_holds[i]->isalive() && curr_holds[i]->underAttack(curr_holds[i]->getCol(), curr_holds[i]->getRow(), theBoard) != 0 &&
    (!(curr_holds[i]->Valid_moves(theBoard,colour)).empty()) && curr_holds[i]->getPower() > max_power){
      max_power = curr_holds[i]->getPower();
      max_holds_index = i;
    }
  }
  if(max_holds_index != -1) {
  auto moves = curr_holds[max_holds_index]->Valid_moves(theBoard,colour);
  int lenth = moves.size();
  for(int i = 0; i < lenth; ++i){
    if(curr_holds[max_holds_index]->underAttack(moves[i].col, moves[i].row, theBoard) < threat &&
      (!expose_king(curr_holds[max_holds_index]->getCol(), curr_holds[max_holds_index]->getRow(),moves[i].col,moves[i].row,curr_holds[max_holds_index]->getColour()))){
        threat = curr_holds[max_holds_index]->underAttack(moves[i].col, moves[i].row, theBoard);
        max_pos = i;
        max_col = moves[i].col;
        max_row = moves[i].row;
    }
  }
}
int holds_num = -1;
for(int i = 0; i < lenth; ++i){
    if(curr_holds[i] && curr_holds[i]->isalive()) holds_num++;
}
if(max_pos != -1 && holds_num < 9){
    int orig_r = curr_holds[max_holds_index]->getRow();
    int orig_c = curr_holds[max_holds_index]->getCol();
    try{
            move(orig_c, orig_r,max_col, max_row);
          }
          catch(bool promotion){
            computer_promotion(max_col, max_row,colour);
          }
          checkStatus(colour);
          return;
  }
else {
  attack_move(colour);
 
}
}

// the method prints out the grid
std::ostream &operator<<(std::ostream &out, const Game &g){
  out << *g.td;
  return out;
  
}

