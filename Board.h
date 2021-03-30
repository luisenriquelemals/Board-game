/**
 * Name: Luis Lema Date: 6/10/2020
 * project: game
 */

#ifndef _BOARD_H
#define _BOARD_H

#include <cstdlib>
#include <iostream>
#include <string>
#include "Pieces.h"

using namespace std;


#define NROWS 10
#define NCOLS 20

class Board {
	private: 
	    int nRows;
	    int nCols;
	    int row;
	    int col;
	    int playerRow;
	    int playerCol;
	    Piece * pieces[ NROWS ][ NCOLS ];
	    int lastTurnPlayed[ NROWS ][ NCOLS ];
	    int currentTurn;
	    static Board * theBoard;
		Board( ); // PRIVATE constructor, for Singleton pattern
	    ~Board();
	    
	public: 
		
		static Board * getBoard( );
		static void releasedBoard();
		void display( );
		void play( );
		void moveMeTo( int newRow,  int newCol );
		void getPlayerPosition( int & row, int & col );
};

#endif //_BOARD_H
