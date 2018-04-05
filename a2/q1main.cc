//--------------------------------------------------------------------------------------------------------------------
// The entry for the program
//--------------------------------------------------------------------------------------------------------------------


#include <iostream>
#include <fstream>
#include <stack>

#include "q1reader.h"
#include "q1writer.h"
#include "q1hexFilter.h"
#include "q1spaceFilter.h"
#include "q1pushFilter.h"

using namespace std;

int main(int argc, char const *argv[])
{
	stack<char> filter;		// stack for storing the flags
	istream * in = &cin;
	ostream * out = &cout;
	ifstream infile;
	ofstream outfile;

	try {
		int i = 2;
		for ( ; i <= argc; ++i ){
			if ( argv[i-1][0] != '-' ) {	// if there is not a flag
				break;	
			} // if
			filter.push(argv[i-1][1]);					// push all the filter operation into the stack
		}	// for
		if ( i <= argc ) {	// try to open the input file if there has one from the cmd line
			try {
				infile.open( argv[i-1] );
				in = &infile;
				i++;
			} catch ( uFile::Failure ) {
				cerr << "Error! count not open input file \"" << argv[i-1] << "\"" << endl;
				throw 1;
			} // try
		}
		if ( i == argc ) {	// try to open the output file if there has.
			try {
				outfile.open( argv[i-1] );
				out = &outfile;
			} catch ( uFile::Failure ) {
				cerr << "Error! count not open output file \"" << argv[i-1] << "\"" << endl;
				throw 1;
			} // try
		} else if ( i < argc ) {		// if there is still some input from the cmd line
			throw 1;
		}	// if
	} catch ( ... ) {
		cerr << "Usage: " << argv[0] << " [ -filter-options ... ] [ infile [outfile] ]" << endl;
		exit ( 1 );
	}	// try

	Filter * preFilter = new Writer( out );
	Filter * newFilter;
	while ( filter.size() != 0 ) {	// poping the filter option from the stack
		char top = filter.top();
		switch ( top ) {
			case 'h': {
				newFilter = new HexFilter( preFilter );
				break;
			}
			case 'w': {
				newFilter = new SpaceFilter( preFilter );
				break;
			}
			case 'p': {
				newFilter = new PushFilter( preFilter );
				break;
			}	
			default: {
				cerr << "unknown filter -" << top << endl;
				exit(1);
			}
		}
		filter.pop();
		preFilter = newFilter;
	}

	Reader * r = new Reader( preFilter, in );

	try {
		r->put(0);
	}	catch ( ... ){
		delete r;
	}	// try

	return 0;
}	// main