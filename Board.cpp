/**
 * Name: Luis Lema Date: 6/10/2020
 * project: game
 */

#include "Board.h"
#include "Exceptions.h"
#include <typeinfo>

#define MIN(a,b) (((a)< (b)? (a) : (b) ))

Board * Board::theBoard = NULL;


Board::Board( ) : nRows(NROWS), nCols(NCOLS), currentTurn(1) {

    // Initiliaze the whole table
    for (int r = 0; r < nRows; r++){
        for ( int c = 0; c < nCols; c++){
            pieces[r][c] = new Space();
            lastTurnPlayed[r][c] = 0;
        }     
    }
    
    // generate some random robots and bricks 
    int nRobots = MIN(nCols, 2 + rand() %10); // generate between  2 and 11
    int nMines =  MIN(nCols, 2 + rand() %10); // generate between  2 and 11
    int nBricks =  MIN(nCols, 2 + rand() %10); // generate  between  2 and 11

    if (nRows < 4) {
        cerr << "Not Enough rows! I can't play on a board small\n" ;
        exit(0);
    }

    // player on a row[0]
    delete pieces[0][0];
    pieces[0][0] = new Player();

    // robots on row 1
    for (int i = 0; i < nRobots; i++){
        delete pieces[1][i];
        pieces[1][i] = new Robot();
    }

    // new Mines on row 2
    for (int i = 0; i < nMines; i++){
        delete pieces[2][i];
        pieces[2][i] = new Mine();
    }

     // new bricks on row 3
    for (int i = 0; i < nBricks; i++){
        delete pieces[3][i];
        pieces[3][i] = new Brick();
    }
    
    int randRow, randCol;
    Piece * temp;

    for (int r = 0; r < nRows ; r++){
        for (int c = 0; c < nCols ; c++){
            if( r + c <= 0) continue;
            randRow = rand() % nRows;
            randCol = rand() % nCols;
            if( randRow + randCol <= 0)
                continue;//  we skip player
            //swap this Piece with randomly chosen piece
            temp = pieces [r][c];
            pieces [r][c] = pieces [randRow][randCol];
            pieces[randRow][randCol] = temp;
            
        } 
    }
    
    //And finally scramble the player
    playerRow = randRow = rand() % nRows;
    playerCol = randCol = rand() % nCols;
    temp = pieces[0][0];
    pieces [0][0] = pieces[randRow][randCol];
    pieces [randRow][randCol] = temp;   

}


Board::~Board( ) {

	for (int i = 0; i < nRows ; i++){
		for (int j = 0; j < nCols; j++){
			delete pieces[i][j] ;
		}	
	}

} // Destructor

Board * Board::getBoard( ) {
    if (!theBoard) {
        theBoard = new Board();
    }
    return theBoard;

}



void Board::display( ) {

    cout << "+========================================+ \n" ;
   for (int i = 0; i < nRows; i++){
       cout <<  "|" ;
       for (int j = 0; j < nCols; j++) {
          cout << pieces[i][j]->display()<< "-"; 
       }
      cout << "|\n";
   }

    cout << "+========================================+ \n" ;
  

}



void Board::play( ) {

         while (true) {
                /*Display the Board*/
                display();
                /*Move the Player */
                row = playerRow;
                col = playerCol;
                /*can the player make a valid move*/

                try {
                        pieces[row][col]->move(row, col);
                }catch(Collision & e) {
                    int collRow, collCol;
                    e.getLocation(collRow, collCol);
                    cerr << "Collision caught: "<< e.getDescription() << endl;

                    cout << "Your are into a "
                        << typeid(* pieces[collRow][collCol]).name()
                        << "Your lose!\n\n";
                    return;
                }catch (Exception & e) {
                        cerr << "Exception caught: " << e.getDescription() << endl;
                }

                // update player's lastTurnedPlayed
                lastTurnPlayed [playerRow][ playerCol] = currentTurn;

                // Move robots

                for (int row = 0; row < nRows; row++){
                    for (int col = 0; col < nCols; col++){
                        // do not allow extra turn
                        if (lastTurnPlayed[row][col] >= currentTurn)
                            continue;

                        // Can the piece make a valid move
                        try{
                            pieces[row][col]->move(row, col);

                        }catch(Collision & e) {
                            int collRow, collCol;
                            e.getLocation(collRow, collCol);
                            cerr << "Collision caught: "<< e.getDescription() << endl;

                            // Collison occur on the player
                            if (collRow == playerRow && collCol == playerCol){
                                cout << "A robot got you! you Lose! \n\n";
                                return;
                             }
                            
                            // else robot can run into a mines or another robot
                            // delete new and old location, insert space and mine
                            //  how many robot are left

                            delete pieces[row][col];
                            pieces [row][col] = new Space();

                            delete pieces[collRow][collCol];
                            pieces [collRow][collCol] = new Mine();

                            if (Robot::getRobots() <= 0) {
                                cout << "Congratulations: No More robots left!\n\n";
                                return;
                            }

                        }catch (Exception & e) {
                                cerr << "Exception caught: " << e.getDescription() << endl;
                                // update the lastTurnPlayed flag so they don't get to go again
                                lastTurnPlayed [row][col] = currentTurn;
                        }
                         
                        
                    }// forloop
                }// forlloop
                
            currentTurn++; 
                
        }// end while

}

void Board::moveMeTo( int newRow, int newCol ) {
            
        if (abs(row - newRow) > 1 || abs(col - newCol) > 1)
            throw InvalidMove("New Position  too far from old position");

        // chewck for bound and negative values
        if(newRow < 0) throw SpaceUnavailable("Negative Row");
        if(newRow >= nRows)throw SpaceUnavailable("Row Exceeds bounds");
        if(newCol < 0) throw SpaceUnavailable("Negative Column");
        if(newCol >= nCols)throw SpaceUnavailable("Column Exceeds bounds");

        // is there on inmovable barrier in the way? if so, i cannot move you
        if(pieces [newRow][newCol]->isBarrier())
            throw SpaceUnavailable("Barrier Encountered!") ;

        //if the destinartination is not space or a barrier
        if(!pieces[newRow][newCol]->isSpace())
            throw Collision("Collision encountered", newRow, newCol);

        //the destination is valid
        Piece * temp = pieces[row][col];
        pieces[row][col] = pieces[newRow][newCol];
        pieces [newRow][newCol] = temp;

        // update the last turned played
        lastTurnPlayed[newRow][ newCol] == currentTurn;

        if (row == playerRow && col == playerCol) {
            playerRow = newRow;
            playerCol = newCol;
        }

        return;
}

/*getting the location of the player*/
void Board::getPlayerPosition( int & row, int & col ) {

    row = playerRow;
    col = playerCol;

    return;
}// end of getPlayerPosition

