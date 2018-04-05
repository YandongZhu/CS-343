//--------------------------------------------------------------------------------------------------------------------
// Interface for the class voter that need to vote
//--------------------------------------------------------------------------------------------------------------------
#ifndef __VOTER_H__
#define __VOTER_H__

#include "MPRNG.h"
#include "q1tallyVotes.h"

class Printer;

_Task Voter {
    unsigned int id;                      // the voter id
    unsigned int nvotes;                  // the chance a voter can get for this tour
    TallyVotes & voteTallier;             // the current tally vote for voter voting    
    Printer & printer;                    // print for printing the result
    TallyVotes::Ballot cast();  
    void main();
  public:
    enum States { Start = 'S', Vote = 'V', Block = 'B', Unblock = 'U', Barging = 'b',
                   Complete = 'C', Finished = 'F', Failed = 'X' };
    Voter( unsigned int id, unsigned int nvotes, TallyVotes & voteTallier, Printer & printer );
};

#endif