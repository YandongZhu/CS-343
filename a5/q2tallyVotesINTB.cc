#include <iostream>

#include "q2tallyVotes.h"
#include "q2printer.h"
#include "MPRNG.h"

using namespace std;

extern MPRNG mprng;

//--------------------------------------------------------------------------------------------------------------------
// TallyVotes::TallyVotes: Constructor for class tallyvotes
//--------------------------------------------------------------------------------------------------------------------
TallyVotes::TallyVotes ( 
	unsigned int voters, 
	unsigned int group, 
	Printer & printer): voters(voters), group(group), printer(printer) {
	currentVoters = 0;
	finishVoters = voters;
	pictureWeight = 0;
	statueWeight = 0;
	giftShopWeight = 0;
	groupFull = false;
}	// TallyVotes::TallyVotes

void TallyVotes::wait() {
    bench.wait();                            // wait until signalled
    while ( rand() % 2 == 0 ) {              // multiple bargers allowed
        _Accept( vote ) {                    // accept barging callers
        } _Else {                            // do not wait if no callers
        } // _Accept
    } // while
}

void TallyVotes::signalAll() {               // also useful
    while ( ! bench.empty() ) bench.signal();// drain the condition
}

//--------------------------------------------------------------------------------------------------------------------
// TallyVotes::Tour TallyVotes::vote: when voter determine there ballot call this function to vote
//--------------------------------------------------------------------------------------------------------------------
TallyVotes::Tour TallyVotes::vote ( unsigned int id, Ballot ballot ) {

	if ( finishVoters < group ) {					// check if there is not enough voter at the end
		return Failed;	
	}	// if

	if ( groupFull ) {	// if the current group if full, which not allow barger to interupt
		printer.print( id, Voter::Barging );
		wait();
	}	// if
	
	currentVoters++;
	printer.print( id, Voter::Vote, ballot ); 

	pictureWeight += ballot.picture;
	statueWeight += ballot.statue;
	giftShopWeight += ballot.giftshop;

	if ( currentVoters < group ) {
		printer.print( id, Voter::Block, currentVoters );
		wait();

		currentVoters--;
		printer.print( id, Voter::Unblock, currentVoters );
		if ( currentVoters == 0 ) {	// if the current voter is the last voter
			// reset the value
			giftShopWeight = 0;
			statueWeight = 0;
			pictureWeight = 0;
			groupFull = false;
			signalAll();
		}	// if
	} else {
		groupFull = true;
		printer.print( id, Voter::Complete );

		// compare by the option that voter select and choose the most one
		if ( giftShopWeight > statueWeight && giftShopWeight > pictureWeight ) {
			destination = GiftShop;
		} else if ( statueWeight > pictureWeight ) {
			destination = Statue;
		} else {
			destination = Picture;
		}	// if
		currentVoters--;
		signalAll();
	}	// if

	if ( finishVoters < group ) {					// check if there is not enough voter at the end
		return Failed;	
	}	// if

	return destination;
}


//--------------------------------------------------------------------------------------------------------------------
// void TallyVotes::done: when voter finish their tour call done to make a record
//--------------------------------------------------------------------------------------------------------------------
void TallyVotes::done() {
	finishVoters--;
	if ( finishVoters < group ) {	// if there is not enough voter
		signalAll();
	}	// if 
}	// void TallyVotes::done
