//--------------------------------------------------------------------------------------------------------------------
// Implement for the tally vote using mutex and condition
//--------------------------------------------------------------------------------------------------------------------
#include <iostream>

#include "q1tallyVotes.h"
#include "q1printer.h"

using namespace std;


//--------------------------------------------------------------------------------------------------------------------
// TallyVotes::TallyVotes: Constructor for class tallyvotes
//--------------------------------------------------------------------------------------------------------------------
TallyVotes::TallyVotes ( 
	unsigned int voters, 
	unsigned int group, 
	Printer & printer): voters(voters), group(group), printer(printer) {
	finishVoters = voters;
	currentVoters = 0;
	pictureWeight = 0;
	statueWeight = 0;
	giftShopWeight = 0;
	bargeFlag = false;
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
	voteLock.acquire();

	if ( finishVoters < group ) {					// check at the beginning if there is not enough voter
		voteLock.release();
		return Failed;
	}	// if

	if ( bargeFlag ) {											// if there is some thread block in the waiting list
		printer.print( id, Voter::Barging );
		barge.wait( voteLock );								// put it self into waiting list
		if ( barge.empty() ) {								// if there is no more thread in the barge list
			bargeFlag = false;
		}	// if
	}	// if

	printer.print( id, Voter::Vote, ballot );

	currentVoters++;

	pictureWeight += ballot.picture;
	statueWeight += ballot.statue;
	giftShopWeight += ballot.giftshop;

	if ( currentVoters < group ) {					// don't have enough voter yet

		printer.print( id, Voter::Block, currentVoters );

		barge.signal();
		waitingVoter.wait( voteLock );
		//cout << "get signal " << endl;
		currentVoters--;
		printer.print( id, Voter::Unblock, currentVoters );
	} else {																// there is enough voters to form a group
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

		// reset the values
		giftShopWeight = 0;
		statueWeight = 0;
		pictureWeight = 0;

	}	// if

	// check if there is some voter in the waiting list
	bargeFlag = !waitingVoter.empty() || !barge.empty();
	if ( !waitingVoter.empty() ) {								// wake up the voter in the waiting list first	
		waitingVoter.signal();	
	} else {																			// then wake up the voters in the barge list
		barge.signal();
	}	// if

	if ( finishVoters < group ) {									// check at the beginning if there is not enough voter
		voteLock.release();
		return Failed;
	}	// if

	voteLock.release();
	return destination;
}	// TallyVotes::Tour TallyVotes::vote


//--------------------------------------------------------------------------------------------------------------------
// void TallyVotes::done: when voter finish their tour call done to make a record
//--------------------------------------------------------------------------------------------------------------------
void TallyVotes::done() {
	finishVoters--;
	if ( finishVoters < group && (!waitingVoter.empty() || !barge.empty() )) {
		if ( !waitingVoter.empty() ) {								// wake up the voter in the waiting list first	
			waitingVoter.signal();	
		} else {																			// then wake up the voters in the barge list
			barge.signal();
		}	// if
	}
}	// void TallyVotes::done


