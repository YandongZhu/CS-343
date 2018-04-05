#include <iostream>
#include "MPRNG.h"

MPRNG randomNum();

#include "q3consumer.h"
#include "q3producer.h"

using namespace std;

// #include "q3busyBoundedBuffer.h"
// typedef BusyBoundedBuffer<int> BoundedBuffer;
#ifdef BUSY                            // busy waiting implementation
	#include "q3busyBoundedBuffer.h"
	typedef BusyBoundedBuffer<TYPE> BoundedBuffer;
#endif // BUSY

#ifdef NOBUSY                          // no busy waiting implementation
	#include "q3noBusyBoundedBuffer.h"
	typedef NoBusyBoundedBuffer<TYPE> BoundedBuffer;
#endif // NOBUSY



int main(int argc, char const *argv[]) {
	int cons = 5;
	int prods = 3;
	int produce = 10;
	unsigned int bufferSize = 10;
	int delay;

	try {
		switch ( argc ) {
			case 6: delay = stoi( argv[5] ); if ( delay < 1 ) throw 1;
			case 5: bufferSize = stoi( argv[4] ); if ( bufferSize < 1 ) throw 1;
			case 4:	produce = stoi( argv[3] ); if ( produce < 1 ) throw 1;
			case 3: prods = stoi( argv[2] ); if ( prods < 1 ) throw 1;
			case 2: cons = stoi( argv[1] ); if ( cons < 1 ) throw 1; 
			case 1: break;
			default: throw 1;
		}
		if ( argc != 6 ) {
			delay = cons + prods;
		}
	} catch ( ... ) {
		cout << "Usage:" << argv[0] << " [ Cons (> 0) [ Prods (> 0) [ Produce (> 0) [ BufferSize (> 0) [ Delay (> 0) ] ] ] ] ]" << endl;
		exit ( 1 );
	}

	#ifdef __U_MULTI__
  	// create additional processor (tostmostor is dual-core!)
  	uProcessor p __attribute__((unused));
	#endif // __U_MULTI__

  BoundedBuffer buffer( bufferSize );
  unsigned int sentinel = -1;
  int sum = 0;
  int sums[cons];
  Consumer<BoundedBuffer>* consumers[cons];
  Producer<BoundedBuffer>* producers[prods];
  for (int i = 0; i < cons; ++i){
  	consumers[i] = new Consumer<BoundedBuffer> ( buffer, delay, sentinel, sums[i]);
  }

  for (int i = 0; i < prods; ++i){
  	producers[i] = new Producer<BoundedBuffer>( buffer, produce, delay );
  }

  for (int i = 0; i < prods; ++i){
  	delete producers[i];
  }

	for (int i = 0; i < cons; i++) {
		buffer.insert( sentinel );
	}  

	for (int i = 0; i < cons; ++i) {
		delete consumers[i];
		sum += sums[i];
	}
	cout << sum << endl;
	return 0;
}
