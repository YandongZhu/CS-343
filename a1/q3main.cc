#include <iostream>
#include <fstream>
#include <string>
#include "q3money.h"

//--------------------------------------------------------------------------------------------------------------------
// Creates the entry for the money program
//--------------------------------------------------------------------------------------------------------------------

using namespace std;

//--------------------------------------------------------------------------------------------------------------------
// pass the next character to continue the coroutine to check it is still a valid amount form or not
//--------------------------------------------------------------------------------------------------------------------
void Money::next( char c ) {
	ch = c;                         // communication input
	resume();                       // activate
}	// Money::next

//--------------------------------------------------------------------------------------------------------------------
// the program entry point
//--------------------------------------------------------------------------------------------------------------------
int main(int argc, char const *argv[]) {
	Money money;																// init the _Coroutain money
	ifstream infile;														// init the file stream
	string line;										
	
	bool inputType = false;											// indicating reading files or enter by input
	try {
		switch ( argc ) {													// process command-line arguments
			case 2: {
				try {
					infile.open( argv[1] );
					inputType = true;										// if success open the file
					break;
				} // try 
				catch ( uFile::Failure ) {						// if fail to open the file
					cout << "Error! Could not open input file \"" << argv[1] << "\"" << endl;
					exit ( 1 ); 
				}
			}
			case 1: break;							
			default: throw 1;
		}	// switch
	} catch ( ... ) {
		cout << "Usage: " << argv[0] << " [infile-file] " << endl;
    exit( 1 );
	}	// try

	for ( ;; ) {
		if ( inputType ) {												// get line from file or input
			getline( infile, line );	
		}	else {
			getline( cin, line );
		}	// if
		int length = line.length();
		
		if ( inputType && infile.fail() ) break; 	// eof for file then break
		if ( !inputType && cin.eof() ) break;			// eof for input
		cout << "'" << line << "' : ";

		if (length == 0) { 												// if there is not input in the line
			cout << "Warning! Blank line." << endl;
		} else {
			for (int i = 0; i < length; ++i) {
				money.next(line[i]);								
			}	// for
			money.next(0);													// sending the character indicating ending line
		}	// if
	}	// for
	return 0;
}	// int main