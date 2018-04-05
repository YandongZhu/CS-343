//--------------------------------------------------------------------------------------------------------------------
// Define the interface for the Hex Filter
//--------------------------------------------------------------------------------------------------------------------

#ifndef __HEXFILTER_H__
#define __HEXFILTER_H__

#include "q1filter.h"

_Coroutine HexFilter : public Filter {
    void main();							// coroutine main
    void groupFour();					// to generate a four character grout
    void groupEight();				// to generate a four character grout
    void charToHex();					// to convert a character into hex form
  public:
    HexFilter( Filter * f );	// constructor
};

#endif