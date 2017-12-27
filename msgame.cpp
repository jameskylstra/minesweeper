#include "msgame.h"
#include <cstdlib>
#include <ctime>
using namespace std;

void MSGame::play () {
    setBoard();
    while (!hasWon && !hasLost)
    {
	takeTurn();
	checkForWin();
    }
    if (hasWon) winGame();
    else loseGame();
}

void MSGame::setBoard () {
    srand((unsigned)time(0));
    // set flag grid to blank
    for (int i = 0; i < rows; i++) {
	for (int j = 0; j < cols; j++) {
	    b->setNoFlag(i, j);
	}
    }
    // lay mines mines
    for (int i = 0; i < mines; i++) {
	b->layMine();
    }
}

void MSGame::printBoard () {
    // print column numbers
    cout << " ";
    for (int i = 0; i < cols; i++)
	cout << " " << i;
    cout << endl;
    for (int i = 0; i < rows; i++) {
	cout << " ";
	printRowPartition();
	cout << i;
	for (int j = 0; j < cols; j++) {
	    cout << "|";
	    printCell(i, j);
	}
	cout << "|" << endl;
    }
    cout << " ";
    printRowPartition();
}

void MSGame::printRowPartition () {
    for (int i = 0; i < 2 * cols + 1; i++)
	cout << "-";
    cout << endl;
}

void MSGame::printCell (int r, int c) {
    if (b->getOpen(r, c) && b->getMine(r, c))
	cout << "*";
    else if (b->getOpen(r, c))
	cout << b->getNumber(r, c);
    else if (b->getFlag(r, c))
	cout << "/";
    else
	cout << " ";
}

void MSGame::takeTurn () {
    printBoard();
    int flagOrOpen = 0;
    cout << mines - b->countFlags() << " mines left." << endl;
    cout << "Flag(1) or Open(2): ";
    cin >> flagOrOpen;
    if (flagOrOpen != 1 && flagOrOpen != 2) {
	cout << "Invalid entry. Must be 1 or 2." << endl;
	takeTurn();
    }
    int r = 0;
    int c = 0;
    cout << "row, col: ";
    cin >> r >> c;
    if (r < 0 || r >= rows) {
	cout << "Invalid entry. Row must be between 0 and " << rows - 1
	    << ". Col must be between 0 and " << cols - 1 << endl;
	takeTurn();
    }
    if (b->getOpen(r, c)) {
	cout << "Invalid entry. Square already open." << endl;
	takeTurn();
    }
    makeMove(flagOrOpen, r, c);
}

void MSGame::makeMove (int flagOrOpen, int r, int c) {
    if (flagOrOpen == 1) // flag
	b->toggleFlag(r, c);
    else { // open
	b->setOpen(r, c);
	if (b->getMine(r, c)) {
	    hasLost = true;
	    return;
	}
	if (b->getNumber(r, c) == 0) {
	    bloom(r, c);
	}
    }
}

void MSGame::bloom (int r, int c) {
    //open each square around r, c
    //if any of those squares has a number of 0, bloom from that square
    int neighbors[8][2] = {
	{ r - 1, c - 1 },
	{ r - 1, c },
	{ r - 1, c + 1 },
	{ r, c - 1 },
	{ r, c + 1 },
	{ r + 1, c - 1 },
	{ r + 1, c },
	{ r + 1, c + 1}
    };
    int nr, nc;
    for (int i = 0; i < 8; i++) {
	nr = neighbors[i][0];
	nc = neighbors[i][1];
	if (nr < 0 || nr >= rows || nc < 0 || nc >= cols || b->getOpen(nr, nc))
	    continue;
	b->setOpen(nr, nc);
	if (b->getNumber(nr, nc) == 0) bloom(nr, nc);
    }
}


void MSGame::checkForWin () {
    // There's a win if the number of flags is 
    // equal to the number of mines and every
    // non-flagged square is empty
    if (b->countFlags() != mines) return;
    for (int i = 0; i < rows; i++) {
	for (int j = 0; j < cols; j++) {
	    if (b->getMine(i, j) && !b->getFlag(i, j)) return;
	}
    }
    hasWon = true;
}

void MSGame::winGame () {
    b->openAll();
    printBoard();
    cout << "Congratulations!" << endl;
}

void MSGame::loseGame () {
    b->openAll();
    printBoard();
    cout << "Ouch! You lost :(" << endl;
}
 











