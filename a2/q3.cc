#include <iostream>
using namespace std;

volatile int iterations = 10000000, shared = 0; // volatile to prevent dead-code removal

_Task increment {
    void main() {
        for ( int i = 1; i <= iterations; i += 1 ) {
            shared += 1;                // two increments to increase pipeline size
            shared += 1;
        }
    }
};
int main( int argc, char * argv[] ) {
    if ( argc == 2 ) iterations = atoi( argv[1] );
#ifdef __U_MULTI__
    uProcessor p;                       // create 2nd kernel thread
#endif // __U_MULTI__
    {
        increment t[2];
    } // wait for tasks to finish
    cout << "shared:" << shared << endl;
}