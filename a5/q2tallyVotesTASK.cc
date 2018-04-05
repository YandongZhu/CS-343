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
// TallyVotes::main: The main function for task to calculate the winner by the ballot
//--------------------------------------------------------------------------------------------------------------------
void TallyVotes::main () {

	for ( ;; ) {
		if ( requireVoter.empty() ) {	// if there is no more voter waiting in the queue, put this function into wait
			startVote.wait();
		}	// if

		if ( finishVoters == 0 ) {	// if all the voters finish their vote
			break;
		}	// if 

		// take the first ballot from the by FIFO order
		pair<unsigned int, TallyVotes::Ballot> tempBallot = ballotQueue.front();
		ballotQueue.pop();

		unsigned int id = tempBallot.first;
		TallyVotes::Ballot ballot = tempBallot.second;

		currentVoters++;
		printer.print( id, Voter::Vote, ballot ); 	

		pictureWeight += ballot.picture;
		statueWeight += ballot.statue;
		giftShopWeight += ballot.giftshop;

		if ( currentVoters == group ) {
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

			while ( ! requireVoter.empty() ) {	// wake up the voters in the condition
        requireVoter.signal();// drain the condition
      }	// while
		}	// if

		if ( finishVoters < group ) {					// check if there is not enough voter at the end
			destination = Failed;	
		}	// if
	}
}

//--------------------------------------------------------------------------------------------------------------------
// TallyVotes:: When voter call this, pass record the ballot and pass it into the main
//--------------------------------------------------------------------------------------------------------------------
TallyVotes::Tour TallyVotes::vote ( unsigned int id, Ballot ballot ) {

	if ( finishVoters < group ) {					// check if there is not enough voter at the end
		return Failed;	
	}	// if

	ballotQueue.push( make_pair( id, ballot ) );

	startVote.signal();
	requireVoter.wait();
	
	currentVoters--;
  printer.print( id, Voter::Unblock, currentVoters );

  return destination;

}

//--------------------------------------------------------------------------------------------------------------------
// void TallyVotes::done: when voter finish their tour call done to make a record
//--------------------------------------------------------------------------------------------------------------------
void TallyVotes::done() {
	finishVoters--;
	if ( finishVoters < group && !requireVoter.empty() ) {
		requireVoter.signal();
	}
}	// void TallyVotes::done
