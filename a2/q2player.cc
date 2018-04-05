//--------------------------------------------------------------------------------------------------------------------
// Implement function for the player
//--------------------------------------------------------------------------------------------------------------------

#include "q2player.h"
#include "q2potato.h"
#include "PRNG.h"
#include <iostream>
using namespace std;

extern int seed;

extern PRNG randomNum;

Player * Player::umpire;

Player::Player( int id, Potato & potato ): id( id ), potato( potato ) {

}	// Player::Player

void Player::main() {

	suspend();																			// suspend when int(main) first call the coroutine
	for ( ;; ){
		try {
			_Enable {
				if ( id == partner[1]->id ) {							// if now the partern is the player, which means no more player
					break;
				}	// if
				cout << id;
				potato.countdown();
				cout << " -> ";
				int next = randomNum( 1 );
				partner[next]->toss();
			};
		} catch ( Potato::Explode & bomb ){						//	if the potato bomb
			cout << " is eliminated" << endl;
			if ( umpire == this ) {											// if the current umpire is the victim
				cout << "E " << id ;
				_Resume Election( id ) _At *partner[1];		// then start election from the right player
				try {
					_Enable {																// enable to catch the election exception
						partner[1]->vote ( id );						
					} 
				} _CatchResume ( Election & playerId ) {	// when the election complete as a loop and back the victim, in this case which is the umpire.
					cout << " : umpire " << playerId.id << endl;
				}	// try
			}	// if
			partner[0]->partner[1] = partner[1];
			partner[1]->partner[0] = partner[0];

			_Resume Terminate( this ) _At *umpire;			// ask the umpire to delete the victim
			umpire->terminate();
		} catch ( Terminate & playerId ) {						// if the umpire is asked to delete player

			delete playerId.victim;
			potato.reset();															// start the game again
			cout << "U ";
			umpire->toss();
		}  catch ( Election & playerId ) {						// if the player is ask to elect the new umpire
			cout << " -> " << id ;

			Player::umpire = this;

			_Resume Election( id ) _At *partner[1];			// ask the player on his right to elect the new one
			partner[1]->vote( partner[1]->id );
		} // try
	}	// for
	cout << id << " wins the Match!" << endl;
}	// Player::main

void Player::start( Player & lp, Player & rp ) {
	partner[0] = &rp;
	partner[1] = &lp;
	resume();
}	// Player::start

void Player::toss() {
	resume();
}	// Player::toss

void Player::terminate() {
	resume();
}	// Player::terminate

void Player::vote( int id ){
	( void )id;
	resume();
}	// Player::vote