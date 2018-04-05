//--------------------------------------------------------------------------------------------------------------------
// Interface for the hot potato players
//--------------------------------------------------------------------------------------------------------------------

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "q2potato.h"

_Coroutine Player {
    _Event Terminate {
      public:
        Player * victim;                      // delete player
        Terminate( Player * victim ) : victim( victim ) {}
    };
    _Event Election {
      public:
        int id;                               // highest id seen so far
        Election( int id ) : id( id ) {}
    };
    Player * partner[2];                      // left and right player
    int id;                                   // the player id
    Potato & potato;                          // the current potato
    void main();                              // coroutine main
  public:
    static Player * umpire;                   // current umpire
    Player( int id, Potato & potato );
    void start( Player & lp, Player & rp );   // supply partners
    void toss();                              // tossed the potato
    void vote( int id );                      // resume partner to vote
    void terminate();                         // resume umpire to delete
};

#endif