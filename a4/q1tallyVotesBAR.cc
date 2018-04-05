//--------------------------------------------------------------------------------------------------------------------
// Implement for the tally vote using barrier
//--------------------------------------------------------------------------------------------------------------------

#include <iostream>
#include <uBarrier.h>

#include "q1tallyVotes.h"
#include "q1printer.h"
#include "MPRNG.h"

using namespace std;

extern MPRNG mprng;


//--------------------------------------------------------------------------------------------------------------------
// TallyVotes::TallyVotes: Constructor for class tallyvotes
//--------------------------------------------------------------------------------------------------------------------
TallyVotes::TallyVotes ( 
	unsigned int voters, 
	unsigned int group, 
	Printer & printer): uBarrier(group), voters(voters), group(group), printer(printer) {
	currentVoters = 0;
	finishVoters = voters;
	pictureWeight = 0;
	statueWeight = 0;
	giftShopWeight = 0;
}	// TallyVotes::TallyVotes


//--------------------------------------------------------------------------------------------------------------------
// TallyVotes::~TallyVotes: Destructor for class tallyvotes
//--------------------------------------------------------------------------------------------------------------------
TallyVotes::~TallyVotes() {
}	// TallyVotes::~TallyVotes


//--------------------------------------------------------------------------------------------------------------------
// TallyVotes::Tour TallyVotes::vote: when voter determine there ballot call this function to vote
//--------------------------------------------------------------------------------------------------------------------
TallyVotes::Tour TallyVotes::vote ( unsigned int id, Ballot ballot ) {
	if ( finishVoters < group ) {					// check at the beginning if there is not enough voter
		return Failed;
	}	// if
	printer.print( id, Voter::Vote, ballot ); 

	pictureWeight += ballot.picture;
	statueWeight += ballot.statue;
	giftShopWeight += ballot.giftshop;

	if ( waiters() != total() - 1 ) {			// don't have enough voter yet
		printer.print( id, Voter::Block, waiters() + 1 );
		uBarrier::block();
		printer.print( id, Voter::Unblock, waiters() );
	} else {															// there is enough voters to form a group
		uBarrier::block();
		printer.print( id, Voter::Complete );

		// compare by the option that voter select and choose the most one
		if ( giftShopWeight > statueWeight && giftShopWeight > pictureWeight ) {
			destination = GiftShop;
		} else if ( statueWeight > pictureWeight ) {
			destination = Statue;
		} else {
			destination = Picture;
		}	// if

		// reset the value
		giftShopWeight = 0;
		statueWeight = 0;
		pictureWeight = 0;
	}	// if

	if ( finishVoters < group ) {					// check if there is not enough voter at the end
		return Failed;	
	}
	return destination;
}	// TallyVotes::Tour TallyVotes::vote


//--------------------------------------------------------------------------------------------------------------------
// void TallyVotes::done: when voter finish their tour call done to make a record
//--------------------------------------------------------------------------------------------------------------------
void TallyVotes::done() {
	finishVoters--;
	if ( finishVoters < group && waiters() > 0 ) {
		block();
	}	// if
}	// void TallyVotes::done
