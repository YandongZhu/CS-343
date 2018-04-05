//--------------------------------------------------------------------------------------------------------------------
// Implement function for the reader
//--------------------------------------------------------------------------------------------------------------------

#include <iostream>
#include "q1reader.h"

using namespace std;

Reader::Reader( Filter * f, istream * i): in(i) {
	next = f;
}	// Reader::Reader

void Reader::main() {
	*in >> noskipws;			// ignore white spaces
	char start;					
	for ( ;; ) {
		*in >> start;				// input each character at a time
		if ( in->fail() || in->eof() ) {	// if reach eof
			_Resume Eof() _At *next;				// pass exception to the next filter
		}	// if
		next->put(start);	
	}	// for

	cout << "finish" << endl;
	
}