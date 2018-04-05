#include <iostream>
#include "q3busyBoundedBuffer.h"

using namespace std;

template class BusyBoundedBuffer<TYPE>;

template <typename T> BusyBoundedBuffer<T>::BusyBoundedBuffer( 
	const unsigned int size ): capacity(size), lock(), consumer(), producer(){}

template <typename T> void BusyBoundedBuffer<T>::insert( T elem ) {
	lock.acquire();

	for ( ;; ) {
		if ( buffer.size() < capacity ) {
			break;
		}
		producer.wait(lock);
	}	// for
	
	assert( buffer.size() < capacity );
	buffer.push( elem );

	consumer.signal();
	lock.release();

}

template <typename T> T BusyBoundedBuffer<T>::remove() {
  lock.acquire();
  for ( ;; ) {
    if ( buffer.size() > 0 ) {
      break;
    }
    consumer.wait(lock);
  }

  T result = buffer.front();

  buffer.pop();

  producer.signal();
  lock.release();

  return result;
}