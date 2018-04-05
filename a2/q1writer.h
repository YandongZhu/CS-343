//-------------------------------------------------------------------------------------------
// Interface for the for the writer
//-------------------------------------------------------------------------------------------

#ifndef __WRITER_H__
#define __WRITER_H__

#include <iostream>
#include "q1filter.h"

_Coroutine Writer : public Filter {
    std::ostream * out;				// the output stream
    int count;								// count the number of all the character
    void main();							// coroutine main
  public:
    Writer( std::ostream * o );	// constructor
};

#endif
