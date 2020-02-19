#include <iostream>
#include <string>
#include <sstream>
#include "game.h"
using namespace std;

// helper function
// if c,r >= 8, piecename invalid, throw exception - TBD
void callSetPiece(int c, int r, string piecename, Game &g)
{
  if ((c >= 0) && (c <= 7) && (r >= 0) && (r <= 7))
  {
    if (piecename == "k")
      g.setPiece(c, r, "king", Colour::Black);
    else if (piecename == "q")
      g.setPiece(c, r, "queen", Colour::Black);
    else if (piecename == "r")
      g.setPiece(c, r, "rook", Colour::Black);
    else if (piecename == "b")
      g.setPiece(c, r, "bishop", Colour::Black);
    else if (piecename == "n")
      g.setPiece(c, r, "knight", Colour::Black);
    else if (piecename == "p")
      g.setPiece(c, r, "pawn", Colour::Black);
    else if (piecename == "K")
      g.setPiece(c, r, "king", Colour::White);
    else if (piecename == "Q")
      g.setPiece(c, r, "queen", Colour::White);
    else if (piecename == "R")
      g.setPiece(c, r, "rook", Colour::White);
    else if (piecename == "B")
      g.setPiece(c, r, "bishop", Colour::White);
    else if (piecename == "N")
      g.setPiece(c, r, "knight", Colour::White);
    else if (piecename == "P")
      g.setPiece(c, r, "pawn", Colour::White);
    else
      cout << "Invalid Input" << endl;
  }
  else
  {
    cout << "Invalid Input" << c << r << endl;
  }
}

void human_move(Colour colour, int &tracker, Game &g)
{
  //read in the original (r,c) and the destination (r,c)
  string orig, dest;
  cin >> orig >> dest;
  istringstream ss1{orig};
  istringstream ss2{dest};
  char column_orig, column_dest;
  int r_orig, r_dest;
  ss1 >> column_orig >> r_orig;
  ss2 >> column_dest >> r_dest;
  int c_orig = column_orig - 'a';
  int c_dest = column_dest - 'a';
  r_orig = 8 - r_orig;
  r_dest = 8 - r_dest;
  try
  {
    g.movePiece(c_orig, r_orig, c_dest, r_dest, colour);
    tracker++;
  }
  catch (string message)
  {
    cout << message << endl;
  }
  catch (bool promotion)
  {
    while (true)
    {
      cout << "Promote your pawn! Enter a string from N,Q,B,R:" << endl;
      string piecename;
      cin >> piecename;
      if ((piecename == "N") || (piecename == "n"))
      {
        g.setPiece(c_dest, r_dest, "knight", colour);
        g.checkStatus(colour);
        tracker++;
        break;
      }
      else if ((piecename == "Q") || (piecename == "q"))
      {
        g.setPiece(c_dest, r_dest, "queen", colour);
        g.checkStatus(colour);
        tracker++;
        break;
      }
      else if ((piecename == "B") || (piecename == "b"))
      {
        g.setPiece(c_dest, r_dest, "bishop", colour);
        g.checkStatus(colour);
        tracker++;
        break;
      }
      else if ((piecename == "R") || (piecename == "r"))
      {
        g.setPiece(c_dest, r_dest, "rook", colour);
        g.checkStatus(colour);
        tracker++;
        break;
      }
      else
      {
        cout << "Wrong Input. Promote your pawn! Re-enter a string from N,Q,B,R:" << endl;
      }
    }
  }
}

int main(int argc, char *argv[])
{
  cin.exceptions(ios::eofbit | ios::failbit);
  string cmd;
  Game g;
  int tracker = 0;
  bool game_started = false;
  Colour colour = Colour::NoColour;
  string whiteplayer;
  string blackplayer;
  double whitescore = 0;
  double blackscore = 0;
  if (argc == 1)
  { // if there is at least one  argument
    cout << "Enter white-player: " << endl;
    cin >> whiteplayer;
    cout << "Enter black-player: " << endl;
    cin >> blackplayer;
  }
  else if (argc == 2)
  { // if there is at least one  argument
    whiteplayer = argv[1];
    cout << "Enter black-player: " << endl;
    cin >> blackplayer;
  }
  else
  {
    whiteplayer = argv[1];
    blackplayer = argv[2];
  }

  try
  {
    while (true)
    {
      cin >> cmd;
      if (cmd == "new")
      {
        g.clearBoard();
        g.init();
        game_started = true;
        cout << g;
      }
      else if (cmd == "move")
      {
        if (game_started)
        {
          try
          {
            if (tracker % 2 == 0)
            {
              colour = Colour::White;
              if (whiteplayer == "human")
                human_move(colour, tracker, g);
              else if (whiteplayer == "computer1")
              {
                g.random_move(colour);
                tracker++;
              }
              else if (whiteplayer == "computer2")
              {
                g.attack_move(colour);
                tracker++;
              }
              else if (whiteplayer == "computer3")
              {
                g.defend_move(colour);
                tracker++;
              }
              else if (whiteplayer == "computer4")
              {
                g.smart_move(colour);
                tracker++;
              }
              else
              {
                human_move(colour, tracker, g);
              }
            }
            else
            {
              colour = Colour::Black;
              if (blackplayer == "human")
                human_move(colour, tracker, g);
              else if (blackplayer == "computer1")
              {
                g.random_move(colour);
                tracker++;
              }
              else if (blackplayer == "computer2")
              {
                g.attack_move(colour);
                tracker++;
              }
              else if (blackplayer == "computer3")
              {
                g.defend_move(colour);
                tracker++;
              }
              else if (blackplayer == "computer4")
              {
                g.smart_move(colour);
                tracker++;
              }
              else
              {
                human_move(colour, tracker, g);
              }
            }
            cout << g;
          }

          catch (Colour win_colour)
          {
            if (win_colour == Colour::Black)
            {
              blackscore++;
            }
            else if (win_colour == Colour::White)
            {
              whitescore++;
            }
            else
            {
              blackscore = blackscore + 0.5;
              whitescore = whitescore + 0.5;
            }
            // g.clearBoard();
            game_started = false;
            cout << endl
                 << "Score: " << endl
                 << "White-player: " << whitescore << endl
                 << "Black-player: " << blackscore << endl
                 << endl;
            cout << "Another game?" << endl;
          }
        }
        else
          cout << "Initialize a game or setup manually." << endl;
      }
      else if (cmd == "resign")
      {
        if (tracker % 2 == 0)
        {
          cout << "White-player resigns. Black-player wins." << endl;
          blackscore++;
        }
        else
        {
          cout << "Black-player resigns. White-player wins." << endl;
          whitescore++;
        }
        g.clearBoard();
        tracker = 0;
        game_started = false;
        cout << endl
             << "Score: " << endl
             << "White-player: " << whitescore << endl
             << "Black-player: " << blackscore << endl
             << endl;
        cout << "Another game?" << endl;
      }
      else if (cmd == "setup")
      {
        if (game_started)
        {
          cout << "You can't setup the board once game has started!" << endl;
        }
        else
        {
          g.clearBoard();
          while (true)
          { //cout<<"setting up!"<<endl;
            string set;
            cin >> set;
            if (set == "+")
            { //place the piece
              string piecename;
              string dest;
              cin >> piecename >> dest;
              istringstream ss{dest};
              char column;
              int r;
              ss >> column >> r;
              int c = column - 'a';
              r = 8 - r;
              try
              {
                callSetPiece(c, r, piecename, g);
                cout << g;
              }
              catch (string message)
              {
                cout << message << endl;
              }
            }
            else if (set == "-")
            {
              string dest;
              cin >> dest;
              istringstream ss{dest};
              char column;
              int r;
              ss >> column >> r;
              int c = column - 'a';
              r = 8 - r;
              try
              {
                g.removePiece(c, r);
                cout << g;
              }
              catch (string message)
              {
                cout << message << endl;
              }
            }
            else if (set == "=")
            {
              string c;
              cin >> c;
              Colour colour = Colour::NoColour;
              if ((c == "White") || (c == "white"))
                colour = Colour::White;
              else if ((c == "Black") || (c == "black"))
                colour = Colour::Black;
              else
                cout << c << " is not a valid colour!" << endl;
              if (colour == Colour::White)
                tracker = 0;
              if (colour == Colour::Black)
                tracker = 1;
            }
            else if (set == "done")
            {
              if (!g.haswhiteking())
              {
                cout << "White king missing. Adjust the board." << endl;
                cout << g;
              }
              else if (!g.hasblackking())
              {
                cout << "Black king missing. Adjust the board." << endl;
                cout << g;
              }
              else if (g.white_incheck())
              {
                cout << "White in check. Adjust the board." << endl;
                cout << g;
              }
              else if (g.black_incheck())
              {
                cout << "Black in check. Adjust the board." << endl;
                cout << g;
              }
              else
              {
                cout << g;
                game_started = true;
                cout << "setup is done" << endl;
                break;
              }
            }
          }
        }
      }
      else if (cmd == "quit")
      {
        return 0;
      }
    }
  }

  catch (ios::failure &)
  {
  } // Any I/O failure quits
}
