#include <iostream>
#include <cstdlib>                      // access: rand, srand
using namespace std;
#include <unistd.h>                     // access: getpid

int times = 1000;                       // default value

int rtn1( int i ) {
    int rtn1Code = -1;
    bool rtn1Flag = true;
    for ( int j = 0; j < times && rtn1Flag; j += 1 ) {
        if ( rand() % 10000 == 42 ) {
            rtn1Flag = false;
            rtn1Code = j;
        }
    }
    return rtn1Code; 
}
int rtn2( int i ) {
    int rtn2Code = -1;
    bool rtn2Flag = true;
    for ( int j = times; j >= 0 && rtn2Flag; j -= 1 ) { 
        if ( rand() % 10000 == 42 ) {
            rtn2Flag = false;
            rtn2Code = j;
        }
    }
    return rtn2Code;
}
int g( int i ) {
    int gCode = -1;
    bool gFlag = true;
    for ( int j = 0; j < times && gFlag; j += 1 ) {
        if ( rand() % 2 == 0 ) {
            gCode = rtn1( i );
            if ( gCode != -1 ) gFlag = false;
        } 
        else {
            gCode = rtn2( i );
            if ( gCode != -1 ) gFlag = false;
        }
    }
    if ( i % 2 && gFlag ) {
        gCode = rtn2( i );
        if ( gCode != -1 ) gFlag = false;
    }
    if ( gFlag ) gCode = rtn1( i );

    return gCode;
}
int f( int i ) {
    int fCode = -1;
    bool fFlag = true;
    for ( int j = 0; j < times && fFlag; j += 1 ) {
        fCode = g( i );
        if ( fCode != -1 ) fFlag = false;
    }
    if ( i % 2  && fFlag ) {
        fCode = g( i );
        if ( fCode != -1 ) fFlag = false;
    }
    if ( fFlag ) 
        fCode = g( i );

    return fCode;
}
int main( int argc, char *argv[] ) {
    int seed = getpid();                // default value
    try {               // process command-line arguments
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