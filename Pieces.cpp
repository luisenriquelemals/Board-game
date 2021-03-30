/**
 * Name: Luis Lema Date: 6/10/2020
 * project: game
 */

#include "Pieces.h"
#include "Board.h"
#include "Exceptions.h"

using namespace std;


// First the Piece class methods

Piece::~Piece( ) {

} // Destructor

void Piece::move( int r, int c ) {
	return; // Do-nothing method
}

bool Piece::isBarrier() {
	return false; // for most Pieces
}

bool Piece::isSpace() {
	return false; // for most Pieces
}

// Then the Player class methods
char Player::display( ) {
	return 'A';
}

/// location on the moment
void Player::move( int r, int c ){ // Reads in keyboard input
	bool done  = false;
	char ch;


	while (!done) {
			done = true;

			cout << "Enter Move: ";
			cin >> ch;

			switch (ch){
				case 'q':
				case 'Q':
					c--;
					r++;
				break;
				
				case 'w':
				case 'W':
					r--;
				break;

				case 'e':
				case 'E':
					c++;
					r--;
				break;

				case 'a':
				case 'A':
					c--;
				break;

				case 'd':
				case 'D':
					c++;
				break;

				case 'z':
				case 'Z':
					c--;
					r++;
				break;

				case 'x':
				case 'X':
					r++;
				break;

				case 'c':
				case 'C':
					c++;
					r++;
				break;

				case 's':
				case 'S':
				  return; // we don neeed move to, we return
				break;

				default:
					// for some bad options
					done = false;
				break;
			}// end switch

	}// end while

		// Now We can move the player
		try{
			Board::getBoard()->moveMeTo(r,c);
		}
		catch( SpaceUnavailable e){
			cerr << "You can't go there: " << e.getDescription() << '\n';
		}
		

		return;
}

// Then the Robot class methods

int Robot::nRobots = 0;

Robot::Robot () {
		nRobots++;
}

Robot::~Robot () {
		nRobots--;
}

int Robot::getRobots() {
	return nRobots;
}

char Robot::display( ) {
	return 'R';
}

void Robot::move( int r, int c){  // Basic AI to chase the player

	int pRow, pCol; // player row and col
	Board::getBoard()->getPlayerPosition(pRow, pCol);

	if (pRow > r) {
		r++;
	}else if(pRow < r){
		r--;
	}

	if(pCol > c){
		c++;
	}else if (pCol < c){
		c--;
	}
	
	try{
		Board::getBoard()->moveMeTo(r,c);

	}catch( SpaceUnavailable e){
			cerr << "Robot hit a Wall: " << e.getDescription() << '\n';

	}catch( InvalidMove e){
			cerr << "Robot took a flying leap: " << e.getDescription() << '\n';
	}
		
	return;
}


// The Mine class method

char Mine::display( ) {
	return '*';
}

// The Brick class methods

char Brick::display( ) {
	return '#';
}

bool Brick::isBarrier(){
	return true;
}

// The Space class methods

char Space::display( ) {
	return ' ';
}

bool Space::isSpace() { // Space needs to override this one
	return true;
}


