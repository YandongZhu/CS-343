//--------------------------------------------------------------------------------------------------------------------
// Implement for the tally vote using semaphore
//--------------------------------------------------------------------------------------------------------------------
#include <iostream>

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
	Printer & printer): voters(voters), group(group), printer(printer) {
	finishVoters = voters;
	currentVoters = 0;
	pictureWeight = 0;
	statueWeight = 0;
	giftShopWeight = 0;

	waitingVoterLock = new uSemaphore*[group];
	for ( unsigned int i = 0; i < group; ++i ) {
		waitingVoterLock[i] = new uSemaphore(0);
	}
}	// TallyVotes::TallyVotes


//--------------------------------------------------------------------------------------------------------------------
// TallyVotes::~TallyVotes: Destructor for class tallyvotes
//--------------------------------------------------------------------------------------------------------------------
TallyVotes::~TallyVotes() {
	for ( unsigned int i = 0; i < group; ++i ) {
		delete waitingVoterLock[i];
	}	// for
	delete[] waitingVoterLock;
}	// TallyVotes::~TallyVotes


//--------------------------------------------------------------------------------------------------------------------
// TallyVotes::Tour TallyVotes::vote: when voter determine there ballot call this function to vote
//--------------------------------------------------------------------------------------------------------------------
TallyVotes::Tour TallyVotes::vote( unsigned int id, Ballot ballot ) {
	voteLock.P();

	if ( finishVoters < group ) {					// check at the beginning if there is not enough voter
		voteLock.V();
		return Failed;
	}	// if

	printer.print( id, Voter::Vote, ballot );
	currentVoters++;

	pictureWeight += ballot.picture;
	statueWeight += ballot.statue;
	giftShopWeight += ballot.giftshop;

	if ( currentVoters < group ) {				// don't have enough voter yet

		printer.print( id, Voter::Block, currentVoters );
		//cout << "here" << currentVoters << endl;
		waitingVoterLock[currentVoters-1]->P( voteLock );
		currentVoters--;
		printer.print( id, Voter::Unblock, currentVoters );

	} else {															// there is enough voters to form a group

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

		for ( unsigned int i = group - 1;; --i ) {		// assign a semaphone for all member in the list
			waitingVoterLock[i]->V();
			if ( i == 0 ) {
				break;
			}	// if
		}	// for
	}	// if

	if ( finishVoters < group ) {									// check at the beginning if there is not enough voter
		voteLock.V();
		return Failed;
	}	// if
	voteLock.V();

	return destination;
}	// TallyVotes::Tour TallyVotes::vote


//--------------------------------------------------------------------------------------------------------------------
// void TallyVotes::done: when voter finish their tour call done to make a record
//--------------------------------------------------------------------------------------------------------------------
void TallyVotes::done() {
	finishVoters--;
	if ( finishVoters < group && currentVoters ) {	
		//cout << "remainVoters " << remainVoters << " currentVoters " << currentVoters << endl;
		for ( unsigned int i = group - 1;; --i ) {
			waitingVoterLock[i]->V();
			if ( i == 0 ) {
				break;
			}	// if
		}	// for
	}
}	// void TallyVotes::done


