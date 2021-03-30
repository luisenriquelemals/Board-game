/**
 * Name: Luis Lema Date: 6/10/2020
 * project: game
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

#include "Pieces.h"
#include "Exceptions.h"
#include "Board.h"

int main( int argc, char ** argv ) {

	// Initliaze the random number generator
	srand( time(NULL) );
	
	Board * myBoard;
	myBoard = Board::getBoard( );
	cout << "                            Welcome to THE GAME      \n "
		 <<	"Instructions: The borad going to start with a random number of nemies robots(R) \n"
		 << "also some obstacles like bricks(#), if two robots collides a mine(*) going to be created \n"
		 << "You as the Player(A) can move up(W), down(X), left(A), right(D), diagonals(Q, E, Z, C) and stand still(S).\n"
		 << "Q  W  E\n"
		 << " A  S  D\n"
		 << "  Z  X  C\n"  ;

	myBoard->play();

	// call the destructor
	//Board::releasedBoard();
	return 0;
	
} // main
