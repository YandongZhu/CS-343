//--------------------------------------------------------------------------------------------------------------------
// Implement function for the potato class
//--------------------------------------------------------------------------------------------------------------------

#include "q2potato.h"
#include <iostream>
#include <string>
using namespace std;

extern int seed;

extern PRNG randomNum;

Potato::Potato( unsigned int maxTicks ) {

	times = randomNum( 1, maxTicks );
	string postFix = " tosses";
	if ( times == 1 ) {				// if the potato explode in one time, reset the notification
		postFix = " toss";
	}	// if
	cout<< "  POTATO goes off after " << times << postFix << endl;
}	// Potato::Potato

void Potato::reset( unsigned int maxTicks ) {

	times = randomNum( 1, maxTicks );
	string postFix = " tosses";
	if ( times == 1 ) {				// if the potato explode in one time, reset the notification
		postFix = " toss";
	}	// if

	cout<< "  POTATO goes off after " << times << postFix << endl;
}	// Potato::reset

void Potato::countdown() {

	if (times == 1) {					// if it reach the final time
		_Throw Explode ();
	}	// if
	times--;
}	// Potato::countdown