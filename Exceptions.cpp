/**
 * Exceptions.cp - Source code file for the Exception class and all its subclasses.
 * Written by . . . 
 */

#include "Exceptions.h"

// First the methods for Exception itself

Exception::Exception( string s ) {
            description = s;
}

// virtual destructor for Polymorphisim
Exception::~Exception() {}

string Exception::getDescription( ) {
                return description;
}

// Then the subclasses

InvalidMove::InvalidMove( string s ) : Exception( s ) {}

SpaceUnavailable::SpaceUnavailable( string s ) : Exception( s ) {}

Collision::Collision( string s, int r, int c) : Exception( s ), row(r), col(c) {}

 void Collision::getLocation( int & r, int & c ) {
        r = row;
        c = col;
 }

