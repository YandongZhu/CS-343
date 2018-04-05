//--------------------------------------------------------------------------------------------------------------------
// Inplementation for the class printer 
//--------------------------------------------------------------------------------------------------------------------
#include <iostream>

#include "q2printer.h"

using namespace std;


//--------------------------------------------------------------------------------------------------------------------
// Printer::Printer: Constructor for class printer
//--------------------------------------------------------------------------------------------------------------------
Printer::Printer( unsigned int voters ): voters( voters ) {
	voterState = new VoterState[voters];

	for ( unsigned int i = 0; i < voters; ++i ) {	// print for all voter num at the beginning
		if ( i ) {												// print the interval between voters
			cout << "\t";
		}	// if
		cout << "V" << i;
	}	// for

	cout << endl;

	for ( unsigned int i = 0; i < voters; ++i ) {	// print the seperation between name and detail
		if ( i ) {												// print the interval between voters
			cout << " ";
		}	// if
		cout << "*******";
	}	// for

	cout << endl;
	for ( unsigned int i = 0; i < voters; ++i ) {	// init the value for field
		voterState[i].data = false;
		voterState[i].blockNum = 0;
	}	// for

}	// Printer::Printer


//--------------------------------------------------------------------------------------------------------------------
// Printer::~Printer: Destructor for class printer
//--------------------------------------------------------------------------------------------------------------------
Printer::~Printer() {
	flush();
	cout << "***************** " << endl << "All tours started" << endl;
	delete [] voterState;
}	// Printer::~Printer


//--------------------------------------------------------------------------------------------------------------------
// void Printer::printBallot: print the infomation when pass in a TallyVotes::Ballot structure
//--------------------------------------------------------------------------------------------------------------------
void Printer::printBallot( TallyVotes::Ballot curBallot ) {
	cout << " " << curBallot.picture << "," << curBallot.statue << "," << curBallot.giftshop;
}	// Printer::printBallot


//--------------------------------------------------------------------------------------------------------------------
// void Printer::flush: when a voter reaches the next statue, print the current statue 
//						immediately and start storing the infomation for the next statue
//--------------------------------------------------------------------------------------------------------------------
void Printer::flush () {
	for ( unsigned int i = 0; i < voters; ++i ) {	// print current states
		if ( i ) {												// print the tabs
			cout << "\t";
		}	// if

		if ( voterState[i].data ) {						// if there is data in the voters
			cout << ( char ) voterState[i].curState;

			if ( voterState[i].curState == Voter::Vote ) {
				printBallot( voterState[i].voteResult ); 
			} else if ( voterState[i].curState == Voter::Block || voterState[i].curState == Voter::Unblock ) {
				cout << " " << voterState[i].blockNum;
			} else if ( voterState[i].curState == Voter::Finished ) {
				cout << " " << ( char )voterState[i].destination;
			}
		}	// if
		voterState[i].data = false;
	}	// for
	cout << endl;
}	// Printer::flush


//--------------------------------------------------------------------------------------------------------------------
// void Printer::print: the basic type for print which only record the voter's current statue
//--------------------------------------------------------------------------------------------------------------------
void Printer::print ( unsigned int id, Voter::States state ) {
	if ( voterState[id].data ) {					// if the current voter already has data
		flush();
	}	// if

	voterState[id].curState = state; 
	voterState[id].data = true;
}	// Printer::print


//--------------------------------------------------------------------------------------------------------------------
// void Printer::print: the basic type for print which when voter determine where should go( TallyVotes::Tour )
//--------------------------------------------------------------------------------------------------------------------
void Printer::print ( unsigned int id, Voter::States state, TallyVotes::Tour tour ) {
	if ( voterState[id].data ) {					// if the current voter already has data
		flush();
	}	// if

	voterState[id].curState = state; 
	voterState[id].destination = tour;
	voterState[id].data = true;
}	// Printer::print

//--------------------------------------------------------------------------------------------------------------------
// void Printer::print: the basic type for print which when voter determine there ballot
//--------------------------------------------------------------------------------------------------------------------
void Printer::print ( unsigned int id, Voter::States state, TallyVotes::Ballot ballot ) {
	if ( voterState[id].data ) {					// if the current voter already has data
		flush();
	}	// if

	voterState[id].curState = state; 
	voterState[id].voteResult = ballot;
	voterState[id].data = true;
}	// Printer::print


//--------------------------------------------------------------------------------------------------------------------
// void Printer::print: the basic type for print which when voter need to know how many voters does he blocked
//--------------------------------------------------------------------------------------------------------------------
void Printer::print ( unsigned int id, Voter::States state, unsigned int numBlocked ) {
	if ( voterState[id].data ) {					// if the current voter already has data
		flush();
	}	// if

	voterState[id].curState = state; 
	voterState[id].blockNum = numBlocked;
	voterState[id].data = true;
}	// Printer::print









