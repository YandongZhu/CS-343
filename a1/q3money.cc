//--------------------------------------------------------------------------------------------------------------------
// Implement function for the Coroutine Money
//--------------------------------------------------------------------------------------------------------------------

#include <iostream>
#include <string>
#include "q3money.h"														// defination for the Money interface

using namespace std;

//--------------------------------------------------------------------------------------------------------------------
// Define the Coroutine main function
//--------------------------------------------------------------------------------------------------------------------
void Money::main() {
	for ( ;; ) {
		// init the condtions for the new line
		status = false;
		decimal = 0;
		separator = 0;
		validStr = "";
		invalidStr = "";

		try {
			validStr += ch;
			if ( ch == 'E' || ch == '$' ) {				// define the separator and decimal by the kind of currency 
				if ( ch == 'E' ) {						
					separator = '.';
					decimal = ',';
				} else {
					separator = ',';
					decimal = '.';
				} // if 
			} else {															// if the currency kind can't be recognize
				_Throw Error();											
			} // if									
			suspend();

			if ( ch == '-' ) {										// if the amount is negative
				validStr += ch;
				suspend();
			}
	
			validStr += ch;
			if ( ch < '0' || ch > '9' ) {					// if the first digit is not a number
				_Throw Error();											
			}
			suspend();

			int count;
			for ( count = 0; count < 2; ++count ) {	// the first group may not be 3 digits
				validStr += ch;
				if ( ch == separator ) {
					suspend();
					break;
				}	else if ( ch == decimal ) {					// if the character is the decimal
					_Resume Match();									
				} else if ( ch < '0' || ch > '9' ) {	// if the character is not a valid digit
					_Throw Error();										
				}	// if
				suspend();
			}	// for

			if ( count == 2 ) {										// if the first group has 3 digits, the next one should be decimal or separator
				validStr += ch;
				if ( ch == decimal ) { 							// if the next character is decimal
					_Resume Match();
				} else if ( ch != separator ) {			// else if the next character is not separator
					_Throw Error();										
				}	// if
				suspend();
			} // if

			for ( int j = 0 ; j < 4; ++j ) {			// there will remain 4 groups at max
				for ( int i = 0; i < 3; ++i ){			// start with 3 digits
					validStr += ch;
					if ( ch < '0' || ch > '9' ) {			// if the first 3 digits is not a number
						_Throw Error();									
					}	// if
					suspend();
				} // for
				validStr += ch;			

				if ( ch == decimal ) {							// if follow by a decimal
				 _Resume Match();										
				} else if ( ch != separator ) {			// else if it is not followed by a separator
					_Throw Error();										
				}
				suspend();
			}	// for

			invalidStr += ch;
			_Throw Error();												// if after 5 groups the input doesn't end
		} // try
		_CatchResume ( Match & ) {							// if we meet a decimal

			for ( int i = 0; i < 2; ++i ) {				// after decimal will follow by two digits
				suspend();
				validStr += ch;
				if ( ch < '0' || ch > '9' ) {				// if the following digit is not a number
					_Throw Error();										
				}
			}	// for

			_Throw Match();												// check is there any extra digits or not
		} // _CatchResume
		catch ( Match & ) {											// if the amount is valid
			status = "yes";
		}	// catch
		catch ( Error & ) {											// if the amount is invalid
			status = "no";
		}	// catch

		if (ch != 0) suspend();									// if the line not ended yet, there still had some input in the line

		for ( ;; ) {														// if there still has the input
			if ( ch == 0 ) break;									// if the line ended
				invalidStr += ch;
				suspend();
		}	// for

		cout << "'" << validStr << "' " << status;
		if ( invalidStr.length() != 0 ) {				// output the extra characters if there is
			cout << " -- extraneous characters '" << invalidStr << "'";	
		}
		cout << endl;
		suspend();															// waiting for the next line
	}	// for
	return;
} // Money::main
