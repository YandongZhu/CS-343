//--------------------------------------------------------------------------------------------------------------------
// The interface for the self create filter Push Filter
// which simply push a alphabet character to the next one
// (e.g. a->b, b->c, z->a) It is the most simply way to 
// encrypt a context
//--------------------------------------------------------------------------------------------------------------------


#ifndef __PUSHFILTER_H__
#define __PUSHFILTER_H__

#include "q1filter.h"

_Coroutine PushFilter : public Filter {
		_Event AlphaBet {};				// If we meet a alphabet
    void main();							// coroutine main
  public:
    PushFilter( Filter * f );	// constructor
};

#endif