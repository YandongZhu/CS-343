//--------------------------------------------------------------------------------------------------------------------
// Interface for the class printer which is used to print all the status in the tallyvote
//--------------------------------------------------------------------------------------------------------------------

#ifndef __PRINTER_H__
#define __PRINTER_H__

#include "q2voter.h"
#include "q2tallyVotes.h"

class TallyVotes;

_Monitor Printer { 
  unsigned int voters;                    // num of voters
  // struct for recording all the voters infomation
  struct VoterState {
    bool data;                            // voter has data or not
    TallyVotes::Ballot voteResult;        // voter's ballot result
    TallyVotes::Tour destination;         // the destination is selected after tally
    Voter::States curState;               // votter's current status
    unsigned int blockNum;                // the num of voters is blocked
  };
	VoterState * voterState;                // array for including all the voters infomation whose size is the num of voters
	void flush();                       
	void printBallot( TallyVotes::Ballot curBallot );
  public:
    Printer( unsigned int voters );
    ~Printer();
    void print( unsigned int id, Voter::States state );
    void print( unsigned int id, Voter::States state, TallyVotes::Tour tour );
    void print( unsigned int id, Voter::States state, TallyVotes::Ballot ballot );
    void print( unsigned int id, Voter::States state, unsigned int numBlocked );
};

#endif