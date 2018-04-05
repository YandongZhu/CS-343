//--------------------------------------------------------------------------------------------------------------------
// Interface for the reader filter
//--------------------------------------------------------------------------------------------------------------------

#ifndef __READER_H__
#define __READER_H__

#include <iostream>
#include "q1filter.h"

_Coroutine Reader : public Filter {
		std::istream * in;											// istream to read the character
    void main();														// coroutine main
  public:		
    Reader( Filter * f, std::istream * i );	// constructor
};

#endif