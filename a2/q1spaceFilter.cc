//--------------------------------------------------------------------------------------------------------------------
// Implement function for the space filter
//--------------------------------------------------------------------------------------------------------------------

#include <iostream>
#include "q1spaceFilter.h"

using namespace std;

SpaceFilter::SpaceFilter( Filter * f ){
	next = f;
}	// SpaceFilter::SpaceFilter

void SpaceFilter::main(){
		for ( ;; ){
			try {
				_Resume Space();

				for ( ;; ) {							// now the next input will not be whitespace
					_Enable {}
					if ( ch == ' ' || ch == '\t' ) {		// if the next character is a whitespace
						_Resume Space();
						next->put(' ');
					} else {
						next->put( ch );
						if ( ch == '\n' ){		// if there is a new line
							break;
						}	// if
						suspend();
					}	// if		
				}	// for
				suspend();
			} _CatchResume ( Space & ) {
				for ( ;; ){		// if it is no longer space or tab
					if ( ch != ' ' && ch != '\t' ) {
						break;
					}	// if
					suspend();
				}	// for
			} catch ( Eof & ) {		// if it reaches eof
				_Resume Eof() _At *next;
			} // try
		}	// for
}	// SpaceFilter::main