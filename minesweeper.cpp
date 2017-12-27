#include <iostream>
#include <string>
#include "msgame.h"
using namespace std;

void getArg(int& output, string flag, int def, int argc, char* argv[]); 

int main (int argc, char* argv[]) {
    int rows, cols, mines;
    getArg(rows, "-r", 5, argc, argv);
    getArg(cols, "-c", 5, argc, argv);
    getArg(mines, "-m", 3, argc, argv);
    string playAgainAnswer;
    MSGame msg(rows, cols, mines);
    msg.play();
    do
    {
	cout << "Do you want to play again? (y/n): ";
	cin >> playAgainAnswer;
    } while (playAgainAnswer != "y" && playAgainAnswer != "n");
    while (playAgainAnswer != "n")
    {
	msg.reset();
    	msg.getDimensions();
    	msg.play();
    	do
	{
	    cout << "Do you want to play again? (y/n): ";
	    cin >> playAgainAnswer;
	} while (playAgainAnswer != "y" && playAgainAnswer != "n");
    }
}

void getArg(int& output, string flag, int def, int argc, char* argv[]) {
    for (int i = 0; i < argc - 1; i++) {
	if (argv[i] == flag) {
	    output = stoi(argv[i + 1]);
	    return;
	}
    }
    output = def;
}
