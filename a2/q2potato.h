//--------------------------------------------------------------------------------------------------------------------
// Interface for the potato class
//--------------------------------------------------------------------------------------------------------------------

#ifndef __POTATO_H__
#define __POTATO_H__

#include "PRNG.h"

class Potato {
		int times;																// the remaining explode time
  public:
    _Event Explode {};												// event for raise explode exception
    Potato( unsigned int maxTicks = 10 );			// constructor
    void reset( unsigned int maxTicks = 10 );	// reset the explode times
    void countdown();													// reduce countdown time by 1
};

#endif