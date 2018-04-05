#include <iostream>

using namespace std;

_Coroutine Format {
	char ch; // used for communication
	int g, b; // global because used in destructor
	void main() {
		for ( ;; ) { // for as many characters
			for ( g = 0; g < 5; g += 1 ) { // groups of 5 blocks
				for ( b = 0; b < 4; b += 1 ) { // blocks of 4 characters
					for ( ;; ) { // for newline characters
							suspend();
						if ( ch != '\n' ) break; // ignore newline
					}
					cout << ch; // print character
				}
				cout << " "; // print block separator
			}
			cout << endl; // print group separator
		}
	}
public:
	Format() { resume(); } // start coroutine
	~Format() { if ( g != 0 || b != 0 ) cout << endl; }
	void prt( char ch ) { Format::ch = ch; resume(); }
};
int main() {
	Format fmt;
	char ch;
	cin >> noskipws; // turn off white space skipping
	for ( ;; ) {
			cin >> ch; // read one character
		if ( cin.fail() ) break; // eof ?
			fmt.prt( ch );
	}
}
