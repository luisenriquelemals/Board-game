/**
 * Name: Luis Lema Date: 6/10/2020
 * project: game
 */


#ifndef _PIECES_H
#define _PIECES_H


// First the Piece class itself

class Piece {
	public:  
		virtual ~Piece( );
		virtual char display( ) = 0;
    	virtual void move( int r, int c );
    	virtual bool isBarrier( );
    	virtual bool isSpace( );
};

// Then all the subclasses

class Player: public Piece {
		virtual char display( );
    	virtual void move( int r, int c );
};


class Robot: public Piece {
	private:
		static int nRobots;
	public:
		Robot();
		~Robot();
		virtual char display( );
		virtual void move( int r, int c );
		static int getRobots();
};


class Mine: public Piece {
		virtual char display( );
		
};

class Brick: public Piece {
		virtual char display( );
    	virtual bool isBarrier( );
};

class Space: public Piece {
		virtual char display( );
    	virtual bool isSpace( );
};

#endif //_PIECES_H
