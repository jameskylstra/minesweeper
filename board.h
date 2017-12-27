#ifndef BOARD_H
#define BOARD_H
#include <iostream>
using namespace std;

class Board {
  private:
    const int rows;
    const int cols;
    int flags;
    // Mine / no mine grid
    bool mineGrid[100][100];
    // Flag / no flag grid
    bool flagGrid[100][100];
    // Opened / unopened grid
    bool openGrid[100][100];
  public:
    // Default constructor
    Board () : rows(0), cols(0), flags(0) {}

    // Constructor(s)
    Board (int r, int c) : rows(r), cols(c), flags(0) {}

    // Destructor
    ~Board () {}

    // Mutators
    void setMine(int r, int c) {
	mineGrid[r][c] = true;
    }

    void setNoMine(int r, int c) {
	mineGrid[r][c] = false;
    }

    void setFlag(int r, int c) {
	flagGrid[r][c] = true;
    }

    void setNoFlag(int r, int c) {
	flagGrid[r][c] = false;
    }

    void toggleFlag(int r, int c) {
	if (flagGrid[r][c]) {
	    flagGrid[r][c] = false;
	    flags--;
	} else {
	    flagGrid[r][c] = true;
	    flags++;
	}
    }

    void setOpen(int r, int c) {
	openGrid[r][c] = true;
    }

    void setClosed(int r, int c) {
	openGrid[r][c] = false;
    }

    void layMine();

    void openAll () {
	for (int i = 0; i < rows; i++)
	    for (int j = 0; j < cols; j++)
		openGrid[i][j] = true;
    }

    // Accessors
    bool getMine(int r, int c) const { return mineGrid[r][c]; }
    bool getFlag(int r, int c) const { return flagGrid[r][c]; }
    bool getOpen(int r, int c) const { return openGrid[r][c]; }
    int countFlags() const { return flags; }
    int getNumber(int r, int c) const; // returns number of proximate mines

};

#endif // BOARD_H
