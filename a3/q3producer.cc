#include <iostream>
#include "q3producer.h"
#include "q3busyBoundedBuffer.h"
#include "q3noBusyBoundedBuffer.h"
#include "MPRNG.h"

using namespace std;

extern MPRNG randomNum;



#ifdef BUSY                            // busy waiting implementation
	template class Producer<BusyBoundedBuffer<TYPE>>;
#endif // BUSY

#ifdef NOBUSY                          // no busy waiting implementation
	#include "q3noBusyBoundedBuffer.h"
	template class Producer<NoBusyBoundedBuffer<TYPE>>;
#endif // NOBUSY 

template<typename BufferType> Producer<BufferType>::Producer( 
	BufferType &buffer, 
	const int Produce, 
	const int Delay ): buffer( buffer ), produce( Produce ){
	delay = ( unsigned int )Delay;
}

template<typename BufferType> void Producer<BufferType>::main() {

  for (int i = 1; i <= produce; i++) {
		yield( randomNum( ( unsigned int )delay -1 ) );
		buffer.insert( i );
	}
}
