#include <iostream>
#include <cstdlib>                      // access: rand, srand
using namespace std;
#include <unistd.h>                     // access: getpid

int times = 1000;                       // default value

int rtn1( int i ) {
    int rtn1Code = -1;
    for ( int j = 0; j < times; j += 1 ) {
        if ( rand() % 10000 == 42 ) {
            rtn1Code = j;
            break;
        };
    }
    return rtn1Code;
}
int rtn2( int i ) {
    int rtn2Code = -1;
    for ( int j = times; j >= 0; j -= 1 ) {
        if ( rand() % 10000 == 42 ) {
            rtn2Code = j;
            break;
        };
    }
    return rtn2Code;
}
int g( int i ) {
    int gCode = -1;
    for ( int j = 0; j < times && gCode == -1; j += 1 ) {
        if ( rand() % 2 == 0 ) gCode = rtn1( i );
        else gCode = rtn2( i );
    }
    if ( i % 2 && gCode == -1 ) gCode = rtn2( i );
    if ( gCode == -1 ) rtn1( i );

    return gCode;
}
int f( int i ) {
    int fCode = -1;
    for ( int j = 0; j < times && fCode == -1; j += 1 ) {
        fCode = g( i );
    }
    if ( i % 2 && fCode == -1 ) g( i );
    if ( fCode == -1 )g( i );

    return fCode;
}
int main( int argc, char *argv[] ) {
    int seed = getpid();                // default value
    try {				// process command-line arguments
        switch ( argc ) {
          case 3: times = stoi( argv[2] ); if ( times <= 0 ) throw 1;
          case 2: seed = stoi( argv[1] ); if ( seed <= 0 ) throw 1;
          case 1: break;                // use defaults
          default: throw 1;
        } // switch
    } catch( ... ) {
        cout << "Usage: " << argv[0] << " [ seed (> 0) [ times (> 0) ] ]" << endl;
        exit( 1 );
    } // try
    srand( seed );			// set random-number seed
    int mainCode = f( 3 );
    if ( mainCode == -1 )
        cout << "seed:" << seed << " times:" << times << " complete" << endl;
    else    
        cout << "seed:" << seed << " times:" << times << " rc:" << mainCode << endl;
}