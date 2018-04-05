//--------------------------------------------------------------------------------------------------------------------
// Define the interface for the parent class Filter
//--------------------------------------------------------------------------------------------------------------------

#ifndef __FILTER_H__
#define __FILTER_H__

_Coroutine Filter {
  protected:
    _Event Eof {};                    // no more characters
    Filter * next;                    // next filter in chain
    unsigned char ch;                 // communication variable
  public:
  	~Filter ();												// destructor
    void put( unsigned char c );			
};

#endif