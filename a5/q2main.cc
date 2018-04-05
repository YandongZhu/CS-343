//--------------------------------------------------------------------------------------------------------------------
// the entry for the program
//--------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include <unistd.h>                     // access: getpid

#include "MPRNG.h"
#include "q2voter.h"
#include "q2printer.h"
#include "q2tallyVotes.h"

using namespace std;

MPRNG mprng;


int main(int argc, char const *argv[]) {
	unsigned int voters = 6;
	unsigned int group = 3;
	unsigned int votes = 1;
	unsigned int seed = getpid();

	// command line argument handler
	try {
		switch ( argc ) {
			case 5: seed = stoi( argv[4] ); if ( seed < 1 ) throw 1; 
			case 4: votes = stoi( argv[3] ); if ( votes < 1 ) throw 1;
			case 3: group = stoi( argv[2] ); if ( group < 1 ) throw 1;
			case 2: voters = stoi( argv[1] ); if ( voters < 1 ) throw 1;
			case 1: break;
			default: throw 1;
		}
	} catch ( ... ) {
		cout << "Usage: " << argv[0] << " vote [ voters | ’x’ [ group | ’x’ [ votes | ’x’ [ seed | ’x’ ] ] ]" << endl;
		exit( 1 );
	}	// try

	mprng.set_seed( seed );

	Printer printer( voters );

	TallyVotes task( voters, group, printer );

	Voter *voterList[voters];
	for ( unsigned int i = 0; i < voters; ++i ) {
		voterList[i] = new Voter( i, votes, task, printer );
	}	// for
	for ( unsigned int i = 0; i < voters; ++i ) {
		delete voterList[i];
	}	// for 
	return 0;
}