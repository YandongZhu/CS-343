#include <iostream>
#include <fstream>

#include "q2mergesort.h"

using namespace std;

unsigned int uDefaultStackSize() {
    return 512 * 1000;        // set task stack-size to 512K
}

void print( int * arr, int length, ostream * out ) {
	for ( int i = 0; i < length; ++i ) {
		if ( i % 22 == 0 && i != 0 ){
				*out << endl << " ";
		}
		if ( i ) {
			*out << " ";
		}
		*out << arr[i];
	}
	*out << endl;
}

void sort( ifstream * infile, ostream * out, unsigned int depth ) {
	int length;
	unsigned int num;
	int * list;

	for ( ;; ) {
		
		*infile >> length;
		if ( infile->fail() ) {
			break;
		}	// if

		list = new int[length];
		for ( int i = 0; i < length; ++i ) {
			*infile >> num;
			list[i] = num;	
		}

		print ( list, length, out );

		{
			Mergesort<TYPE> sort( list, 0, length, depth );
		}

		print ( list, length, out );

		*out << endl;
		
		delete [] list;
	}
}

int main(int argc, char const *argv[]) {
	int depth = 0;
	ifstream infile;
	ofstream outfile;	
	ostream *out = &cout;
	int size;
	int * list;
	try {
		if ( argc > 2 && argc < 5) {
			if ( argv[1][0] != '-' ) {	// if there is not a flag
				throw 1;	
			} // if
			if ( argv[1][1] == 's' ) {
				
				//ostream cout;
				switch ( argc ) {
					case 4: {
						try {
							outfile.open( argv[3] );
							out = &outfile;
						} catch ( uFile::Failure ) {
							cout << "Error! Could not open unsorted output file \"" << argv[3] << "\"" << endl;
							throw 1;
						}
					}
					case 3: {
						try {
							infile.open( argv[2] );
						} catch ( uFile::Failure ) {
							cout << "Error! Could not open unsorted input file \"" << argv[2] << "\"" << endl;
							throw 1;
						}
					}
				}	// switch
				sort ( &infile, out, ( unsigned int )depth );
			} else if ( argv[1][1] == 't' ) {
				switch ( argc ) {
					case 4: {
						depth = stoi ( argv[3] );
						if ( depth < 0 ) {
							throw 1;
						}
					}
					case 3: {
						size = stoi ( argv[2] );
						if ( size < 0 ) {
							throw 1;
						}
					}
				}	// switch

				uProcessor p[ (1 << depth) - 1 ] __attribute__(( unused )); // 2^depth-1 kernel threads
				list = new int[size];

				for ( int i = 0; i < size; ++i ) {
					list[i] = size - i;
				}

				{
					Mergesort<TYPE> sort( list, 0, size, ( unsigned int )depth );
				}

				delete[] list;

				return 0;

			} else {
				throw 1;
			}	// if
		} else {
			throw 1;
		}	// if
	} catch ( ... ) {
		cout << "Usage: " << argv[0] << " ( -s unsorted-file [ sorted-file ] | -t size (>= 0) [ depth (>= 0) ] )" << endl;
		exit ( 1 );
	}
	
	return 0;
}
