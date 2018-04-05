//--------------------------------------------------------------------------------------------------------------------
// Interface for the tally vote using three kinds of mutual exclusion
//--------------------------------------------------------------------------------------------------------------------
#ifndef __TALLYVOTES_H__
#define __TALLYVOTES_H__

class Printer;

#if defined( MC )                    // mutex/condition solution
// includes for this kind of vote-tallier
class TallyVotes {
    uCondLock barge;                 // cond lock for blocking barge
    uCondLock waitingVoter;          // cond lock when waiting for enough voter
    uOwnerLock voteLock;             // owner lock for lock the vote
    bool bargeFlag;                  // indicating there is some voter is barging or not
    // private declarations for this kind of vote-tallier
#elif defined( SEM )                // semaphore solution
#include <uSemaphore.h>
// includes for this kind of vote-tallier
class TallyVotes {
    uSemaphore voteLock;              // semaphore for block the vote
    uSemaphore **waitingVoterLock;    // array of array of semaphore for each member in the group to get a unique semaphore 
    // private declarations for this kind of vote-tallier
#elif defined( BAR )                // barrier solution
// includes for this kind of vote-tallier
#include <uBarrier.h>
_Cormonitor TallyVotes : public uBarrier {
    // private declarations for this kind of vote-tallier
#else
    #error unsupported voter type
#endif
    unsigned int voters;               // the voters number
    unsigned int group;                // the group number
    Printer & printer;                 // the using printer
    unsigned int finishVoters;         // the number of remaining voters that not finish tour yet
    unsigned int currentVoters;        // the number of current voted voters
    unsigned int pictureWeight;        // the weight for voting picture
    unsigned int statueWeight;         // the weight for voting statue
    unsigned int giftShopWeight;       // the weight for voting giftshop
    // common declarations
  public:                            // common interface
    TallyVotes( unsigned int voters, unsigned int group, Printer & printer );
    ~TallyVotes();
    struct Ballot { unsigned int picture, statue, giftshop; };
    enum Tour { Picture = 'p', Statue = 's', GiftShop = 'g', Failed = 'f' };
    Tour vote( unsigned int id, Ballot ballot );
    void done();
  private:
    Tour destination;                   // the final destination selected depended on each weight
};

#endif  