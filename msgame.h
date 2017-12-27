#ifndef MSGAME_H
#define MSGAME_H
#include <iostream>
#include "board.h"
using namespace std;

class MSGame {
  private:
      int rows;
      int cols;
      int mines;
      bool hasWon;
      bool hasLost;
      Board* b;
      void createBoard (int r, int c) {
	  if (b != NULL) delete b;
	  b = new Board(r, c);
      }
      void setBoard ();
      void printBoard ();
      void printCell (int r, int c);
      void printRowPartition ();
      void takeTurn ();
      void makeMove (int flagOrOpen, int r, int c);
      void checkForWin ();
      void winGame ();
      void loseGame ();
      void playAgain ();
      void bloom (int r, int c);
  public:
    // Default constructor
    MSGame () {
	b = NULL;
	rows = 0;
	cols = 0;
	mines = 0;
	hasWon = false;
	hasLost = false;
    }

    // Constructor(s)
    MSGame (int r, int c, int m) {
	b = new Board(r, c);
	rows = r;
	cols = c;
	mines = m;
	hasWon = false;
	hasLost = false;
    }

    // Destructor
    ~MSGame () {
	delete b;
    }

    // Accessors
    Board* getBoard () { return b; }

    // Other functions
    void getDimensions () {
	cout << "Number of rows: ";
	cin >> rows;
	cout << "Number of columns: ";
	cin >> cols;
	cout << "Number of mines: ";
	cin >> mines;
	b = new Board(rows, cols);
    }

    void reset () {
	hasWon = false;
	hasLost = false;
    }

    void play ();
};

#endif // MSGAME_H
