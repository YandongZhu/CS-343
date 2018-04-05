#include <iostream>
#include "q3consumer.h"
#include "q3busyBoundedBuffer.h"
#include "q3noBusyBoundedBuffer.h"
#include "MPRNG.h"

using namespace std;

MPRNG randomNum;

#ifdef BUSY                            // busy waiting implementation
	template class Consumer<BusyBoundedBuffer<TYPE>>; 
#endif // BUSY

#ifdef NOBUSY                          // no busy waiting implementation
	template class Consumer<NoBusyBoundedBuffer<TYPE>>; 
#endif // NOBUSY

template<typename BufferType> Consumer<BufferType>::Consumer( 
	BufferType &buffer,
	const int Delay, 
	const int Sentinel, 
	int &sum ): buffer(buffer), delay(Delay), sentinel(Sentinel), sum(sum){}


template<typename BufferType> void Consumer<BufferType>::main() {
	sum = 0;
	for ( ;; ){
		//yield(rand() % delay_);
		yield( randomNum( ( unsigned int )delay -1 ) );
		int key = buffer.remove();
		if ( key == sentinel ) {
			break;
		}	// if
		sum += key;
	}
}
