//--------------------------------------------------------------------------------------------------------------------
// Interface for the tally vote using three kinds of mutual exclusion
//--------------------------------------------------------------------------------------------------------------------
#ifndef __TALLYVOTES_H__
#define __TALLYVOTES_H__

class Printer;

#if defined( EXT )                           // external scheduling monitor solution
// includes for this kind of vote-tallier
_Monitor TallyVotes {
    // private declarations for this kind of vote-tallier
#elif defined( INT )                         // internal scheduling monitor solution
// includes for this kind of vote-tallier
_Monitor TallyVotes {
    uCondition requireVoter;
    // private declarations for this kind of vote-tallier
#elif defined( INTB )                        // internal scheduling monitor solution with barging
// includes for this kind of vote-tallier
_Monitor TallyVotes {
    // private declarations for this kind of vote-tallier
    bool groupFull;
    uCondition bench;                        // only one condition variable (you may change the variable name)
    void wait();                             // barging version of wait
    void signalAll();                        // unblock all waiting tasks
#elif defined( AUTO )                        // automatic-signal monitor solution
#include "AutomaticSignal.h"
// includes for this kind of vote-tallier
_Monitor TallyVotes {
    // private declarations for this kind of vote-tallier
    AUTOMATIC_SIGNAL;
    bool completeFlag;
#elif defined( TASK )                        // internal/external scheduling task solution
#include <queue>
struct Ballot;
_Task TallyVotes {
    void main();
    uCondition requireVoter, startVote;
    
    // private declarations for this kind of vote-tallier
#else
    #error unsupported voter type
#endif
    // common declarations
  public:                                    // common interface
    TallyVotes( unsigned int voters, unsigned int group, Printer & printer );
    struct Ballot { unsigned int picture, statue, giftshop; };
    enum Tour { Picture = 'p', Statue = 's', GiftShop = 'g', Failed = 'f' };
    Tour vote( unsigned int id, Ballot ballot );
    void done();
  private:
    unsigned int voters;               // the voters number
    unsigned int group;                // the group number
    Printer & printer;                 // the using printer
    unsigned int finishVoters;         // the number of remaining voters that not finish tour yet
    unsigned int currentVoters;        // the number of current voted voters
    unsigned int pictureWeight;        // the weight for voting picture
    unsigned int statueWeight;         // the weight for voting statue
    unsigned int giftShopWeight;       // the weight for voting giftshop
    Tour destination;                  // the final destination selected depended on each weight
#if defined( TASK )  
    std::queue<std::pair<unsigned int, Ballot>> ballotQueue;
#endif
};

#endif