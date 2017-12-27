#include "board.h"

int Board::getNumber (int r, int c) const {
    int mines = 0;
    if (r > 0) {
	if (mineGrid[r - 1][c]) mines++;
	if (c > 0 && mineGrid[r - 1][c - 1]) mines++;
	if (c < cols - 1 && mineGrid[r - 1][c + 1]) mines++;
    }
    if (r < rows - 1) {
	if (mineGrid[r + 1][c]) mines++;
	if (c > 0 && mineGrid[r + 1][c - 1]) mines++;
	if (c < cols - 1 && mineGrid[r + 1][c + 1]) mines++;
    }
    if (true) {
	if (c > 0 && mineGrid[r][c - 1]) mines++;
	if (c < cols - 1 && mineGrid[r][c + 1]) mines++;
    }
    return mines;
}

void Board::layMine () {
    // assumes rand is already seeded
    bool hasLaid = false;
    int r;
    int c;
    while (!hasLaid) {
	r = rand() % rows;
	c = rand() % cols;
	if (!mineGrid[r][c]) {
	    mineGrid[r][c] = true;
	    hasLaid = true;
	}
    }
}
