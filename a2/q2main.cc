//--------------------------------------------------------------------------------------------------------------------
// The entry for the hot potato program
//--------------------------------------------------------------------------------------------------------------------

#include <iostream>
#include <unistd.h>  
#include <vector>
#include "PRNG.h"

#include "q2potato.h"
#include "q2player.h"

using namespace std;

int seed = getpid();
	
PRNG randomNum( seed );

int main(int argc, char const *argv[])
{	
	
	int player = randomNum( 2, 10 );
	int game = 5;
	try {
		switch ( argc ) {
			case 4: {
				seed = stoi( argv[3] ); 
				if ( seed <= 0 ) throw 1;
				randomNum.seed( seed );				// reset the random seed
			}
			case 3: {
				player = stoi( argv[2] ); 
				if ( player < 2 ) throw 1;
			}
			case 2: {
				game = stoi( argv[1] ); 
				if ( game <= 0 ) throw 1;
			}
		} 
	} catch ( ... ) {
		cout << "Usage: " << argv[0] << " [ games (>= 0) | \"x\" [ players (>= 2) | \"x\" [ random-seed (> 0) | \"x\" ] ] ]" << endl;
		exit ( 1 );
	}	// try

	Potato * po = new Potato;

	for (int i = 0; i < game; ++i) {
		if ( i ){												// if it is the second game
			cout << endl;
			cout << endl;
		}	// if 

		std::vector< Player * > playerList;

		Player * curPlayer;

		for (int j = 0; j < player; ++j) {		// create all the players
			curPlayer = new Player ( j, *po );
			playerList.push_back( curPlayer );	// push the player into the player list
		}	// for

		Player::umpire = playerList[0];				// set the umpire
		playerList[0]->start( *playerList[1], *playerList[player-1] );		// set the first and the last neightbour player
		playerList[player-1]->start( *playerList[0], *playerList[player-2] );
		
		for (int j = 1; j < player-1; ++j) {	// set the rest neightbour for the players
			playerList[j]->start( *playerList[j+1], *playerList[j-1] );
		}	// for
		cout << player << " players in the game" << endl;
		cout << "U ";

		playerList[0]->toss();								// start the game

		delete Player::umpire;
	}

	delete po;
	return 0;
}

