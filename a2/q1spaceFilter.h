//--------------------------------------------------------------------------------------------------------------------
// Interface for the for the space filter
//--------------------------------------------------------------------------------------------------------------------

#ifndef __SPACEFILTER_H__
#define __SAPCEFILTER_H__

#include "q1filter.h"

_Coroutine SpaceFilter : public Filter {
    _Event Space {};							// exception for the space case
    void main();									// coroutine main
  public:
    SpaceFilter( Filter * f );		// constructor
};

#endif