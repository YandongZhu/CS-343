//--------------------------------------------------------------------------------------------------------------------
// Implement function for hex filter
//--------------------------------------------------------------------------------------------------------------------


#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>					// setw() setfill()
#include "q1hexFilter.h"

using namespace std;

HexFilter::HexFilter( Filter * f ) {
	next = f;
}	// HexFilter::HexFilter

void HexFilter::charToHex() {
	int chNum = ch;																	// convert the char into int
	stringstream ss;
	ss << setw(2) << setfill('0') << hex << chNum;	// set the whitespace with 0 if there has not enough character
	string res = ( ss.str() );
	next->put( res[0] );														// push two char into nex filter
	next->put( res[1] );
}	// HexFilter::charToHex()

void HexFilter::groupFour() {
	for (int i = 0; i < 2; ++i) {										// for two characters input to generate 4 characters
		charToHex();
		suspend();																		// waiting for the next character

		try {
		_Enable {};																		// enable the Eof expection
		} catch ( Eof & ) {
			_Resume Eof() _At *next;										// pass to next filter
		}	// try
	}	// for
}	// HexFilter::groupFour()

void HexFilter::groupEight() {	
	for (int i = 0; i < 2; ++i) {									// for two sets of 4 to generate 8 characters
		groupFour();
		next->put( ' ' );														// put a space between the two sets
	}	// for
}	// HexFilter::groupEight

void HexFilter::main() {
	try {
		_Enable {};
	} catch ( Eof & ) {														// if we meet the Eof at the beginning
		_Resume Eof() _At *next;
	}	// try
	for ( ;; ) {																
		for (int i = 0; i < 3; ++i) {								// for each line the first 3 set is the same
			groupEight();
			next->put( ' ' );													// put two spaces after set of 8
			next->put( ' ' );
		}	// for

		groupFour();																// the last one is different with only newline char
		next->put( ' ' );
		groupFour();
		next->put( '\n' );
	}	// for			
}	// HexFilter::main