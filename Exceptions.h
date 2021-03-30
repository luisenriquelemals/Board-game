/**
 * Exceptions.h - Header file for the Exception class and all its subclasses.
 * Written by . . . 
 */


#ifndef _EXCEPTIONS_H
#define _EXCEPTIONS_H

#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

class Exception {
	private: 
	    string description;
	public: 
		virtual ~Exception();
		Exception( string s );
    	string getDescription( );
};


class SpaceUnavailable : public Exception {
	public:
		SpaceUnavailable( string s );
};


class InvalidMove : public Exception {
	public:
		InvalidMove( string s );
};

class Collision: public Exception {
	private: 
	    int row;
	    int col;
	    
	public: 
		Collision( string s, int r, int c);
		void getLocation( int & r, int & c);
};

#endif //_EXCEPTIONS_H
