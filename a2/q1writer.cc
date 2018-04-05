//--------------------------------------------------------------------------------------------------------------------
// Implement function for the writer
//--------------------------------------------------------------------------------------------------------------------

#include <iostream>
#include "q1writer.h"

using namespace std;

Writer::Writer( ostream * o ): out(o), count(0) {
	next = NULL;
}	// Writer::Writer

void Writer::main(){
	for ( ;; ) {
		try {
			_Enable {};
		}	catch ( Eof & ) {	// if reaches eof then output the number of character
			*out << count << " characters" << endl;
			_Throw Eof();
		}	// try
		*out << ch;
		count++;
		suspend();
	} // for
}	// Writer::main
