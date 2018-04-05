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
}	// TallyVotes::TallyVotes

//--------------------------------------------------------------------------------------------------------------------
// TallyVotes::Tour TallyVotes::vote: when voter determine there ballot call this function to vote
//--------------------------------------------------------------------------------------------------------------------
TallyVotes::Tour TallyVotes::vote ( unsigned int id, Ballot ballot ) {

	if ( finishVoters < group ) {					// check if there is not enough voter at the end
		RETURN(Failed);	
	}	// if
	
	currentVoters++;
	printer.print( id, Voter::Vote, ballot ); 

	pictureWeight += ballot.picture;
	statueWeight += ballot.statue;
	giftShopWeight += ballot.giftshop;

	if ( currentVoters < group ) {
		completeFlag = false;
	} else {
		printer.print( id, Voter::Complete );

		currentVoters--;

		// compare by the option that voter select and choose the most one
		if ( giftShopWeight > statueWeight && giftShopWeight > pictureWeight ) {
			destination = GiftShop;
		} else if ( statueWeight > pictureWeight ) {
			destination = Statue;
		} else {
			destination = Picture;
		}	// if

		completeFlag = true;

		// reset the value
		giftShopWeight = 0;
		statueWeight = 0;
		pictureWeight = 0;
	}

	WAITUNTIL (
		completeFlag,
		printer.print( id, Voter::Block, currentVoters ),
		printer.print( id, Voter::Unblock, --currentVoters )
	);

	if ( finishVoters < group ) {					// check if there is not enough voter at the end
		RETURN( Failed );	
	}	// if

	RETURN( destination );
}

//--------------------------------------------------------------------------------------------------------------------
// void TallyVotes::done: when voter finish their tour call done to make a record
//--------------------------------------------------------------------------------------------------------------------
void TallyVotes::done() {
	finishVoters--;
	if ( finishVoters < group ) {	// if there is not enough voter to form a group
		completeFlag = true;
	}	// if
}	// void TallyVotes::done
