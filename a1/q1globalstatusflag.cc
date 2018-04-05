#include <iostream>
#include <cstdlib>                      // access: rand, srand
using namespace std;
#include <unistd.h>                     // access: getpid

int times = 1000;                       // default value
int flag = -1;                          // flag for expectation

void rtn1( int i ) {
    for ( int j = 0; j < times; j += 1 ) {
        if ( rand() % 10000 == 42 ) {
            flag = j;
            return;
        }
    }
    return; 
}
void rtn2( int i ) {
    for ( int j = times; j >= 0; j -= 1 ) { 
        if ( rand() % 10000 == 42 ) {
            flag = j;
            return;
        }
    }
    return;
}
void g( int i ) {
    for ( int j = 0; j < times && flag == -1; j += 1 ) {
        if ( rand() % 2 == 0 ) rtn1( i );
        else rtn2( i );
    }
    if ( i % 2 && flag == -1 ) rtn2( i );
    if ( flag == -1 ) rtn1( i );

    return;
}
void f( int i ) {
    for ( int j = 0; j < times && flag == -1; j += 1 ) {
        g( i );
    }
    if ( i % 2  && flag == -1 ) g( i );
    if ( flag == -1 ) g( i );

    return;
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
    srand( seed );          // set random-number seed
    f( 3 );
    if ( flag == -1 )
        cout << "seed:" << seed << " times:" << times << " complete" << endl;
    else 
        cout << "seed:" << seed << " times:" << times << " rc:" << flag << endl;
}