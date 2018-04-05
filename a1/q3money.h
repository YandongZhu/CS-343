//--------------------------------------------------------------------------------------------------------------------
// Define the interface for the Coroutine money
//--------------------------------------------------------------------------------------------------------------------
#include <string>												// Define string

_Coroutine Money {
		char ch;														// the current character
		char separator;											// the separator mark for the current kind
		char decimal;												// the decimal mark for the current kind
		std::string status;									// the message for success or not
		std::string validStr;								// the current valid string
		std::string invalidStr;							// the unnesserary string
    void main();                        // coroutine main
  public:
    _Event Match {};                    // last character match
    _Event Error {};                    // last character invalid

   	void next( char c );			
};
