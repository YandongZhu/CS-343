#include <iostream>
//--------------------------------------------------------------------------------------------------------------------
// Implement for the tally vote using semaphore
//--------------------------------------------------------------------------------------------------------------------
#include "q2voter.h"
#include "q2printer.h"

using namespace std;

extern MPRNG mprng;


//--------------------------------------------------------------------------------------------------------------------
// Voter::Voter Constructor for class voter
//--------------------------------------------------------------------------------------------------------------------
Voter::Voter ( 
	unsigned int id, 
	unsigned int nvotes, 
	TallyVotes & voteTallier, 
	Printer & printer ): 
id(id), 
nvotes(nvotes), 
voteTallier(voteTallier), 
printer(printer){} // Voter::Voter


//--------------------------------------------------------------------------------------------------------------------
// TallyVotes::Ballot Voter::cast(): determine a ballot form randomly
//--------------------------------------------------------------------------------------------------------------------
TallyVotes::Ballot Voter::cast() {        // cast 3-way vote
  // O(1) random selection of 3 items without replacement using divide and conquer.
  static unsigned int voting[3][2][2] = { { {2,1}, {1,2} }, { {0,2}, {2,0} }, { {0,1}, {1,0} } };
  unsigned int picture = mprng( 2 ), statue = mprng( 1 );
  return (TallyVotes::Ballot){ picture, voting[picture][statue][0], voting[picture][statue][1] };
}	// TallyVotes::Ballot Voter::cast

//--------------------------------------------------------------------------------------------------------------------
// void Voter::main: the flow that a voter will be done start from vote, tour and finish
//--------------------------------------------------------------------------------------------------------------------
void Voter::main() {
	yield( mprng( 19 ) );
	for ( unsigned int i = 0; i < nvotes; ++i ) {
		// start 
		printer.print( id, Start );

		yield( mprng( 4 ) );

		// vote
		TallyVotes::Ballot voteResult = cast();
		//printer.print( id, Vote, voteResult );
		TallyVotes::Tour tourResult = voteTallier.vote( id, voteResult );

		if ( tourResult == TallyVotes::Failed ) {		// if the return result is failed, which means there has not enough voter to form a group
			printer.print( id, Failed );
			break;
		}	// if 
		yield( mprng( 4 ) );

		// finish
		printer.print( id, Finished, tourResult );
	}	// for
	voteTallier.done();
}	// void Voter::main
