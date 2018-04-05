//--------------------------------------------------------------------------------------------------------------------
// Implement function for the Coroutine push filter
//--------------------------------------------------------------------------------------------------------------------

#include "q1pushFilter.h"

using namespace std;

PushFilter::PushFilter ( Filter * f ) {
	next = f;
}	// PushFilter::PushFilter

void PushFilter::main() {
	for ( ;; ) {
		try {
			_Enable {};
			if ( ( ch >= 'a' && ch <= 'z' ) || ( ch >= 'A' && ch <= 'Z' )) {	// if the char is a English letter
				_Resume AlphaBet();
			}	// if
			next->put(ch);
			suspend();
		} _CatchResume ( AlphaBet & ) {
			if ( ch == 'z' || ch == 'Z' ) {			// if the character is the last one which is 'z'
				ch = ch - 25;
			} else {
				ch = ch + 1;
			}	// if
		} catch ( Eof & ) {
			_Resume Eof() _At *next;
		}	// try
	}	// for
}	// PushFilter::main